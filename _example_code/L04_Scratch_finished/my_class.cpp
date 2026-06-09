#include <iostream>

#include "my_class.h"

// Implementation of MyClass
// Informationen, die zur Laufzeit nötig sind
MyClass::MyClass(int value)  {
    some_value = value;
    std::cout << "MyClass constructor called!" << std::endl;
}

void MyClass::some_method()
{
    std::cout << "Greetings from MyClass! some_value is: " << some_value << std::endl;
}

MyClass::~MyClass() {
    std::cout << "MyClass destructor called!" << std::endl;
}
