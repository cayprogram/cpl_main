#include "cpl_controllerframeincludes.h"
#include <cpl_guiengine/cpl_applicationguiengineimpincludes.h>

//local includes.
#include <lua.hpp>
#include <lunar.h>
#include "cpl_controllermanagerluawrapper.h"


// -----------------------------------------------------------------------------
// class cpl_ControllerManagerLuaWrapper
// -----------------------------------------------------------------------------
//

char const cpl_ControllerManagerLuaWrapper::className[] = "cpl_ControllerManagerLuaWrapper";
Lunar<cpl_ControllerManagerLuaWrapper>::RegType cpl_ControllerManagerLuaWrapper::methods[] = 
{
    LUNAR_DECLARE_METHOD(cpl_ControllerManagerLuaWrapper, SetOutputWindowOnOff),
    LUNAR_DECLARE_METHOD(cpl_ControllerManagerLuaWrapper, ExecCommand),
    {0,0},
};

// -----------------------------------------------------------------------------
int cpl_ControllerManagerLuaWrapper::SetOutputWindowOnOff(lua_State* L) {
    //@@preconditions
    assert(L != NULL);
    assert(this->pControlManager != NULL);
    //@@end preconditions

    this->pControlManager->GetGUIEngine()->SetOutputWindowOnOff();
    return 0;
}

// -----------------------------------------------------------------------------
int cpl_ControllerManagerLuaWrapper::ExecCommand(lua_State* L) {
    //@@preconditions
    assert(L != NULL);
    assert(this->pControlManager != NULL);
    //@@end preconditions

    const char* sdata = NULL;
    if (LuaD_getString(L, 1, sdata) == 0) {
        return 0;
    }
    this->pControlManager->DoCommand((char*)sdata, NULL, NULL);
    return 0;
}

//------------------------------------------------------------------------
void cpl_ControllerManagerLuaWrapper::DoInitialization(cpl_ControllerManager* pOwner) {
    this->pControlManager = pOwner;
}

//------------------------------------------------------------------------
void cpl_ControllerManagerLuaWrapper::DoCleanup() {
    this->pControlManager = NULL;
}

//------------------------------------------------------------------------
cpl_ControllerManagerLuaWrapper::cpl_ControllerManagerLuaWrapper(lua_State *L) {
    this->pControlManager = NULL;
}

//------------------------------------------------------------------------
cpl_ControllerManagerLuaWrapper::~cpl_ControllerManagerLuaWrapper() {
}
