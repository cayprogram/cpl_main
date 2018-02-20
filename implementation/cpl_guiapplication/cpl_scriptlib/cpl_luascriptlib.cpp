#include <lua.hpp>
#include <cpl_guisystemincludes.h>
#include "cpl_luascriptlib.h"

//-----------------------------------------------------------------------------
// system.
//-----------------------------------------------------------------------------
//
extern int LuaRunStringBuffer           (lua_State* l); 
extern int LuaGetApplicationPath        (lua_State* l);
extern int LuaGetEnvironmentVariable    (lua_State* l);

extern int LuaGetResourceIconRootPath   (lua_State* l);

//-----------------------------------------------------------------------------
// function
//-----------------------------------------------------------------------------
//
extern int LuaFuncExec                  (lua_State* l);
extern int LuaFuncSetInputINT           (lua_State* l);
extern int LuaFuncSetInputINTArray      (lua_State* l);
extern int LuaFuncSetInputREAL          (lua_State* l);
extern int LuaFuncSetInputREALArray     (lua_State* l);
extern int LuaFuncSetInputSTRING        (lua_State* l);
extern int LuaFuncSetInputSTRINGArray   (lua_State* l);
extern int LuaFuncSetInputOBJECT        (lua_State* l);
extern int LuaFuncGetOutputParamNumber  (lua_State* l);
extern int LuaFuncGetOutputParamType    (lua_State* l);
extern int LuaFuncGetOutputINT          (lua_State* l);
extern int LuaFuncGetOutputINTArray     (lua_State* l);
extern int LuaFuncGetOutputREAL         (lua_State* l);
extern int LuaFuncGetOutputREALArray    (lua_State* l);
extern int LuaFuncGetOutputSTRING       (lua_State* l);
extern int LuaFuncGetOutputSTRINGArray  (lua_State* l);
extern int LuaFuncGetOutputOBJECT       (lua_State* l);

//-----------------------------------------------------------------------------
// script.
//-----------------------------------------------------------------------------
//
extern int LuaScriptExec                (lua_State* l);
extern int LuaScriptSetInputINT         (lua_State* l);
extern int LuaScriptSetInputINTArray    (lua_State* l);
extern int LuaScriptSetInputREAL        (lua_State* l);
extern int LuaScriptSetInputREALArray   (lua_State* l);
extern int LuaScriptSetInputSTRING      (lua_State* l);
extern int LuaScriptSetInputSTRINGArray (lua_State* l);
extern int LuaScriptSetInputOBJECT      (lua_State* l);
extern int LuaScriptGetOutputParamNumber(lua_State* l);
extern int LuaScriptGetOutputParamType  (lua_State* l);
extern int LuaScriptGetOutputINT        (lua_State* l);
extern int LuaScriptGetOutputINTArray   (lua_State* l);
extern int LuaScriptGetOutputREAL       (lua_State* l);
extern int LuaScriptGetOutputREALArray  (lua_State* l);
extern int LuaScriptGetOutputSTRING     (lua_State* l);
extern int LuaScriptGetOutputSTRINGArray(lua_State* l);
extern int LuaScriptGetOutputOBJECT     (lua_State* l);

//-----------------------------------------------------------------------------
// table of function names and entry points that will be registered with LUA
//-----------------------------------------------------------------------------
//
static const luaL_reg scriptAppLib[] = {
//-----------------------------------------------------------------------------    
    {"AppPath",                             LuaGetApplicationPath         },   
    {"RunString",                           LuaRunStringBuffer            },      
    {"GetEnv",                              LuaGetEnvironmentVariable     },

    {"GetResourceIconRootPath",             LuaGetResourceIconRootPath    },   

//-----------------------------------------------------------------------------
    {"FScriptExec",                         LuaScriptExec                 },
    {"FScriptSetInputINT",                  LuaScriptSetInputINT          },
    {"FScriptSetInputINTArray",             LuaScriptSetInputINTArray     },
    {"FScriptSetInputREAL",                 LuaScriptSetInputREAL         },
    {"FScriptSetInputREALArray",            LuaScriptSetInputREALArray    },
    {"FScriptSetInputSTRING",               LuaScriptSetInputSTRING       },
    {"FScriptSetInputSTRINGArray",          LuaScriptSetInputSTRINGArray  },
    {"FScriptSetInputOBJECT",               LuaScriptSetInputOBJECT       },
    {"FScriptGetOutputParamNumber",         LuaScriptGetOutputParamNumber },
    {"FScriptGetOutputParamType",           LuaScriptGetOutputParamType   },
    {"FScriptGetOutputINT",                 LuaScriptGetOutputINT         },
    {"FScriptGetOutputINTArray",            LuaScriptGetOutputINTArray    },
    {"FScriptGetOutputREAL",                LuaScriptGetOutputREAL        },
    {"FScriptGetOutputREALArray",           LuaScriptGetOutputREALArray   },
    {"FScriptGetOutputSTRING",              LuaScriptGetOutputSTRING      },
    {"FScriptGetOutputSTRINGArray",         LuaScriptGetOutputSTRINGArray },    
    {"FScriptGetOutputOBJECT",              LuaScriptGetOutputOBJECT      },
//-----------------------------------------------------------------------------
    {"FuncExec",                            LuaFuncExec                   },
    {"FuncSetInputINT",                     LuaFuncSetInputINT            },
    {"FuncSetInputINTArray",                LuaFuncSetInputINTArray       },
    {"FuncSetInputREAL",                    LuaFuncSetInputREAL           },
    {"FuncSetInputREALArray",               LuaFuncSetInputREALArray      },
    {"FuncSetInputSTRING",                  LuaFuncSetInputSTRING         },
    {"FuncSetInputSTRINGArray",             LuaFuncSetInputSTRINGArray    },
    {"FuncSetInputOBJECT",                  LuaFuncSetInputOBJECT         },
    {"FuncGetOutputINT",                    LuaFuncGetOutputINT           },
    {"FuncGetOutputINTArray",               LuaFuncGetOutputINTArray      },
    {"FuncGetOutputREAL",                   LuaFuncGetOutputREAL          },
    {"FuncGetOutputREALArray",              LuaFuncGetOutputREALArray     },
    {"FuncGetOutputSTRING",                 LuaFuncGetOutputSTRING        },
    {"FuncGetOutputSTRINGArray",            LuaFuncGetOutputSTRINGArray   },    
    {"FuncGetOutputOBJECT",                 LuaFuncGetOutputOBJECT        },

//-----------------------------------------------------------------------------    

    {NULL, NULL}
};

//-----------------------------------------------------------------------------
void LuaOpenScriptLib(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    // register our library of routines under the table name Script   
    luaL_openlib(l, "App", scriptAppLib, 0);
}

//-----------------------------------------------------------------------------
// extension lua function table.
//-----------------------------------------------------------------------------
const char* prog = "--version 120\n" 
"function init()\n" 
"end\n" 
"\n" 
"function main()\n" 
"end\n" 
"\n" 
"function deinit()\n" 
"end\n";
