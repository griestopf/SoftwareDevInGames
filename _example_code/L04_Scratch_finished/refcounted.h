#ifndef REFCOUNTED_H
#define REFCOUNTED_H

#include "object.h"

// TODO: Look, if the Godot implementation of RefCounted is different from this one. Especially look, 
// if incrementing and decrementing the reference count is done using methods like ref and unref.
class RefCounted : public Object {
public:
    RefCounted();
    RefCounted(std::string new_name);
    ~RefCounted();

    // Reference counting methods
    void reference();
    void unreference();  

    // Get the current reference count
    int get_reference_count() const;  
private:
    int ref_count;  // Reference count
};

#endif // REFCOUNTED_H