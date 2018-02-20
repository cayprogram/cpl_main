#include <cpl_controller/cpl_controllerframeincludes.h>
#include "cpl_scriptproxy.h"

//-----------------------------------------------------------------------------
// class cpl_ScriptAction
//-----------------------------------------------------------------------------
//
class cpl_ScriptAction : public cpl_Action {

public:
    //execute.
    virtual int Execute() {        
        return this->receiver->DoCommand(this->actionData.text,  this->actionData.userdata, this->actionData.cmddata);
    }
public:
    //constructor
    cpl_ScriptAction(cpl_ControllerManager* r):  receiver(r) {}

    //protected variables.
    cpl_ControllerManager* receiver;        
};

//-----------------------------------------------------------------------------
// class cpl_ScriptProxy
//-----------------------------------------------------------------------------
//
cpl_ScriptProxy* cpl_ScriptProxy::New() {
    return new cpl_ScriptProxy;
}

//-----------------------------------------------------------------------------
void cpl_ScriptProxy::DoInitialization() {
    //@@preconditions
    assert(this->pOwner != NULL);
    assert(this->scriptProxy == NULL);
    //@@end preconditions

    this->scriptProxy = new cpl_ScriptAction(this->pOwner);
}

//-----------------------------------------------------------------------------
void cpl_ScriptProxy::DoCleanup() {
    if (this->scriptProxy != NULL) {
        delete this->scriptProxy;
        this->scriptProxy = NULL;
    }
}

//-----------------------------------------------------------------------------
cpl_Action* cpl_ScriptProxy::GetScriptHandler() {
    //@@postconditions
    assert(this->scriptProxy != NULL);
    //@@end postconditions
    
    return this->scriptProxy;
}

//-----------------------------------------------------------------------------
cpl_ScriptProxy::cpl_ScriptProxy() {
    this->scriptProxy = NULL;
}

//-----------------------------------------------------------------------------
cpl_ScriptProxy::~cpl_ScriptProxy() {
    if (this->scriptProxy != NULL) {
        delete this->scriptProxy;
        this->scriptProxy = NULL;
    }
}
