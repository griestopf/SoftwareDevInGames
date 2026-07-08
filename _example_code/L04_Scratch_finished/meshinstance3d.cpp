#include "meshinstance3d.h"

void MeshInstance3D::setMesh(Ref<Mesh> new_mesh)
{
    mesh = new_mesh;
}

Ref<Mesh> MeshInstance3D::getMesh()
{
    return mesh;
}

void MeshInstance3D::accept(Visitor *visitor)
{
    visitor->visit(this);
    visitChildren(visitor);
}

