#include "cpl_frameobjectincludes.h"

//-----------------------------------------------------------------------------
// class cpl_ObjectFactoryPool
//-----------------------------------------------------------------------------
//
cpl_ObjectFactoryPool* cpl_ObjectFactoryPool::New() {
    return new cpl_ObjectFactoryPool;
}

//-----------------------------------------------------------------------------
const char* cpl_ObjectFactoryPool::GetClassName() {
    return "cpl_ObjectFactoryPool";
}

//-----------------------------------------------------------------------------
int cpl_ObjectFactoryPool::InsertItem(char* name, cpl_ObjectFactory* item) {
    //@@preconditions
    assert(item != NULL);
    assert(name != NULL);
    assert(name[0] != '\0');
    //@@end preconditions

    {
        for (int i = 0; i < MAX_NUM_STACK; i++) {
            if (strcmp(this->m_objStackArray[i].id, name) == 0) {
                return 0;
            }
        }
    }

    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (this->m_objStackArray[i].used == 0) {
            this->m_objStackArray[i].FactoryStack = item; 
            this->m_objStackArray[i].used = 1;
            strcpy(this->m_objStackArray[i].id, name);
            return 1;
        }
    }
    assert(0);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_ObjectFactoryPool::RemoveItem(char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(name[0] != '\0');
    //@@end preconditions

    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (strcmp(this->m_objStackArray[i].id, name) == 0) {
            this->m_objStackArray[i].FactoryStack->Release();
            this->m_objStackArray[i].FactoryStack = NULL; 
            this->m_objStackArray[i].used = 0;
            this->m_objStackArray[i].id[0] ='\0';
            return 1;
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_ObjectFactoryPool::RemoveAll() {
    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (this->m_objStackArray[i].FactoryStack != NULL) {
            this->m_objStackArray[i].FactoryStack->Release();
            this->m_objStackArray[i].FactoryStack = NULL;
            this->m_objStackArray[i].used = 0;
            this->m_objStackArray[i].id[0] ='\0';
        }
    }
    return 1;
}

//-----------------------------------------------------------------------------
cpl_ObjectFactoryPool::cpl_ObjectFactoryPool() {
    for (int i = 0; i < MAX_NUM_STACK; i++) {
        this->m_objStackArray[i].FactoryStack = NULL;
        this->m_objStackArray[i].id[0] = '\0';
        this->m_objStackArray[i].used  = 0;
    }
}

//-----------------------------------------------------------------------------
cpl_ObjectFactoryPool::~cpl_ObjectFactoryPool() {
    for (int i = 0; i < MAX_NUM_STACK; i++) {
        if (this->m_objStackArray[i].FactoryStack != NULL) {
            this->m_objStackArray[i].FactoryStack->Release();
            this->m_objStackArray[i].FactoryStack = NULL;
        }
    }
}
