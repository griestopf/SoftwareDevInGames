#ifndef MESH_H
#define MESH_H

#include "refcounted.h"

class Mesh : public RefCounted
{
public:
    Mesh(const std::string &new_name) : RefCounted(new_name)
    {}
    virtual ~Mesh()
    {}
};

#endif