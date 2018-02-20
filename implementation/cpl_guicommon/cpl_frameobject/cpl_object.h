#ifndef CPL_OBJECT_H
#define CPL_OBJECT_H

class cpl_Object: public cpl_ObjectBase {

public:
    /** create object and reference count = 1. */
    static cpl_Object * New();

    /** return class name as string. */
    virtual const char * GetClassName() { return "cpl_Object"; }

protected:
    // constructor.
    cpl_Object();

    // destructor.
    virtual ~cpl_Object();
};

#endif //CPL_OBJECT_H
