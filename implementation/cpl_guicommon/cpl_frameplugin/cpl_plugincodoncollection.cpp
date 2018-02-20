#include "cpl_pluginframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginCodonCollection);

//-------------------------------------------------------------------------
// class cpl_PluginCodonCollection
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
int cpl_PluginCodonCollection::GetNumberOfItem() {
    return this->MaxId+1;
}

//-------------------------------------------------------------------------
int cpl_PluginCodonCollection::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].item != NULL) {
                    this->Array[i].item->Release();
                    this->Array[i].item = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbCodon_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].item = NULL;;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-------------------------------------------------------------------------
int cpl_PluginCodonCollection::InsertNextItem(cpl_PluginCodon* codon) {
    //@@preconditons
    assert(codon != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, codon);
    return this->MaxId;
}

//-------------------------------------------------------------------------
void cpl_PluginCodonCollection::InsertItem(int pos, cpl_PluginCodon* codon) {
    //@@preconditoins
    assert(pos >= 0);
    assert(codon != NULL);
    //@@end preconditons

    _fbCodon_s * items = NULL;
    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    items = this->Array + pos;
    assert(items != NULL);
    items->item = codon;
}

//-------------------------------------------------------------------------
int cpl_PluginCodonCollection::RemoveItem(cpl_PluginCodon* codon) {
    //@@preconditions
    assert(codon != NULL);
    assert(this->Array != NULL);
    //@@end preconditions

    int id = -1;
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].item == codon) {
            this->Array[i].item = NULL;
            id = i;
            break;
        }
    }
    assert(id != -1);
    if (id != this->MaxId) {
        this->Array[id] = this->Array[this->MaxId];
    }
    this->MaxId--;
    return this->MaxId;
}
    
//-------------------------------------------------------------------------
int cpl_PluginCodonCollection::RemoveAllItems(){
    for (int i = 0; i < this->MaxId + 1; i++) {
        if (this->Array[i].item != NULL) {
            this->Array[i].item->Release();
            this->Array[i].item = NULL;
        }
    }
    this->MaxId = -1;
    return this->MaxId;
}

//-------------------------------------------------------------------------
cpl_PluginCodonCollection::_fbCodon_s* cpl_PluginCodonCollection::Resize(int sz) {
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

    cpl_PluginCodonCollection::_fbCodon_s * newArray = new cpl_PluginCodonCollection::_fbCodon_s[newSize];
    for (int j = 0; j < newSize; j++) {
        newArray[j].item = NULL;
    }
    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].item = this->Array[i].item;
    }

    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;
    return this->Array;
}

//-------------------------------------------------------------------------
int cpl_PluginCodonCollection::GetNextItem(cpl_PluginCodon*& codon) {
    //@@preconditions
    assert(this->Array != NULL);
    //@@end preconditions

    if (this->TraversalPos > this->MaxId) {
        return 0;
    }
    codon = this->Array[this->TraversalPos++].item;
    return 1;
}

//-------------------------------------------------------------------------
cpl_PluginCodonCollection::cpl_PluginCodonCollection(){
    this->Array  =  NULL;
    this->MaxId  = -1;
    this->Size   =  0;
    this->Extend =  5;
    this->TraversalPos = 0;
}

//-------------------------------------------------------------------------
cpl_PluginCodonCollection::~cpl_PluginCodonCollection() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].item != NULL) {
                this->Array[i].item->Release();
                this->Array[i].item = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}
