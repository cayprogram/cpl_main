#include "cpl_controllerframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_ControllerObjectFactory
//-----------------------------------------------------------------------------
//
cpl_ControllerObjectFactory * cpl_ControllerObjectFactory::instance = NULL;

//-----------------------------------------------------------------------------
cpl_ControllerObjectFactory * cpl_ControllerObjectFactory::Instance() {
    return cpl_ControllerObjectFactory::instance;
}

//-----------------------------------------------------------------------------
void cpl_ControllerObjectFactory::Delete() {
    if (cpl_ControllerObjectFactory::instance) {
        delete cpl_ControllerObjectFactory::instance;
        cpl_ControllerObjectFactory::instance = NULL;
    }
}

//-----------------------------------------------------------------------------
void cpl_ControllerObjectFactory::SetFactory(cpl_ControllerObjectFactory* factory) {
    //@@preconditions
    assert(factory != NULL);
    //@@end preconditions

    cpl_ControllerObjectFactory::instance = factory;
}

//-----------------------------------------------------------------------------
cpl_ControllerObjectFactory::cpl_ControllerObjectFactory() {
}

//-----------------------------------------------------------------------------
cpl_ControllerObjectFactory::~cpl_ControllerObjectFactory() {
}

