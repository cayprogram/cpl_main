#include "cpl_controllerapplicationincludes.h"

//-----------------------------------------------------------------------------
// class fmx_ApplicationControllerObjectFactory
//-----------------------------------------------------------------------------
//
cpl_ControllerManager* cpl_ApplicationControllerObjectFactory::CreateControlManager() {
    return new cpl_ApplicationControllerManager;
}

//-----------------------------------------------------------------------------
cpl_ApplicationControllerObjectFactory::cpl_ApplicationControllerObjectFactory() {
    cpl_ControllerObjectFactory::SetFactory(this);
}

//-----------------------------------------------------------------------------
cpl_ApplicationControllerObjectFactory::~cpl_ApplicationControllerObjectFactory(){
}
