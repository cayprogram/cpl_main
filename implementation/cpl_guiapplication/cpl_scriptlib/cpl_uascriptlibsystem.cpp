#include <lua.hpp>
#include <cpl_guicommonincludes.h>
#include <cpl_guisystemincludes.h>
#include <ls_script.h>
#include "cpl_luascriptlib.h"

//-----------------------------------------------------------------------------
// script.
//-----------------------------------------------------------------------------
int LuaScriptExec(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    const char* name = NULL;
    LuaD_getString(l, 1, name);
    assert(name != NULL);

    pl_ExecuteScript((char*)name);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaScriptSetInputREAL(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    float fdata = 0.0f;
    if (LuaD_getFloat(l, 2, fdata) == 0) {
        return (0);
    }

    pl_ScriptServerSetInputAsREAL((PSFuncParamEnum)paramidx, fdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaScriptSetInputREALArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    float* fdata = NULL;
    int dataLen = LuaD_getArrayFloat(l, 2, fdata);
    if (dataLen == 0 || fdata == NULL) {
        return (0);
    }

    pl_ScriptServerSetInputAsREALArray((PSFuncParamEnum)paramidx, fdata, dataLen);
    cpl_LuaScriptUtilty::FreeArray(fdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaScriptSetInputINT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    int idata = 0;
    if (LuaD_getInteger(l, 2, idata) == 0) {
        return (0);
    }

    pl_ScriptServerSetInputAsINT((PSFuncParamEnum)paramidx, idata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaScriptSetInputINTArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    int* idata = NULL;
    int dataLen = LuaD_getArrayInteger(l, 2, idata);
    if (dataLen == 0 || idata == NULL) {
        return (0);
    }

    pl_ScriptServerSetInputAsINTArray((PSFuncParamEnum)paramidx, idata, dataLen);
    cpl_LuaScriptUtilty::FreeArray(idata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaScriptSetInputSTRING(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    const char* sdata = NULL;
    if (LuaD_getString(l, 2, sdata) == 0 || sdata == NULL) {
        return (0);
    }

    pl_ScriptServerSetInputAsSTRING((PSFuncParamEnum)paramidx, (char*)sdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaScriptSetInputSTRINGArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    const char** sdata = NULL;
    int dataLen = LuaD_getArrayString(l, 2, sdata);
    if (dataLen == 0 || sdata == NULL) {
        return (0);
    }

    pl_ScriptServerSetInputAsSTRINGArray((PSFuncParamEnum)paramidx, (char**)sdata, dataLen);
    cpl_LuaScriptUtilty::FreeArray(sdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaScriptSetInputOBJECT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    void* vdata = NULL;
    if (LuaD_getVoid(l, 2, vdata) == 0) {
        return (0);
    }

    pl_ScriptServerSetInputAsVOID((PSFuncParamEnum)paramidx, vdata);
    return (0);     
}

//////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
int LuaScriptGetOutputParamNumber(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int num = pl_ScriptServerGetOutputParamNumber();

    LuaD_retInteger(l, num);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputParamType(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    PSDataTypeEnum dataType = PS_AtomINVALID;
    pl_ScriptServerGetOutputParamType((PSFuncParamEnum)paramidx, dataType);

    LuaD_retInteger(l, (int)dataType);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputREAL(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    float fdata = 0.0f;
    pl_ScriptServerGetOutputAsREAL((PSFuncParamEnum)paramidx, fdata);

    LuaD_retFloat(l, fdata);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputREALArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int dataLen = 0;
    float* fdata = NULL;
    pl_ScriptServerGetOutputAsREALArray((PSFuncParamEnum)paramidx, fdata, dataLen);
    assert(fdata != NULL);

    LuaD_retArrayFloat(l, fdata, dataLen);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputINT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int idata = 0;
    pl_ScriptServerGetOutputAsINT((PSFuncParamEnum)paramidx, idata);

    LuaD_retInteger(l, idata);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputINTArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int dataLen = 0;
    int* idata = NULL;
    pl_ScriptServerGetOutputAsINTArray((PSFuncParamEnum)paramidx, idata, dataLen);
    assert(idata != NULL);

    LuaD_retArrayInteger(l, idata, dataLen);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputSTRING(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    char* sdata = NULL;
    pl_ScriptServerGetOutputAsSTRING((PSFuncParamEnum)paramidx, sdata);
    assert(sdata != NULL);

    LuaD_retString(l, sdata);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputSTRINGArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int dataLen = 0; char** sdata = NULL;
    pl_ScriptServerGetOutputAsSTRINGArray((PSFuncParamEnum)paramidx, sdata, dataLen);
    assert(sdata != NULL);

    LuaD_retArrayString(l, (const char**)sdata, dataLen);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaScriptGetOutputOBJECT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    void* vdata = NULL;
    pl_ScriptServerGetOutputAsVOID((PSFuncParamEnum)paramidx, vdata);
    assert(vdata != NULL);

    LuaD_retVoid(l, vdata);
    return (1);
}

//-----------------------------------------------------------------------------
// function.
//-----------------------------------------------------------------------------
int LuaFuncExec(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    const char* name = NULL;
    LuaD_getString(l, 1, name);
    assert(name != NULL);

    pl_ExecuteFunction((char*)name);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaFuncSetInputREAL(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    float fdata = 0.0f;
    if (LuaD_getFloat(l, 2, fdata) == 0) {
        return (0);
    }

    pl_FuncServerSetInputAsREAL((PSFuncParamEnum)paramidx, fdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaFuncSetInputREALArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    float* fdata = NULL;
    int dataLen = LuaD_getArrayFloat(l, 2, fdata);
    if (dataLen == 0 || fdata == NULL) {
        return (0);
    }

    pl_FuncServerSetInputAsREALArray((PSFuncParamEnum)paramidx, fdata, dataLen);
    cpl_LuaScriptUtilty::FreeArray(fdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaFuncSetInputINT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    int idata = 0;
    if (LuaD_getInteger(l, 2, idata) == 0) {
        return (0);
    }

    pl_FuncServerSetInputAsINT((PSFuncParamEnum)paramidx, idata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaFuncSetInputINTArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    int* idata = NULL;
    int dataLen = LuaD_getArrayInteger(l, 2, idata);
    if (dataLen == 0 || idata == NULL) {
        return (0);
    }

    pl_FuncServerSetInputAsINTArray((PSFuncParamEnum)paramidx, idata, dataLen);
    cpl_LuaScriptUtilty::FreeArray(idata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaFuncSetInputSTRING(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    const char* sdata = NULL;
    if (LuaD_getString(l, 2, sdata) == 0 || sdata == NULL) {
        return (0);
    }

    pl_FuncServerSetInputAsSTRING((PSFuncParamEnum)paramidx, (char*)sdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaFuncSetInputSTRINGArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    const char** sdata = NULL;
    int dataLen = LuaD_getArrayString(l, 2, sdata);
    if (dataLen == 0 || sdata == NULL) {
        return (0);
    }

    pl_FuncServerSetInputAsSTRINGArray((PSFuncParamEnum)paramidx, (char**)sdata, dataLen);
    cpl_LuaScriptUtilty::FreeArray(sdata);
    return (0);     
}

//-----------------------------------------------------------------------------
int LuaFuncSetInputOBJECT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = 0;
    if (LuaD_getInteger(l, 1, paramidx) == 0 || paramidx < 0) {
        return (0);
    }
    void* vdata = NULL;
    if (LuaD_getVoid(l, 2, vdata) == 0) {
        return (0);
    }

    pl_FuncServerSetInputAsVOID((PSFuncParamEnum)paramidx, vdata);
    return (0);     
}

//////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
int LuaFuncGetOutputREAL(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    float fdata = 0.0f;
    pl_FuncServerGetOutputAsREAL((PSFuncParamEnum)paramidx, fdata);

    LuaD_retFloat(l, fdata);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaFuncGetOutputREALArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int dataLen = 0;
    float* fdata = NULL;
    pl_FuncServerGetOutputAsREALArray((PSFuncParamEnum)paramidx, fdata, dataLen);
    assert(fdata != NULL);

    LuaD_retArrayFloat(l, fdata, dataLen);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaFuncGetOutputINT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int idata = 0;
    pl_FuncServerGetOutputAsINT((PSFuncParamEnum)paramidx, idata);
    LuaD_retInteger(l, idata);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaFuncGetOutputINTArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int dataLen = 0;
    int* idata = NULL;
    pl_FuncServerGetOutputAsINTArray((PSFuncParamEnum)paramidx, idata, dataLen);
    assert(idata != NULL);

    LuaD_retArrayInteger(l, idata, dataLen);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaFuncGetOutputSTRING(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    char* sdata = NULL;
    pl_FuncServerGetOutputAsSTRING((PSFuncParamEnum)paramidx, sdata);
    assert(sdata != NULL);

    LuaD_retString(l, sdata);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaFuncGetOutputSTRINGArray(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    int dataLen = 0; char** sdata = NULL;
    pl_FuncServerGetOutputAsSTRINGArray((PSFuncParamEnum)paramidx, sdata, dataLen);
    assert(sdata != NULL);

    LuaD_retArrayString(l, (const char**)sdata, dataLen);
    return (1);     
}

//-----------------------------------------------------------------------------
int LuaFuncGetOutputOBJECT(lua_State* l) {
    //@@preconditions
    assert(l != NULL);
    //@@end preconditions

    int paramidx = (int)luaL_checknumber(l, 1);
    assert(paramidx >= 0);

    void* vdata = NULL;
    pl_FuncServerGetOutputAsVOID((PSFuncParamEnum)paramidx, vdata);
    assert(vdata != NULL);

    LuaD_retVoid(l, vdata);
    return (1);
}
