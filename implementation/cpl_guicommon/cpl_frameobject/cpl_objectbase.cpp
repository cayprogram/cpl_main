#include "cpl_frameobjectincludes.h"

//-----------------------------------------------------------------------------
// cpl_ObjectBase
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void cpl_ObjectBase::Delete() {
    delete this;
}

//-----------------------------------------------------------------------------
unsigned long cpl_ObjectBase::GetReference() {
    return this->ReferenceCount;
}

//-----------------------------------------------------------------------------
unsigned long cpl_ObjectBase::AddReference() {
    this->ReferenceCount++;
    return this->ReferenceCount;
}

//-----------------------------------------------------------------------------
unsigned long cpl_ObjectBase::Release() {
    this->ReferenceCount--;
    if (this->ReferenceCount == 0) {
        delete this;
        return 0;
    }
    return this->ReferenceCount;
}

//-----------------------------------------------------------------------------
void cpl_ObjectBase::Modified() {
    this->MTime.Modified();
}

//-----------------------------------------------------------------------------
unsigned long cpl_ObjectBase::GetMTime() {
    return this->MTime.GetMTime();
}


cpl_ObjectBase::cpl_ObjectBase() {
    this->Modified();
    this->ReferenceCount = 1;
}

//-----------------------------------------------------------------------------
cpl_ObjectBase::~cpl_ObjectBase() {
    //@@preconditions.
    assert(this->ReferenceCount == 0);
    //@@end preconditions.
}
