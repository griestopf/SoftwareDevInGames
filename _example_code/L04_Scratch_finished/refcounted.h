#ifndef REFCOUNTED_H
#define REFCOUNTED_H

#include "object.h"

class RefCounted : public Object
{
public:
    RefCounted(const std::string &new_name) : Object(new_name)
    {
        counter = 0;
    }

    RefCounted() : Object()
    {
        counter = 0;
    }

    virtual ~RefCounted()
    {

    }

    void _ref()
    {
        counter++;
    }

    void _unref()
    {
        counter--;
        if (counter <= 0)
        {
            delete this;
        }
    }
private:
    int counter;
};



#endif