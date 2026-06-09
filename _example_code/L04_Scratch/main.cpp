#include <iostream>
#include <memory>
#include "meshinstance3d.h"


int main() {

    std::cout << "Starting scene graph demo." << std::endl;

    ///////////////////////////////////////////////////////////////////////
    // STEP 1
    // Set up a scene graph using Node3D and MeshInstance3D objects
    //
    // root
    // |- child1
    // |   |- grandChild1
    // |   |- grandChild2
    // |- child2
    //     |- grandChild3
    //
    // TODO: Implement the Node3D and MeshInstance3D classes with basic 
    //       functionality to create this scene graph structure.
    // - Create a base class Object allowing objects to have a name.
    // - Create a Node3D class that can have child nodes (addChild).
    // - allow children to be associated with a name.
    
    /*
    Node3D* root = new Node3D("Root");
    
    Node3D* child1 = new Node3D("Child1");
    MeshInstance3D* child2 = new MeshInstance3D("Child2");
    root->addChild(child1);
    root->addChild(child2);

    MeshInstance3D* grandChild1 = new MeshInstance3D("GrandChild1");
    child1->addChild(grandChild1);

    MeshInstance3D* grandChild2 = new MeshInstance3D("GrandChild2");
    child1->addChild(grandChild2);

    Node3D* grandChild3 = new Node3D("GrandChild3");
    child2->addChild(grandChild3);
    */


    ///////////////////////////////////////////////////////////////////////
    // STEP 2
    // Insert references to Mesh objects into the scene graph. Implement the reference counting mechanism to allow
    // multiple MeshInstance3D objects to share the same Mesh resource without memory leaks or dangling pointers.
    // Make grandChild1 and child2 share the same Mesh resource, while grandChild2 has its own Mesh resource.
    // 
    // TODO: As a first iteration, implement a simple reference counting mechanism (e.g., using std::shared_ptr) to manage Mesh resources.
    // In the end, try to mimic Godot's Ref<T> behavior as closely as possible, including copy semantics and automatic cleanup when no longer referenced.
    // This will require implementing a custom Ref<T> class that manages reference counting and resource cleanup, and a RefCounded base class 
    // that Mesh (and other resources) can inherit from to enable reference counting.
    /*
    Ref<Mesh> mesh1 = Ref<Mesh>(new Mesh("Mesh1"));
    grandChild1->setMesh(mesh1);

    Ref<Mesh> mesh2 = Ref<Mesh>(new Mesh("Mesh2"));
    grandChild2->setMesh(mesh2);
    child2->setMesh(mesh2);
    */

    ///////////////////////////////////////////////////////////////////////
    // STEP 3
    // Implement a simple rendering traversal that traverses the scene graph and renders each MeshInstance3D using the shared Mesh resources.
    //
    // TODO: Implement a polymorphic render() method in Node3D and MeshInstance3D. The render() method in Node3D should call render() on its children,
    // while the render() method in MeshInstance3D should output the name of the mesh it is rendering (e.g., "Rendering Mesh1").
    /*
    root->render();
    */

    ///////////////////////////////////////////////////////////////////////
    // STEP 4
    // Enable for scene graph traversals other than rendering, such as serialization or physics updates, without modifying the Node3D and MeshInstance3D classes.
    //
    // TODO: Implement the Visitor pattern to allow different operations (e.g., rendering, serialization) to be performed on the scene graph 
    // without modifying the node classes.
  
    /*
    Renderer *renderer = new Renderer();
    root->accept(renderer);

    Serializer *serializer = new Serializer();
    root->accept(serializer);
    */
    std::cout << "Scene graph demo complete." << std::endl;
    return 0;
}
