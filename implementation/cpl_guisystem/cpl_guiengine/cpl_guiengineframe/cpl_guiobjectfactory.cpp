#include "cpl_guiengineframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_GUIObjectFactory
//-----------------------------------------------------------------------------
//
cpl_GUIObjectFactory * cpl_GUIObjectFactory::instance = NULL;

//-----------------------------------------------------------------------------
cpl_GUIObjectFactory * cpl_GUIObjectFactory::Instance() {
    return cpl_GUIObjectFactory::instance;
}

//-----------------------------------------------------------------------------
void cpl_GUIObjectFactory::Delete() {
    if (cpl_GUIObjectFactory::instance) {
        delete cpl_GUIObjectFactory::instance;
        cpl_GUIObjectFactory::instance = NULL;
    }
}

//-----------------------------------------------------------------------------
void cpl_GUIObjectFactory::SetFactory(cpl_GUIObjectFactory* factory) {
    //@@preconditions
    assert(factory != NULL);
    //@@end preconditions

    cpl_GUIObjectFactory::instance = factory;
}

//-----------------------------------------------------------------------------
cpl_GUIObjectFactory::cpl_GUIObjectFactory() {
}

//-----------------------------------------------------------------------------
cpl_GUIObjectFactory::~cpl_GUIObjectFactory() {
}
