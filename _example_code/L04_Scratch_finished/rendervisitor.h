#ifndef RENDERVISITOR_H
#define RENDERVISITOR_H

#include "visitor.h"


class RenderVisitor : public Visitor
{
public:
    virtual void visit(Node3D *node);
    virtual void visit(MeshInstance3D *mi3d);
    // ... and 150 more...
};


#endif
