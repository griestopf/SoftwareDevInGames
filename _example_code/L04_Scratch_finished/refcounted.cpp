#include "refcounted.h"
#include <iostream>

// Constructor
// TODO: Check if the reference count must be initialized to 1 or 0.
RefCounted::RefCounted() : ref_count(1) {
    // std::cout << "RefCounted constructor called!" << std::endl;
}

RefCounted::RefCounted(std::string new_name) : Object(new_name), ref_count(1) {
    // std::cout << "RefCounted constructor with name called!" << std::endl;
}

// Destructor
// TODO: Check if destructor of inherited classes is called.
RefCounted::~RefCounted() {
    // std::cout << "RefCounted destructor called!" << std::endl;
}

// Increment the reference count
void RefCounted::reference() {
    ++ref_count;
}

// Decrement the reference count and delete if it reaches zero
void RefCounted::unreference() {
    if (--ref_count == 0) {
        delete this;
    }
}

// Get the current reference count
int RefCounted::get_reference_count() const {
    return ref_count;
}

