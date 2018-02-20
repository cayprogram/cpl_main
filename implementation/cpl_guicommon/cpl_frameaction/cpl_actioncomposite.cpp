#include "cpl_actionframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_ActionComposite
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int cpl_ActionComposite::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].actionItem != NULL) {
                    delete this->Array[i].actionItem;
                    this->Array[i].actionItem = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbActionItem_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].actionItem = NULL;;
             this->Array[i].resourceId = 0; 
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ActionComposite::InsertNextItem(cpl_Action* action) {    
    //@@preconditons
    assert(action != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, action);

    return this->MaxId;
}

//-----------------------------------------------------------------------------
void cpl_ActionComposite::InsertItem(int pos, cpl_Action* action) {
    //@@preconditoins
    assert(pos >= 0);   
    assert(action != NULL);
    //@@end preconditons

    _fbActionItem_s * actions = NULL;

    if (pos >= this->Size) {
        this->Resize(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    actions = this->Array + pos;
    assert(actions != NULL);

    actions->actionItem = action;
    actions->resourceId = 0;
}

//-----------------------------------------------------------------------------
int cpl_ActionComposite::RemoveItem(cpl_Action* action) {
    //@@preconditions
    assert(action != NULL);
    assert(this->Array != NULL);
    //@@end preconditions

    int actionId = -1;
    for (int i = 0; i < this->MaxId+1; i++) {
        if (this->Array[i].actionItem == action) {
            actionId = i;
            break;
        }
    }
    assert(actionId != -1);

    //exchange position between lnId and MaxId.
    if (actionId != this->MaxId) {
        this->Array[actionId] = this->Array[this->MaxId];
    }
    this->MaxId--;

    return this->MaxId;
}
 
//-----------------------------------------------------------------------------
int cpl_ActionComposite::RemoveAllItems(){
    for (int i = 0; i < this->MaxId+1; i++) {
        if (this->Array[i].actionItem != NULL) {
            delete this->Array[i].actionItem;
            this->Array[i].actionItem = NULL;
        }
    }
    this->MaxId = -1;
    return 1;
}
 
//-----------------------------------------------------------------------------
int cpl_ActionComposite::IsExist(cpl_Action* action) {
    for (int i = 0; i < this->MaxId+1; i++) {
        if (this->Array[i].actionItem == action) {
            return i;
        }
    }
    return -1;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite::_fbActionItem_s* cpl_ActionComposite::Resize(int sz) {
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

    cpl_ActionComposite::_fbActionItem_s * newArray = new cpl_ActionComposite::_fbActionItem_s[newSize];

    for (int j = 0; j < newSize; j++) {
        newArray[j].actionItem = NULL;
        newArray[j].resourceId = 0;
    }
    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].actionItem = this->Array[i].actionItem;
        newArray[i].resourceId = this->Array[i].resourceId;
    }

    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;

    return this->Array;
}

//-----------------------------------------------------------------------------
int cpl_ActionComposite::GetNumberOfNestSubActions() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubActions(this);
}

