#include "mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(std::string new_name) : RefCounted(new_name) {

}   

// TODO: Check if Mesh destructor is called by Refcounted::unreference().
Mesh::~Mesh() {

}