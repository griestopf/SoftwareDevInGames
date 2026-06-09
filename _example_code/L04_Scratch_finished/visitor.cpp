#include "visitor.h"

#include "node3d.h"
#include "meshinstance3d.h"

void Visitor::visit(Node3D *node3D)
{

}

void Visitor::visit(MeshInstance3D *mi3D)
{

}


// RENDERER //////////////////////////////////////////

void Renderer::visit(Node3D *node3D)
{
    std::cout << "Rendering node: "  << node3D->getName() << std::endl;
}

void Renderer::visit(MeshInstance3D *mi3D)
{
    if (mi3D->getMesh().get() == nullptr)
    {
        std::cout << "No mesh today!" << std::endl;
    }
    else
    {
        std::cout << "Rendering Mesh: " << mi3D->getMesh().get()->getName() << std::endl;
    }
}



// SERIALIZER //////////////////////////////////////////

void Serializer::visit(Node3D *node3D)
{
    std::cout << "Now serializing: "  << node3D->getName() << std::endl;
}

void Serializer::visit(MeshInstance3D *mi3D)
{
    if (mi3D->getMesh().get() == nullptr)
    {
        std::cout << "No mesh today!" << std::endl;
    }
    else
    {
        std::cout << "Serilaizing a Mesh: " << mi3D->getMesh().get()->getName() << std::endl;
    }
}
