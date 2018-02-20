// signal header has been included
#ifndef _LUAMANAGER_H
#define _LUAMANAGER_H

/*--------------------------------------------------------------------------*/
/*                              Data Structures                             */
/*--------------------------------------------------------------------------*/
class cpl_LuaScript;
typedef struct lua_State lua_State;

typedef void (*lua_RegisterLib) (lua_State* l);

class cpl_LuaManager {
public: // ---------------------------------------
    cpl_LuaManager(void);
    ~cpl_LuaManager(void);

    void RegisterLib(const char* lua_fname);
    void RegisterLib(lua_RegisterLib func);
    void UnlinkScript(cpl_LuaScript* s);
    void Update(float elapsedSec);
    int  NumScripts(void);
    cpl_LuaScript* CreateScript(void);
    lua_State*  masterState;    
private:    // ---------------------------------------
    cpl_LuaScript*   head;
};
#endif // _LUAMANAGER_H
