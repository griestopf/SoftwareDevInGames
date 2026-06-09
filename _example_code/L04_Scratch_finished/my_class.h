// # bedeutet Preprocessor-Direktive
#ifndef MY_CLASS_H
#define MY_CLASS_H

// Declaration of MyClass
// Informationen, die zur Compilezeit für den Compiler nötig sind
class MyClass {
    public:
        MyClass(int value);
        ~MyClass();
        int some_value;
        void some_method();
    };


#endif // MY_CLASS_H