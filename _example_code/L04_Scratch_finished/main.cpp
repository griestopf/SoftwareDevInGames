#include <iostream>
#include <memory>
#include "meshinstance3d.h"
#include "visitor.h"

int main() {

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

    Ref<Mesh> mesh1 = Ref<Mesh>(new Mesh("Mesh1"));
    grandChild1->setMesh(mesh1);

    Ref<Mesh> mesh2 = Ref<Mesh>(new Mesh("Mesh2"));
    grandChild2->setMesh(mesh2);
    child2->setMesh(mesh2);


    Renderer *renderer = new Renderer();
    root->accept(renderer);

    Serializer *serializer = new Serializer();
    root->accept(serializer);


    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
