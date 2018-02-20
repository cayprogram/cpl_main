#ifndef CPL_OBJECTFACTORYPOOL_H
#define CPL_OBJECTFACTORYPOOL_H

/** @stereotype container */
class cpl_ObjectFactoryPool : public cpl_Object {

public:
    /** create instance */
    static cpl_ObjectFactoryPool* New();

public:
    /** get class name */
    virtual const char * GetClassName();

    /** insert new item */
    virtual int InsertItem(char* name, cpl_ObjectFactory* item);

    /** remove item */
    virtual int RemoveItem(char* name);
    
    /** remove all */
    virtual int RemoveAll();

    /** get number item */
    virtual int GetPoolSize() {return MAX_NUM_STACK; }

    /** get item */
    virtual cpl_ObjectFactory* GetItem(int i) {return this->m_objStackArray[i].FactoryStack; }

protected:
    //enum 
    enum { MAX_NUM_STACK = 10 };

    //inner structure.
    struct fbFactoryStacks {
        cpl_ObjectFactory* FactoryStack;
        char id[64];
        char used;
    };

    // constructor
    cpl_ObjectFactoryPool();

    // destructor
    virtual ~cpl_ObjectFactoryPool();
    
    fbFactoryStacks m_objStackArray[MAX_NUM_STACK];
};

#endif //CPL_OBJECTFACTORYPOOL_H
