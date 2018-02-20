#include <lua.hpp>
#include <cpl_guicommonincludes.h>
#include <cpl_guisystemincludes.h>
#include "cpl_luascriptlib.h"

//-----------------------------------------------------------------------------
int LuaRunStringBuffer(lua_State * l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions
    
    const char* name = NULL;
    LuaD_getString(l, 1, name);
    assert(name != NULL);

    cpl_Application::Instance()->RunLuaScriptCommand(name);
    return (0);                 
}

//-----------------------------------------------------------------------------
int LuaGetApplicationPath(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions
    
    char * path = cpl_SystemConfig::Instance()->GetApplicationDirectory();
    assert(path != NULL);

    LuaD_retString(l, path);
    return 1;        
}

//-----------------------------------------------------------------------------
int LuaGetResourceIconRootPath(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    const char* subdir = NULL;
    LuaD_getString(l, 1, subdir);
    assert(subdir != NULL);

    char * application_path = cpl_SystemConfig::Instance()->GetApplicationDirectory();
    assert(application_path != NULL);

    char* iconbasePath = NULL;
    if( !strcmp(subdir, "small") ) {
        iconbasePath = cpl_SystemTools::AppendPath((char*)application_path, "/res/icon/small");
    } else if ( !strcmp(subdir, "medium") ) {
        iconbasePath = cpl_SystemTools::AppendPath((char*)application_path, "/res/icon/medium");
    } else if ( !strcmp(subdir, "large") ) {
        iconbasePath = cpl_SystemTools::AppendPath((char*)application_path, "/res/icon/large");
    } else if ( !strcmp(subdir, "placeholder") ) {
        iconbasePath = cpl_SystemTools::AppendPath((char*)application_path, "/res/icon/_placeholder");
    }

    assert(iconbasePath);
    LuaD_retString(l, iconbasePath);

    return 1;        
}

//-----------------------------------------------------------------------------
int LuaGetEnvironmentVariable(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions
    
    const char* name = NULL;
    LuaD_getString(l, 1, name);
    assert(name != NULL);

    char* var = getenv(name);
    if (var != NULL) {
        LuaD_retString(l, var);
        return 1;        
    }
    else {
        return 0;        
    }     
}
