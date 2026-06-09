#ifndef NODE3D_H
#define NODE3D_H

#include "object.h"
#include <unordered_map>
#include <string>


class Visitor;

class Node3D : public Object
{
public:
    Node3D();
    Node3D(const std::string &new_name);

    ~Node3D();

    void addChild(Node3D *child);
    // get a child by name
    Node3D *getChild(const std::string &child_name);

    // remove a child by name
    void removeChild(const std::string &child_name);

    virtual void accept(Visitor *visitor);    

protected:
    void visitChildren(Visitor *visitor);

private:
    std::unordered_map<std::string, Node3D *> children;
    // TODO: Add transformation properties.
};

#endif // NODE3D_H