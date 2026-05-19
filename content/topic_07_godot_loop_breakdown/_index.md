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


#### Physics

Physics is fixed-step, so it can run zero, one, or multiple times per rendered frame, depending on the accumulated time and the `max_physics_steps` setting. This is handled at the [for-loop early stage in the iteration function (main/main.cpp#L4966)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L4966). In this loop, it checks how much time has accumulated and runs the physics steps accordingly. A single physics step involves calling [`MainLoop::physics_process(double p_time)` (main/main.cpp#L4997)](https://github.com/godotengine/godot/blob/ef02314f2bd0305035ecbe907883401a393da7a7/main/main.cpp#L4997), which in turn calls `_process(true)` to process all nodes that have physics processing enabled.


**Assignment** - Inspect the for-loop and identify how a constant frame rate for physics updates is maintained!


#### Processing

After the physics steps, the main iteration calls [MainLoop::process(double p_time)](main/main.cpp#L5008), which calls `_process(false)` to process all nodes that have regular processing enabled. This is where the game logic updates happen for each frame.

Interestingly, this _process call ends up in the same [SceneTree::_process()](scene\main\scene_tree.cpp#L1239) function that is used for both physics and regular processing, but it distinguishes between them using a boolean parameter.

**Assignemnt** Inspect the [SceneTree::_process()](scene\main\scene_tree.cpp#L1239) function and try to grasp how it differentiates between physics processing and regular processing. Identify the places that determine the behavior based on the boolean parameter. 


The `_process()` function does not traverse the entire scene graph. Instead, it uses cached lists of nodes that have processing enabled. This means that only the nodes that need to be processed are visited, which can improve performance.

