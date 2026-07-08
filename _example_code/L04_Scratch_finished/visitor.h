#ifndef VISITOR_H
#define VISITOR_H

class Node3D;
class MeshInstance3D;

class Visitor
{
public:
    virtual void visit(Node3D *node) = 0;
    virtual void visit(MeshInstance3D *mi3d) =0;
    // ... and 150 more...

};


#endif
