#include "cpl_plugintreeframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginTreePath);


//-----------------------------------------------------------------------------
// class cpl_PluginTreePath
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
cpl_PluginTreePath::cpl_PluginTreePath() : cpl_PluginTreeNode(NULL) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_PluginTreePath::cpl_PluginTreePath(cpl_PluginTreePath * pNode) : cpl_PluginTreeNode(pNode)  {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_PluginTreePath::~cpl_PluginTreePath() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].Item != NULL) {
                this->Array[i].Item->Release();
                this->Array[i].Item = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}

//-----------------------------------------------------------------------------
int cpl_PluginTreePath::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].Item != NULL) {
                    this->Array[i].Item->Release();
                    this->Array[i].Item = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbNodetem_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].Item = NULL;
             this->Array[i].resourceId = 0;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_PluginTreePath::InsertNextItem(IPluginTreeNode* node) {    
    //@@preconditons
    assert(node != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, (cpl_PluginTreeNode*)node);
    return this->MaxId;
}

//-----------------------------------------------------------------------------
int cpl_PluginTreePath::RemoveItem(IPluginTreeNode* node) {
    //@@preconditions
    assert(node != NULL);
    //@@end preconditions

    int id = -1;
    for (int i = 0; i <= this->MaxId; i++) {
        if (this->Array[i].Item == node) {
            id = i;
            break;
        }
    }
    assert(id != -1);

    //exchange position between lnId and MaxId, note: widget is not delete.
    if (id != this->MaxId) {
        this->Array[id] = this->Array[this->MaxId];
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-----------------------------------------------------------------------------
int cpl_PluginTreePath::RemoveAllItems(){
    for (int i = 0; i <= this->MaxId; i++) {
        if (this->Array[i].Item != NULL) {
            this->Array[i].Item->Release();
            this->Array[i].Item = NULL;
        }
    }
    this->MaxId = -1;
    return 1;
}

//-----------------------------------------------------------------------------
void cpl_PluginTreePath::InsertItem(int pos, cpl_PluginTreeNode* node) {
    //@@preconditions
    assert(pos >= 0);
    assert(node != NULL);
    //@@end preconditions

    _fbNodetem_s * nodes;
    if (pos >= this->Size) {
        this->Reallocate(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    nodes = this->Array + pos;
    assert(nodes != NULL);

    nodes->Item = node;
    nodes->resourceId = 0;

    //set as parent.
    nodes->Item->SetParent(this);
}
 
//-----------------------------------------------------------------------------
cpl_PluginTreePath::_fbNodetem_s* cpl_PluginTreePath::Reallocate(int sz) {
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

    cpl_PluginTreePath::_fbNodetem_s * newArray = new cpl_PluginTreePath::_fbNodetem_s[newSize];

    for (int j = 0; j < newSize; j++) {
        newArray[j].Item = NULL;
        newArray[j].resourceId = 0;
    }

    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].Item = this->Array[i].Item;
        newArray[i].resourceId = this->Array[i].resourceId;
    }
    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;
    return this->Array;
}

//-----------------------------------------------------------------------------
int cpl_PluginTreePath::GetNumberOfNestItems() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItem(this);
}

//-----------------------------------------------------------------------------
int cpl_PluginTreePath::GetNestSubItem(cpl_PluginTreePath* path) {
    //@@preconditions
    assert(path != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = path->GetNumberOfNestItems();
    for (int i = 0; i < numItem ; i++) {
        cpl_PluginTreeNode* node = path->GetItemA(i);
        if (node->IsComposite() == 1) {
            count += this->GetNestSubItem((cpl_PluginTreePath*)node);
        }
        else {
            count++;
        }        
    }
    return count;
}

//-----------------------------------------------------------------------------
IPluginTreeNode* cpl_PluginTreePath::GetItem(char* subID) {
    //@@preconditions
    assert(subID != NULL);
    //@@end preconditions

    for (int i = 0; i <= this->MaxId; i++) {
        const char* name = this->Array[i].Item->GetName();
        if (strcmp(subID, name) == 0) {
            return this->Array[i].Item;
        }
    }
    return NULL;    
}

//-----------------------------------------------------------------------------
IPluginTreeNode* cpl_PluginTreePath::GetItem(IPluginCodon* subID) {
    //@@preconditions
    assert(subID != NULL);
    //@@end preconditions

    for (int i = 0; i <= this->MaxId; i++) {
        if (this->Array[i].Item->GetCodon() == subID) { 
            return this->Array[i].Item;
        }
    }
    return NULL;    
}

//-------------------------------------------------------------------------
cpl_PluginTreeNode* cpl_PluginTreePath::GetItemA(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfItems());
    assert(this->Array != NULL);
    //@@end preconditons
    
    return this->Array[pos].Item;    
}

//-----------------------------------------------------------------------------
cpl_PluginTreeNode* cpl_PluginTreePath::GetItemA(char* subID) {
    //@@preconditions
    assert(subID != NULL);
    //@@end preconditions

    for (int i = 0; i <= this->MaxId; i++) {
        const char* name = this->Array[i].Item->GetName();
        if (strcmp(subID, name) == 0) {
            return this->Array[i].Item;
        }
    }
    return NULL;    
}

//-----------------------------------------------------------------------------
void cpl_PluginTreePath::SetName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    cpl_PluginTreeNode::SetName(name);
}

//-----------------------------------------------------------------------------
const char* cpl_PluginTreePath::GetName() {
    return  cpl_PluginTreeNode::GetName();
}

//-----------------------------------------------------------------------------
void cpl_PluginTreePath::SetPath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) >= 0);
    //@@end preconditions

    cpl_PluginTreeNode::SetPath(path);
}

//-----------------------------------------------------------------------------
const char* cpl_PluginTreePath::GetPath() {
    return  cpl_PluginTreeNode::GetPath();
}

//-----------------------------------------------------------------------------
void cpl_PluginTreePath::SetUserData(const void* usrData) {
    //@@preconditions
    //@@end preconditions

    cpl_PluginTreeNode::SetUserData(usrData);
}

//-----------------------------------------------------------------------------
const void* cpl_PluginTreePath::GetUserData() {
    return  cpl_PluginTreeNode::GetUserData();
}

//-----------------------------------------------------------------------------
void cpl_PluginTreePath::SetCodon(IPluginCodon* codon) {
    //@@preconditions
    assert(codon != NULL);
    //@@end preconditions

    cpl_PluginTreeNode::SetCodon(codon);
}

//-----------------------------------------------------------------------------
IPluginCodon* cpl_PluginTreePath::GetCodon() {
    return cpl_PluginTreeNode::GetCodon();
}

//-----------------------------------------------------------------------------
void cpl_PluginTreePath::SetParent(IPluginTreePath* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    cpl_PluginTreeNode::SetParent(parent);
}
   
//-----------------------------------------------------------------------------
IPluginTreePath* cpl_PluginTreePath::GetParent() {
    return cpl_PluginTreeNode::GetParent();
}

