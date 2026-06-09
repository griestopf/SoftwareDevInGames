#include "meshinstance3d.h"

#include "visitor.h"

MeshInstance3D::MeshInstance3D(const std::string &new_name) : Node3D(new_name) {
    // std::cout << "MeshInstance3D constructor called!" << std::endl;
}

MeshInstance3D::~MeshInstance3D() {
    // std::cout << "MeshInstance3D destructor called!" << std::endl;
}

Ref<Mesh> MeshInstance3D::getMesh() {
    return mesh;
}

void MeshInstance3D::setMesh(Ref<Mesh> new_mesh) {
    mesh = new_mesh;
}


void MeshInstance3D::accept(Visitor *visitor) 
{
    visitor->visit(this);
    visitChildren(visitor);
}