//-----------------------------------------------------------------------------
int cpl_ActionComposite::PutItemAtFirst(cpl_Action* action) {
    //@@preconditions
    assert(action != NULL);
    //@@end preconditions

    int pos = -1, i = 0;
    for (i = 0; i < this->MaxId+1; i++) {
        if (this->Array[i].actionItem == action) {
            pos = i;
            break;
        }
    }
    assert(pos != -1);

    _fbActionItem_s* tmpArray = new _fbActionItem_s[this->MaxId+1];
    assert(tmpArray != NULL);

    int count = 1;
    for (i = 0; i < this->MaxId+1; i++) {
        if (i == pos) {
            tmpArray[0].actionItem = this->Array[i].actionItem;
            tmpArray[0].resourceId = this->Array[i].resourceId;
            continue;
        }
        tmpArray[count].actionItem = this->Array[i].actionItem;
        tmpArray[count].resourceId = this->Array[i].resourceId;
        count++;
    }
    for (i = 0; i < this->MaxId+1; i++) {
        this->Array[i].actionItem = tmpArray[i].actionItem;
        this->Array[i].resourceId = tmpArray[i].resourceId;
    }
    delete[] tmpArray;

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ActionComposite::GetNestSubActions(cpl_ActionComposite* pAction) {
    int count = 1;
    int numItem = pAction->GetNumberOfSubActions();
    for (int i = 0; i < numItem ; i++) {
        cpl_Action* subAction = pAction->GetAction(i);
        assert(subAction != NULL);

        if (subAction->IsComposite() == 1) {
            count += pAction->GetNestSubActions((cpl_ActionComposite*)subAction);
        }
        else {
            count ++;
        }        
    }
    return count+1;
}

//-----------------------------------------------------------------------------
cpl_Action* cpl_ActionComposite::FindSpecificItem(const char* name) {
    //@@preconditions
    assert(name != NULL);
    //@@end preconditions

    return this->FindSpecificItemInNestSubActions(name, this);
}

//-----------------------------------------------------------------------------
cpl_Action* cpl_ActionComposite::FindSpecificItem(int cmdId) {
    //@@preconditions
    assert(cmdId != 0);
    //@@end preconditions

    return this->FindSpecificItemInNestSubActions(cmdId, this);
}

//-----------------------------------------------------------------------------
cpl_Action* cpl_ActionComposite::FindSpecificItemInNestSubActions(const char* name, cpl_ActionComposite* pAction) {
    //@@preconditions
    assert(name != NULL);
    assert(pAction != NULL);
    //@@end preconditions

    int numItem = pAction->GetNumberOfSubActions();
    for (int i = 0; i < numItem ; i++) {
        cpl_Action* subAction = pAction->GetAction(i);
        assert(subAction != NULL);

        if (strcmp(subAction->GetText(), name) == 0) {
            return subAction;
        }
        if (subAction->IsComposite() == 1) {
            cpl_Action* _action = pAction->FindSpecificItemInNestSubActions(name, (cpl_ActionComposite*)subAction);
             if (_action != NULL) {
                 return _action;
             }
             continue;
        }
    }
    return NULL;
}

//-----------------------------------------------------------------------------
cpl_Action* cpl_ActionComposite::FindSpecificItemInNestSubActions(int id, cpl_ActionComposite* pAction) {
    //@@preconditions
    assert(pAction != NULL);
    //@@end preconditions

    int numItem = pAction->GetNumberOfSubActions();
    for (int i = 0; i < numItem ; i++) {
        cpl_Action* subAction = pAction->GetAction(i);
        assert(subAction != NULL);

        if (subAction->GetCommandId() == id) {
            return subAction;
        }
        if (subAction->IsComposite() == 1) {
             cpl_Action* _action = pAction->FindSpecificItemInNestSubActions(id, (cpl_ActionComposite*)subAction);
             if (_action != NULL) {
                 return _action;
             }
             continue;
        }
    }
    return NULL;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite& cpl_ActionComposite::operator+=(cpl_Action* action) {
    //@@preconditions
    assert(action != NULL);
    //@@end preconditions

    this->InsertNextItem(action);
    return *this;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite& cpl_ActionComposite::operator-=(cpl_Action* action) {
    //@@preconditions
    assert(action != NULL);
    //@@end preconditions

    this->RemoveItem(action);
    return *this;
}

//-----------------------------------------------------------------------------
int cpl_ActionComposite::IsComposite() {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ActionComposite::GetNumberOfSubActions() {
    return this->MaxId + 1;
}

//-----------------------------------------------------------------------------
cpl_Action* cpl_ActionComposite::GetAction(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfSubActions());
    assert(this->Array != NULL);
    //@@end preconditons
    
    return this->Array[pos].actionItem;    
}

//-----------------------------------------------------------------------------
cpl_ActionComposite::cpl_ActionComposite() : cpl_Action(NULL) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite::cpl_ActionComposite(cpl_ActionComposite * pAction) : cpl_Action(pAction)  {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite::cpl_ActionComposite(const char* text, const char* shortcut, int enable, int type, int cmdid, void * userdata, cpl_ActionComposite* parent) : cpl_Action(text, shortcut, enable, type, cmdid, userdata, parent) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite::cpl_ActionComposite(const char* text, const char* stringid, const char* shortcut, int enable, int type, int cmdid, int checked, char* tooltip, const char * pixmap_name, const char* domain, void * userdata, cpl_ActionComposite* parent) : cpl_Action(text, stringid, shortcut, enable, type, cmdid, checked, tooltip, pixmap_name, domain, userdata, parent) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite::~cpl_ActionComposite() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->MaxId+1; i++) {
            if (this->Array[i].actionItem != NULL) {
                delete this->Array[i].actionItem;
                this->Array[i].actionItem = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}
