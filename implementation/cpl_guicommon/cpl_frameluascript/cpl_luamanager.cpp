/*--------------------------------------------------------------------------*/
/*                              Include Files                               */
/*--------------------------------------------------------------------------*/
#include <lua.hpp>
#include <stdio.h>
#include <assert.h>
#include "cpl_luascript.h"
#include "cpl_luamanager.h"

//-----------------------------------------------------------------------------
cpl_LuaManager::cpl_LuaManager() {
    this->masterState = lua_open();
    if (this->masterState) {
        // open any auxiliary libraries we may need
        luaL_openlibs(this->masterState);
    }
    head = NULL;
}

//-----------------------------------------------------------------------------
cpl_LuaManager::~cpl_LuaManager() {
    // destroy all children scripts
    cpl_LuaScript* s = head;
    while (s) {
        // save the next pointer in case the script is deleted
        cpl_LuaScript* next = s->next;
        delete s;
        s = next;
    }
    // Verify the stack
    lua_close(this->masterState);
}

//-----------------------------------------------------------------------------
void cpl_LuaManager::RegisterLib(lua_RegisterLib func) {
    //@@preconditions
    assert(this->masterState != NULL);
    //@@end preconditions

    func(this->masterState);
}

//-----------------------------------------------------------------------------
void cpl_LuaManager::RegisterLib(const char* lua_fname) {
    //@@preconditions
    assert(this->masterState != NULL);
    //@@end preconditions

    if (luaL_loadfile(this->masterState, lua_fname) || lua_pcall(this->masterState, 0, 0, 0)) {
        printf("error: %s", lua_tostring(this->masterState, -1));
    }
}

//-----------------------------------------------------------------------------
cpl_LuaScript* cpl_LuaManager::CreateScript() {
    // create a script object
    cpl_LuaScript* s = new cpl_LuaScript(this);

    // tell the script object who its manager is
    s->manager = this;

    // link the new script into the list
    s->next = head;
    head = s;
    return(s);
}

//-----------------------------------------------------------------------------
void cpl_LuaManager::UnlinkScript(cpl_LuaScript* s) {
    // if s is at the head, simply unlink it
    if (head == s) {
        head = s->next;
        return;
    }

    // find previous link
    cpl_LuaScript* prev = head;
    while (prev) {
        if (prev->next == s) {
            prev->next = s->next;
            return;
        }
        prev = prev->next;
    }
}

//-----------------------------------------------------------------------------
void cpl_LuaManager::Update(float elapsedSec) {
    cpl_LuaScript* s = head;
    while (s) {
        s = s->Update(elapsedSec);
    }
}
