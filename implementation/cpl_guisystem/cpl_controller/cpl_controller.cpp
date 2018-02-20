#include "cpl_controllerframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_Controller
//-----------------------------------------------------------------------------
//
cpl_Controller * cpl_Controller::New() {
    return new cpl_Controller;
}

//-----------------------------------------------------------------------------
void cpl_Controller::SetControllerManager(cpl_ControllerManager* manager) {
    //@@preconditions
    assert(manager != NULL);
    //@@end preconditions
    
    this->pOwner = manager;
}

//-----------------------------------------------------------------------------
cpl_Controller::cpl_Controller(): pOwner(0) {
}

//-----------------------------------------------------------------------------
cpl_Controller::~cpl_Controller() {
}
