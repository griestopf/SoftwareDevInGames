#ifndef MESHINSTANCE3D_H
#define MESHINSTANCE3D_H

#include <iostream>

#include "node3d.h"
#include "mesh.h"
#include "ref.h"

class MeshInstance3D : public Node3D
{
public:
    MeshInstance3D();
    MeshInstance3D(const std::string &new_name) : Node3D(new_name) {};
    ~MeshInstance3D() {};

    void setMesh(Ref<Mesh> new_mesh);
    Ref<Mesh> getMesh();

    virtual void accept(Visitor *visitor);

private:
    Ref<Mesh> mesh;
};

#endif // MESHINSTANCE3D_H
