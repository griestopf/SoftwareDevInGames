#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object {
public:
    Object();
    Object(const std::string &new_name) { setName(new_name); } 
    ~Object() {};

    std::string getName() const { return name; };
    void setName(const std::string &new_name) { name = new_name; }
private:
    std::string name;
};  


#endif // OBJECT_H