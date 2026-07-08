#ifndef REF_H
#define REF_H

template <typename T>
class Ref
{
public:
    Ref(T *p)
    {
        pt_to_t = p;
        if (pt_to_t)
            pt_to_t->_ref();
    }

    // TODO!!
    Ref(Ref &r)
    {
        pt_to_t = r.pt_to_t;
        if (pt_to_t)
            pt_to_t->_ref();
    }

    Ref &operator = (const Ref &r)
    {
       pt_to_t = r.pt_to_t;
       if (pt_to_t)
           pt_to_t->_ref();
       return *this;     
    }


    Ref()
    {
        pt_to_t = NULL;
    }

    ~Ref()
    {
        if (pt_to_t)
            pt_to_t->_unref();
    }

    Ref &operator = (T *p)
    {
        if (p != pt_to_t)
        {
            if (pt_to_t)
            {
                pt_to_t->_unref();
            }
            pt_to_t = p;
            if (pt_to_t)
                pt_to_t->_ref();
        }
        return *this;
    }

    T *operator->()
    {
        return pt_to_t;
    }

private:
    T *pt_to_t;
};

#endif
