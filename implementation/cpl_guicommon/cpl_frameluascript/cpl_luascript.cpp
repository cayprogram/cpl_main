/*--------------------------------------------------------------------------*/
/*                              Include Files                               */
/*--------------------------------------------------------------------------*/
#include <lua.hpp>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "cpl_luascript.h"
#include "cpl_luamanager.h"

//-----------------------------------------------------------------------------
cpl_LuaScript::cpl_LuaScript(cpl_LuaManager* mgr) {
    //@@preconditions
    assert(mgr != NULL);
    //@@end preconditions

    this->manager = mgr;
    this->state = LSS_NOTLOADED;
    this->time = 0;
    sprintf(this->lastErrorString, "No error.\n");

    // create a thread/state for this object
    this->threadState = lua_newthread(this->manager->masterState);

    // save a pointer to the thread manager object in the global table
    // using the new thread's vm pointer as a key
    lua_pushlightuserdata(this->manager->masterState, this->threadState);
    lua_pushlightuserdata(this->manager->masterState, this);
    lua_settable(this->manager->masterState, LUA_GLOBALSINDEX);
}

//-----------------------------------------------------------------------------
cpl_LuaScript::~cpl_LuaScript() {
    // Unhook from the script manager
    this->manager->UnlinkScript(this);
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::RunFile(char* fileName) {
    //@@preconditions
    assert(fileName != NULL);
    assert(fileName[0] != '\0');
    assert(this->manager->masterState);
    assert(this->threadState);
    //@@end precondition

    int status = luaL_loadfile(this->threadState, fileName);
    if (status == 0) {
        ResumeScript(0.0f);
    }
    else {
        FormatError();
        OutputError("Syntax Error");
    }
}

//-----------------------------------------------------------------------------
int cpl_LuaScript::RunString(char* commandString) {
    //@@preconditions
    assert(this->manager->masterState);
    assert(this->threadState);
    //@@end preconditions

    int status = luaL_loadbuffer(this->threadState, commandString, strlen(commandString), "Console");
    if (status == 0) {
        status = lua_pcall(this->threadState, lua_gettop(this->threadState) - 1, 0, 0);
    }
    if (status) {
        FormatError();
        OutputError("Syntax Error");
        return(-1);
    }
    return(0);
}

//-----------------------------------------------------------------------------
cpl_LuaScript* cpl_LuaScript::Update(float elapsedSec) {
    time += elapsedSec;
    switch (this->state) {
    case LSS_WAITTIME:
        if (time >= this->waitTimestamp) {
            ResumeScript(0.0f);
        }
        break;
    case LSS_WAITFRAME:
        this->waitFrame--;
        if (this->waitFrame <= 0) {
            ResumeScript(0.0f);
        }
        break;
    case LSS_NOTLOADED:
        break;
    default:
        break;
    }
    return(next);
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::AbortWait() {
    ResumeScript(1.0f);
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::ResumeScript(float param) {
    // we're about to run/resume the thread, so set the global
    this->state = LSS_RUNNING;
    
    // param is treated as a return value from the function that yielded
    lua_pushnumber(this->threadState, param);

    int status = lua_resume(this->threadState, 1);
    if (status) {
        FormatError();
        OutputError("Runtime Error:");
    }
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::CallFn(char* fnName) {
    //@@precondition
    assert(fnName != NULL);
    assert(fnName[0] != '\0');
    //@@end precondition

    // find the lua function and push it on the stack
    lua_getglobal(this->threadState, fnName);

    // now, call into Lua
    int status = lua_pcall(this->threadState, 0, 0, 0);
    if (status) {
        FormatError();
        OutputError("Runtime Error:");
    }
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::CallFn(char* fnName, int iParam) {
    //@@precondition
    assert(fnName != NULL);
    assert(fnName[0] != '\0');
    //@@end precondition

    // find the lua function and push it on the stack
    lua_getglobal(this->threadState, fnName);

    // push our single argument
    lua_pushnumber(this->threadState, iParam);

    // now, call into Lua
    int status = lua_pcall(this->threadState, 1, 0, 0);
    if (status) {
        FormatError();
        OutputError("Runtime Error:");
    }
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::CallFn(char* fnName, int* iParam) {
    //@@precondition
    assert(fnName != NULL);
    assert(fnName[0] != '\0');
    //@@end precondition

    // find the lua function and push it on the stack
    lua_getglobal(this->threadState, fnName);

    // now, call into Lua
    int status = lua_pcall(this->threadState, 0, 1, 0);
    if (status) {
        FormatError();
        OutputError("Runtime Error:");
        *iParam = -1;
    }
    else {
        *iParam = (int)lua_tointeger(this->threadState, -1);
        lua_pop(this->threadState, 1);
    }
}

void cpl_LuaScript::CallFn(char* fnName, const char *& sParam)
{
    //@@precondition
    assert(fnName != NULL);
    assert(fnName[0] != '\0');
    assert(sParam == NULL);
    //@@end precondition

    // find the Lua function and push it on the stack
    lua_getglobal(this->threadState, fnName);

    // now, call into Lua
    int status = lua_pcall(this->threadState, 0, 1, 0);
    if (status) {
        FormatError();
        OutputError("Runtime Error:");
        sParam = NULL;
    }
    else {
        sParam = lua_tostring(this->threadState, -1);
        lua_pop(this->threadState, 1);
    }
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::FormatError() {
    const char*  msg;
    msg = lua_tostring(this->threadState, -1);
    if (msg == NULL) {
        msg = "(error with no message)";
    }
    lua_pop(this->threadState, 1);
    sprintf(this->lastErrorString, msg);
}

//-----------------------------------------------------------------------------
void cpl_LuaScript::OutputError(char* strType) {
    //@@preconditions
    assert(strType != NULL);
    assert(strType[0] != '\0');
    //@@end preconditions

    printf("%s %s \n", strType, this->lastErrorString);
}
