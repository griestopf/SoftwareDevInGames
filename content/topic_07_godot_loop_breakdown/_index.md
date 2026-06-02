+++
title = 'Godot Main Loop'
draft = false
weight = 70 
+++

# Iteration Breakdown

## Main Loop

[`OS_Windows::run()` (platform\windows\os_windows.cpp#L2343)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/platform/windows/os_windows.cpp#L2342)

seems to show the classical outer game structure: An initialization phase and then the main game loop.

```cpp
void main()
{
    initialize();
    while (true)
    {
        // Process Windows messages
        ProcessInput();

        // Update game logic
        Update();

        // Render a single frame of the current scene
        RenderScene();
    }
}
```

Here the `ProcessInput()`, `Update()`, and `RenderScene()` functions all seem to be centralized into the [`Main::iteration()` (main/main.cpp#L4917)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L4917) function. 

## Scene Traversal

The RendeScene function is where the scene graph traversal happens. In a typical game engine, you would expect to see a recursive traversal of the scene graph, where each node is visited and rendered in a specific order (e.g., depth-first or breadth-first).

### Classical Model (how you'd think of it)

In a game engine, the scene graph is a hierarchical structure that organizes all the objects in the game world. Traversing the scene graph typically involves visiting each node and performing certain operations, such as updating logic, rendering, or handling physics. 

You can imagine a simple traversal like this:

```cpp
void traverseSceneGraph(Node* node) {
    // Update logic for the current node
    node->update();

    // Render the current node
    node->render();

    // Traverse child nodes
    for (Node* child : node->getChildren()) {
        traverseSceneGraph(child);
    }
}
```

### The Reality in Godot (how it actually works)

Let's look at the [`Main::iteration()` (main/main.cpp#L4917)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L4917) function that handles a single iteration of the main loop. It does not simply call a single traversal function. Instead, it has separate phases for physics, processing, and rendering.


#### Physics Processing

Physics is fixed-step, so it can run zero, one, or multiple times per rendered frame, depending on the accumulated time and the `max_physics_steps` setting. This is handled at the [for-loop early stage in the iteration function (main/main.cpp#L4966)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L4966). In this loop, it checks how much time has accumulated and runs the physics steps accordingly. A single physics step involves calling [`MainLoop::physics_process(double p_time)` (main/main.cpp#L4997)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L4997), which in turn calls `_process(true)` to process all nodes that have physics processing enabled.


> 🔧 **Assignment**
> - Inspect the for-loop and identify how a constant frame rate for physics updates is maintained.
> - Try to figure out how physics processing is abstracted allowing different physics engines (such as the "old" Bullet-based engine and the new Jolt-based Physics engine).
> - Try to identify how a single physics step is implemented and how it affects the nodes' transformations.


#### Script Processing

After the physics steps, the main iteration calls [`MainLoop::process(double p_time) ()` main/main.cpp#L5058)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L5058), which calls `_process(false)` to process all nodes that have regular processing enabled. This is where the game logic updates happen for each frame.

Interestingly, this _process call ends up in the same [`SceneTree::_process()` (scene/main/scene_tree.cpp#L1244)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/scene/main/scene_tree.cpp#L1244) function that is used for both physics and regular processing, but it distinguishes between them using a boolean parameter.

> 🔧 **Assignment**
>
> - Inspect the [`SceneTree::_process()` (scene/main/scene_tree.cpp#L1244)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/scene/main/scene_tree.cpp#L1244) function and try to grasp how it differentiates between physics processing and regular processing. Identify the places that determine the behavior based on the boolean parameter. 
> - See how GDScript nodes are processed in this function. Look for the calls to `_process()` on the nodes and how they are organized.
> - Try to identify how GDScript is interfaced with the C++ code in Godot

The `_process()` function does not traverse the entire scene graph. Instead, it uses cached lists of nodes that have processing enabled. This means that only the nodes that need to be processed are visited, which can improve performance.

#### Rendering

Finally, the rendering phase is handled by calling [`MainLoop::render(double p_time)` (main/main.cpp#L5088)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L5088).

The rendering phase is more complex and involves multiple steps, including culling, sorting, and drawing. In Godot 4.x, each renderable resource (like a mesh or a texture) is represented by a RID (Resource ID), and the rendering backend (like Vulkan) interacts with these RIDs directly. The scene graph nodes that represent renderable objects (like MeshInstance3D) have references to these RIDs, but the actual rendering process is driven by the RIDs and the rendering backend, not by traversing the scene graph.

The rendering itself is controlled by the RenderingServer/RendererSceneCull classes. In General there are three levels how the rendering is controlled:

- User-Level: The Scene Graph nodes and their ressources
- Engine-Level: The RenderingServer and RendererSceneCull classes that manage the rendering process and interact with the rendering backend.
Backend-Level: The actual rendering backend (like Vulkan) that executes the rendering commands based on the RIDs and the rendering state set by the engine.


> 🔧 **Assignment**
> - Read: https://docs.godotengine.org/en/stable/engine_details/architecture/internal_rendering_architecture.html to get a grasp how rendering works in Godot 4.x and how the scene graph nodes interact with the rendering backend through RIDs. Especially look at the [Core Rendering Classes Architecture image](https://docs.godotengine.org/en/stable/engine_details/architecture/internal_rendering_architecture.html#core-rendering-classes-architecture) to get an overview of the involved classes and their relationships.
> - Identify the classes in he above architecture image in the source code.
> - Look at how individual nodes like MeshInstance3D interact with the rendering backend using the RenderingServer class. Read the [Optimization using Servers](https://docs.godotengine.org/en/stable/tutorials/performance/using_servers.html) article to understand how the RenderingServer's functionality can be used to create "server side" representations of renderable resources.
> - Explain the role of the [`Instance`](https://github.com/godotengine/godot/blob/d569fcf207aea355ea9d0822255ad490945f5572/servers/rendering/renderer_scene_cull.h#L402) and the [`Scenario`](https://github.com/godotengine/godot/blob/d569fcf207aea355ea9d0822255ad490945f5572/servers/rendering/renderer_scene_cull.h#L327) classes in the rendering server (defined in the [render_scene_cull.h] file)
- How is the cumulated transformation of nested nodes handled in the rendering process? Look at how the transformation of a MeshInstance3D is calculated and how it interacts with the rendering backend. Does the `Instance`'s [`tranform` property](https://github.com/godotengine/godot/blob/d569fcf207aea355ea9d0822255ad490945f5572/servers/rendering/renderer_scene_cull.h#L412) contain a cumulative transformation of the node and its parents, or is it just the local transformation of the node?

#### Sound (?)

> 🔧 **Assignment**

> - Look at how sound processing is handled in the main loop.
> - Identify the relevant classes and functions that manage sound processing in Godot.
> - What steps are involved in processing sound each frame


