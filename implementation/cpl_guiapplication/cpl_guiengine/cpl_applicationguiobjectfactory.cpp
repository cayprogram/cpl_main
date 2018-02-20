#include "cpl_applicationguiengineimpincludes.h"

//-----------------------------------------------------------------------------
// class cpl_ApplicationGUIObjectFactory
//-----------------------------------------------------------------------------
//
cpl_GUIEngineImp* cpl_ApplicationGUIObjectFactory::CreateGUIEngineImp() {
    return new cpl_ApplicationGUIEngineImp;
}

//-----------------------------------------------------------------------------
cpl_MainWindowImp* cpl_ApplicationGUIObjectFactory::CreateMainWindowImp(cpl_MainWindow* pOwner) {
    return new cpl_ApplicationMainWindowImp(pOwner);
}

//-----------------------------------------------------------------------------
cpl_ApplicationGUIObjectFactory::cpl_ApplicationGUIObjectFactory() {
}

//-----------------------------------------------------------------------------
cpl_ApplicationGUIObjectFactory::~cpl_ApplicationGUIObjectFactory() {
}
