#include "node3d.h"
#include <iostream>


void Node3D::addChild(Node3D *child)
{
    if (child) {
        children[child->getName()] = child;
    }
}

void Node3D::accept(Visitor *visitor)
{
    visitor->visit(this); // Dispatch Number 1:  Choose the "column": which concrete visitor type? 
    visitChildren(visitor);
}

void Node3D::visitChildren(Visitor *visitor)
{  
    for (auto ch = children.begin(); ch != children.end(); ch++)
    {
        ch->second->accept(visitor); // Dispatch Number 2: Choose the "row": which concrete node type?
    }
}
