#ifndef CPL_OBJECTBASE_H
#define CPL_OBJECTBASE_H

class cpl_ObjectBase {

public:
    /** delete object directly, dangerously. */
    virtual void Delete();

    /** make a mark. */
    virtual void Modified();

    /** increase reference count. */
    virtual unsigned long AddReference();

    /** decrease reference count, if reference count == 0, then destory this object. */
    virtual unsigned long Release();

    /** get the current reference count. */
    virtual unsigned long GetReference();

    /** return this object's modified time. */
    virtual unsigned long GetMTime();

protected:
    // constructor.
    cpl_ObjectBase();

    // destructor.
    virtual ~cpl_ObjectBase();

private:
    // reference count.
    unsigned long ReferenceCount;

    // timestamp.
    cpl_TimeStamp MTime;
};

#endif //CPL_OBJECTBASE_H
