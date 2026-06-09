#ifndef MESH_H
#define MESH_H

#include "refcounted.h"

class Mesh : public RefCounted {
public:
    Mesh();
    Mesh(std::string new_name);
    ~Mesh();

    // TODO implement mesh data such as vertices, indices, normals, etc.
};


#endif // MESH_H