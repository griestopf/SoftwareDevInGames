#include "node3d.h"
#include <iostream>

#include "visitor.h"

Node3D::Node3D()
{};

Node3D::Node3D(const std::string &new_name) : Object(new_name)
{};
    
Node3D::~Node3D()
{
    // Delete all children nodes#
    for (auto &child : children) {
        delete child.second; // Assuming ownership of the child
    }
};


void Node3D::addChild(Node3D *child) {
    if (child) {
        children[child->getName()] = child;
    }
}

// get a child by name
Node3D *Node3D::getChild(const std::string &child_name) {
    auto it = children.find(child_name);
    if (it != children.end()) {
        return it->second;
    }
    return nullptr; // Child not found
}

// remove a child by name
void Node3D::removeChild(const std::string &child_name) {
    auto it = children.find(child_name);
    if (it != children.end()) {
        delete it->second; // Assuming ownership of the child
        children.erase(it);
    }
}


void Node3D::accept(Visitor *visitor)
{
    visitor->visit(this);
    visitChildren(visitor);
}

void Node3D::visitChildren(Visitor *visitor)
{
    for (const auto &child : children) {
        child.second->accept(visitor); // Recursively render each child
    }
}
