#ifndef REF_H
#define REF_H

#include "refcounted.h"

template <typename T>
class Ref
{
    T *reference;

public:
    Ref(T *p_reference = nullptr) : reference(p_reference)
    {
        if (reference)
        {
            reference->reference();
        }
    }

    Ref(const Ref &p_ref) : reference(p_ref.reference)
    {
        if (reference)
        {
            reference->reference();
        }
    }

    ~Ref()
    {
        if (reference)
        {
            reference->unreference();
        }
    }

    Ref &operator=(const Ref &p_ref)
    {
        if (this != &p_ref)
        {
            if (reference)
            {
                reference->unreference();
            }
            reference = p_ref.reference;
            if (reference)
            {
                reference->reference();
            }
        }
        return *this;
    }

    T *get() const { return reference; }
};
#endif // REF_H