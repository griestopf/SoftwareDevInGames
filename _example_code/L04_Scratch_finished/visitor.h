#ifndef VISITOR_H
#define VISITOR_H

#include "meshinstance3d.h"


class Node3D;
class MeshInstance3D;

class Visitor
{
public:
    virtual void visit(Node3D *node3D);
    virtual void visit(MeshInstance3D *mi3D);
};


class Renderer : public Visitor
{
public:
    virtual void visit(Node3D *node3D);
    virtual void visit(MeshInstance3D *mi3D);
};


class Serializer : public Visitor
{
public:
    virtual void visit(Node3D *node3D);
    virtual void visit(MeshInstance3D *mi3D);
};


#endif