#ifndef CPL_OBJECTFACTORY_H
#define CPL_OBJECTFACTORY_H

class cpl_ObjectFactory : public cpl_Object {

public:
    /** create instance */
    static cpl_Object* CreateInstance(const char* classname);

    /** intialization */
    static void Init();

    /** deintialization */
    static void DeInit();
    
    /** register factory */
    static void RegisterFactory(cpl_ObjectFactory* item);
    
    /** unregister factory */
    static void UnRegisterFactory(cpl_ObjectFactory* item);

    /** unregister all factories */
    static void UnRegisterAllFactories();

public:
    /** get class name */
    virtual const char * GetClassName();

    // create object 
    virtual cpl_Object* CreateObject(const char* classname );

protected:
    // constructor
    cpl_ObjectFactory();

    // destructor
    virtual ~cpl_ObjectFactory();    

    //protected variables.
    static cpl_ObjectFactoryPool* FactoryPool;

protected:
    typedef cpl_Object* (*CreateFunction)();
    
    //inner structure.
    struct OverrideInformation {
        char* Description;
        char* OverrideWithName;
        int EnabledFlag;
        CreateFunction CreateCallback;
    };

    OverrideInformation* OverrideArray;
    char** OverrideClassNames;
    int SizeOverrideArray;
    int OverrideArrayLength;
    
    // register object creation information with the factory.
    virtual void RegisterOverride(const char* classOverride, const char* overrideClassName, const char* description, int enableFlag, CreateFunction createFunction);

    // adjust override array.
    virtual void GrowOverrideArray();
};

#endif //CPL_OBJECTFACTORY_H
