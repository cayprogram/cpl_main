#include "cpl_frameobjectincludes.h"

//-----------------------------------------------------------------------------
// static declaration
//-----------------------------------------------------------------------------
//
cpl_ObjectFactoryPool * cpl_ObjectFactory::FactoryPool = NULL;

//-----------------------------------------------------------------------------
// class cpl_ObjectFactory
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
const char* cpl_ObjectFactory::GetClassName() {
    return "cpl_ObjectFactory";
}

//-----------------------------------------------------------------------------
cpl_Object* cpl_ObjectFactory::CreateObject(const char* classname) {
    for (int i = 0; i < this->OverrideArrayLength; i++) {
        if (this->OverrideArray[i].EnabledFlag && strcmp(this->OverrideClassNames[i], classname) == 0) {
            return (*this->OverrideArray[i].CreateCallback)();
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------
cpl_Object* cpl_ObjectFactory::CreateInstance(const char* classname) {
    //@@precondiitons
    assert(classname != NULL);
    assert(classname[0] != '\0');
    //@@end precondiitons

    ///initialize object factory pool.
    if (cpl_ObjectFactory::FactoryPool == NULL) {
        cpl_ObjectFactory::Init();
        assert(cpl_ObjectFactory::FactoryPool != NULL);
    }  

    ///create object from factory.
    int numSize = cpl_ObjectFactory::FactoryPool->GetPoolSize();
    for (int i = 0; i < numSize; i++) {
        cpl_ObjectFactory* factory = cpl_ObjectFactory::FactoryPool->GetItem(i);
        if (factory == NULL) {
            continue;
        }
        cpl_Object* newobject = factory->CreateObject(classname);
        if (newobject != NULL) {
            return newobject;
        }
    }
    return NULL;
}

//-----------------------------------------------------------------------------
void cpl_ObjectFactory::RegisterFactory(cpl_ObjectFactory* item) {
    //@@preconditions
    assert(item != NULL);
    //@@end preconditions

    cpl_ObjectFactory::Init();
    cpl_ObjectFactory::FactoryPool->InsertItem((char*)item->GetClassName(), item);
}

//-----------------------------------------------------------------------------
void cpl_ObjectFactory::UnRegisterFactory(cpl_ObjectFactory* item) {
    //@@preconditions
    assert(item != NULL);
    assert(cpl_ObjectFactory::FactoryPool != NULL);
    //@@end preconditions

    cpl_ObjectFactory::FactoryPool->RemoveItem((char*)item->GetClassName());
}

//-----------------------------------------------------------------------------
void cpl_ObjectFactory::UnRegisterAllFactories() {
    //@@preconditions
    assert(cpl_ObjectFactory::FactoryPool != NULL);
    //@@end precondiitons

    cpl_ObjectFactory::FactoryPool->RemoveAll();
}

//-----------------------------------------------------------------------------
void cpl_ObjectFactory::RegisterOverride(const char* classOverride, const char* subclass, const char* description, int enableFlag, CreateFunction createFunction) {
    //@@preconditions
    assert(classOverride != NULL);
    assert(description != NULL);
    assert(subclass != NULL);
    //@@end preconditions

    //adjust array.
    this->GrowOverrideArray();

    int nextIndex = this->OverrideArrayLength;
    this->OverrideArrayLength++;
    char* override = strcpy(new char[strlen(classOverride)+1], classOverride);
    char* desc = strcpy(new char[strlen(description)+1], description);
    char* ocn =  strcpy(new char[strlen(subclass)+1], subclass);
    this->OverrideClassNames[nextIndex]             = override;
    this->OverrideArray[nextIndex].Description      = desc;
    this->OverrideArray[nextIndex].OverrideWithName = ocn;
    this->OverrideArray[nextIndex].EnabledFlag      = enableFlag;
    this->OverrideArray[nextIndex].CreateCallback   = createFunction;
}

//-----------------------------------------------------------------------------
void cpl_ObjectFactory::Init() {
    if (cpl_ObjectFactory::FactoryPool != NULL) {
        return;
    }  
    cpl_ObjectFactory::FactoryPool = cpl_ObjectFactoryPool::New();
}

//-----------------------------------------------------------------------------
void cpl_ObjectFactory::DeInit() {
    if (cpl_ObjectFactory::FactoryPool == NULL) {
        return;
    }  
    cpl_ObjectFactory::FactoryPool->Release();
    cpl_ObjectFactory::FactoryPool = NULL;
}

//-----------------------------------------------------------------------------
void cpl_ObjectFactory::GrowOverrideArray() {
    if (this->OverrideArrayLength+1 > this->SizeOverrideArray) {
        int newLength = this->OverrideArrayLength + 50;
        OverrideInformation* newArray = new OverrideInformation[newLength];
        char** newNameArray = new char*[newLength];

        for (int i =0; i < this->OverrideArrayLength; i++) {
            newNameArray[i] = this->OverrideClassNames[i];
            newArray[i] = this->OverrideArray[i];
        }
        delete [] this->OverrideClassNames;
        this->OverrideClassNames = newNameArray;
        delete [] this->OverrideArray;
        this->OverrideArray = newArray;
    }
}

//-----------------------------------------------------------------------------
cpl_ObjectFactory::cpl_ObjectFactory() {
    this->OverrideArray       = 0;
    this->OverrideClassNames  = 0;
    this->SizeOverrideArray   = 0;
    this->OverrideArrayLength = 0;
}

//-----------------------------------------------------------------------------
cpl_ObjectFactory::~cpl_ObjectFactory() {
    for(int i = 0; i < this->OverrideArrayLength; i++) {
        delete [] this->OverrideClassNames[i];
        delete [] this->OverrideArray[i].Description;
        delete [] this->OverrideArray[i].OverrideWithName;
    }
    delete [] this->OverrideArray;
    delete [] this->OverrideClassNames;
    this->OverrideArray      = NULL;
    this->OverrideClassNames = NULL;
}
