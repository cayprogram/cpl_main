#include "cpl_actionframeincludes.h"

//-----------------------------------------------------------------------------
void cpl_ActionCompositeProxy::SetRoot(cpl_ActionComposite* pAction) {
    //@@preconditions
    assert(pAction != NULL);
    assert(pAction->GetComposite() == NULL);
    //@@end preconditions
    
    this->root = pAction;
    this->current = pAction;
}

//-----------------------------------------------------------------------------
void cpl_ActionCompositeProxy::SetCurrent(cpl_ActionComposite* pAction) {
    //@@preconditions
    assert(pAction != NULL);
    //@@end preconditions

    this->current = pAction;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite* cpl_ActionCompositeProxy::GetRoot() {
    //@@preconditions
    assert(this->root != NULL);
    //@@end preconditions

    return this->root;
}

//-----------------------------------------------------------------------------
cpl_ActionComposite* cpl_ActionCompositeProxy::GetCurrent() {
    //@@preconditions
    assert(this->current != NULL);
    //@@end preconditions

    return this->current;
}

//-----------------------------------------------------------------------------
cpl_ActionCompositeProxy::cpl_ActionCompositeProxy() {    
    this->root = NULL;
    this->current = NULL;
}

//-----------------------------------------------------------------------------
cpl_ActionCompositeProxy::~cpl_ActionCompositeProxy() {
    //as proxy, so don't delete this pointer.
    this->root = NULL;
    this->current = NULL;
}
