#include "cpl_guiengineframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_MainWindowImp
//-----------------------------------------------------------------------------
//
cpl_MainWindowImp* cpl_MainWindowImp::New(cpl_MainWindow* pOwner) {    
    //@@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions
    
    return cpl_GUIObjectFactory::Instance()->CreateMainWindowImp(pOwner);
}

//-----------------------------------------------------------------------------
cpl_MainWindowImp::cpl_MainWindowImp(cpl_MainWindow* pOwner) : Owner(pOwner) {
}

//-----------------------------------------------------------------------------
cpl_MainWindowImp::~cpl_MainWindowImp() {
}
