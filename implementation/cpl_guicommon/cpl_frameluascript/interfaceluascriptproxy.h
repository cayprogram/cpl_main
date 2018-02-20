#ifndef LUASCRIPTPROXYINTERFACE_H
#define LUASCRIPTPROXYINTERFACE_H

typedef struct lua_State lua_State;
typedef void (*lua_RegisterLib) (lua_State* l);

class ILuaScriptProxy {
public:
    virtual int RunFile(const char* fileName) = 0;
    virtual int RunString(const char* commandString) = 0;
    virtual int RegisterLib(const char* lua_fname) = 0;
    virtual int RegisterLib(lua_RegisterLib func) = 0;
    virtual int CallFn(const char* funcName) = 0;
    virtual int CallFn(const char* funcName, int& retVal) = 0;
    virtual int CallFn(const char* funcName, const char *& retVal) = 0;
};

#endif //LUASCRIPTPROXYINTERFACE_H
