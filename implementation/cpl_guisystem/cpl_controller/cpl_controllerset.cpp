#include "cpl_controllerframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_ControllerSet
//-----------------------------------------------------------------------------
//
cpl_ControllerSet* cpl_ControllerSet::New() {
    return new cpl_ControllerSet();
}

//-----------------------------------------------------------------------------
int cpl_ControllerSet::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].controlItem != NULL) {
                    this->Array[i].controlItem->Release();
                    this->Array[i].controlItem = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbControllerItem_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].controlItem = NULL;;
             this->Array[i].resourceId = -1;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ControllerSet::InsertNextItem(cpl_Controller* control) {    
    //@@preconditions
    assert(control != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, control);
    return this->MaxId;
}

//-----------------------------------------------------------------------------
void cpl_ControllerSet::InsertItem(int pos, cpl_Controller* control) {
    //@@preconditions
    assert(pos >= 0);
    assert(control != NULL);
    //@@end preconditions

    _fbControllerItem_s * controls = NULL;

    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    controls = this->Array + pos;
    assert(controls != NULL);

    controls->controlItem = control;
    controls->resourceId = 0;

    return;
}

//-----------------------------------------------------------------------------
int cpl_ControllerSet::RemoveItem(cpl_Controller* control) {
    //@@preconditions
    assert(control != NULL);
    //@@end preconditions

    int controlId = -1;
    for (int i = 0; i < this->MaxId+1; i++) {
        if (this->Array[i].controlItem == control) {
            controlId = i;
            break;
        }
    }
    if (controlId == -1) {
        return 0;
    }
    //exchange position between lnId and MaxId.
    if (controlId != this->MaxId) {
        this->Array[controlId] = this->Array[this->MaxId];
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-----------------------------------------------------------------------------
int cpl_ControllerSet::RemoveAllItems(){
    for (int i = 0; i < this->MaxId+1; i++) {
        if (this->Array[i].controlItem != NULL) {
            this->Array[i].controlItem->Release();
            this->Array[i].controlItem = NULL;
        }
    }
    this->MaxId = -1;
    return 1;
}
       
//-----------------------------------------------------------------------------
void cpl_ControllerSet::DoCleanup() {
    for (int i = 0; i < this->MaxId+1; i++) {
        if (this->Array[i].controlItem != NULL) {
            this->Array[i].controlItem->DoCleanup();
        }
    }
}

//-----------------------------------------------------------------------------
cpl_ControllerSet::_fbControllerItem_s* cpl_ControllerSet::Resize(int sz) {
    //@@preconditions
    assert(sz > 0);
    //@@end preconditions

    int newSize = 0;
    if (sz >= this->Size) {
        newSize = this->Size + sz;
    }
    else {
        assert(0);
        newSize = sz;
    }

    _fbControllerItem_s * newArray = new _fbControllerItem_s[newSize];

    for (int j = 0; j < newSize; j++) {
        newArray[j].controlItem = NULL;
        newArray[j].resourceId = 0;
    }
    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].controlItem = this->Array[i].controlItem;
        newArray[i].resourceId  = this->Array[i].resourceId;
    }

    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;

    return this->Array;
}

//-----------------------------------------------------------------------------
cpl_ControllerSet::cpl_ControllerSet() {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_ControllerSet::~cpl_ControllerSet(){
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].controlItem != NULL) {
                this->Array[i].controlItem->Release();
                this->Array[i].controlItem = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}
