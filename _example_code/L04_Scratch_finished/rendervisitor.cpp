#include "rendervisitor.h"

#include "node3d.h"
#include "meshinstance3d.h"

void RenderVisitor::visit(Node3D *node)
{
    std::cout << "Rendering Node3D: " + node->getName() << std::endl;
}

void RenderVisitor::visit(MeshInstance3D *mi3d)
{
    std::cout << "Rendering Node: " << mi3d->getName() << " with Mesh: " << mi3d->getMesh()->getName() << std::endl;
}
