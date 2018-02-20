#include <cpl_controller/cpl_controllerframeincludes.h>

//local includes.
#include "cpl_luaproxy.h"

//-----------------------------------------------------------------------------
// class cpl_LuaProxy::Implemenation
//-----------------------------------------------------------------------------
//
class cpl_LuaProxy::Implemenation : public ILuaScriptProxy {

public:
    //initialize.
    void Initialize();
    
    //cleanup.
    void Cleanup();
        
    //execute file
    int RunFile(const char* fileName);

    //call function 
    int CallFn(const char* funcName);
    int CallFn(const char* funcName, int& retVal);
    int CallFn(const char* funcName, const char *& retVal);

    //execute command  
    int RunString(const char* commandString);

    //register lib.
    int RegisterLib(lua_RegisterLib func);
    
    //register lib.
    int RegisterLib(const char* lua_lib);

public:
    //constructor
    Implemenation();

    //destructor.
    ~Implemenation();

    //protected variables.
    cpl_LuaManager * LuaHandler;
    cpl_LuaScript* luaScript;
};

//-----------------------------------------------------------------------------
cpl_LuaProxy::Implemenation::Implemenation() {
    this->luaScript = NULL;
    this->LuaHandler = new cpl_LuaManager();
}

//-----------------------------------------------------------------------------
cpl_LuaProxy::Implemenation::~Implemenation() {
    //@@preconditions
    assert(this->luaScript == NULL);
    //@@end preconditions    

    if (this->LuaHandler != NULL) {
        delete this->LuaHandler;
        this->LuaHandler = NULL;
    }
}

//-----------------------------------------------------------------------------
int cpl_LuaProxy::Implemenation::RegisterLib(lua_RegisterLib func) {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    this->LuaHandler->RegisterLib(func);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_LuaProxy::Implemenation::RegisterLib(const char* lua_lib) {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    this->LuaHandler->RegisterLib(lua_lib);
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::Implemenation::Initialize() {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    this->luaScript = this->LuaHandler->CreateScript();
    assert(this->luaScript != NULL);
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::Implemenation::Cleanup() {
    //@@preconditions
    assert(this->LuaHandler != NULL);
    //@@end preconditions

    if (this->luaScript != NULL) {
        delete this->luaScript;
        this->luaScript = NULL;
    }
}

//-----------------------------------------------------------------------------
int cpl_LuaProxy::Implemenation::CallFn(const char* funcName) {
    //@@preconditions
    assert(this->luaScript != NULL);
    assert(funcName != NULL);
    //@@end preconditions

    this->luaScript->CallFn((char*)funcName);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_LuaProxy::Implemenation::CallFn(const char* funcName, int& retVal) {
    //@@preconditions
    assert(this->luaScript != NULL);
    assert(funcName != NULL);
    //@@end preconditions

    this->luaScript->CallFn((char*)funcName, &retVal);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_LuaProxy::Implemenation::CallFn(const char* funcName, const char *& retVal) {
    //@@preconditions
    assert(this->luaScript != NULL);
    assert(funcName != NULL);
    //@@end preconditions

    this->luaScript->CallFn((char*)funcName, retVal);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_LuaProxy::Implemenation::RunString(const char* buffer) {
    //@@preconditions
    assert(this->luaScript != NULL);
    assert(buffer != NULL);
    //@@end preconditions

    return this->luaScript->RunString((char*)buffer);
}

//-----------------------------------------------------------------------------
int cpl_LuaProxy::Implemenation::RunFile(const char* fname) {
    //@@preconditions
    assert(this->luaScript != NULL);
    assert(fname != NULL);
    //@@end preconditions

    this->luaScript->RunFile((char*)fname);
    return 1;
}

//-----------------------------------------------------------------------------
// class cpl_LuaProxy
//-----------------------------------------------------------------------------
//
cpl_LuaProxy* cpl_LuaProxy::New() {
    return new cpl_LuaProxy;
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::DoInitialization() {
    //@@preconditions
    assert(this->pOwner != NULL);
    assert(this->scriptProxy == NULL);
    //@@end preconditions

    this->scriptProxy = new Implemenation();
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::DoCleanup() {
    if (this->scriptProxy != NULL) {
        this->scriptProxy->Cleanup();
        delete this->scriptProxy;
        this->scriptProxy = NULL;
    }
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::CreateScriptContext() {
    //@@preconditions
    assert(this->pOwner != NULL);
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    this->scriptProxy->Initialize();
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::Execute(const char* buffer) {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    assert(buffer != NULL);
    //@@end preconditions
    
    this->scriptProxy->RunString(buffer);
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::RunScriptFile(const char* fname)  {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    assert(fname != NULL);
    //@@end preconditions
    
    this->scriptProxy->RunFile(fname);
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::RunScriptString(const char* buffer)  {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    assert(buffer != NULL);
    //@@end preconditions
    
    this->scriptProxy->RunString(buffer);
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::RegisterLib(lua_RegisterLib func) {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    this->scriptProxy->RegisterLib(func);
}

//-----------------------------------------------------------------------------
void cpl_LuaProxy::RegisterLib(const char* libname) {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    this->scriptProxy->RegisterLib(libname);
}

//-----------------------------------------------------------------------------
void* cpl_LuaProxy::GetMainLuaState() {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    assert(this->scriptProxy->LuaHandler != NULL);
    //@@end preconditions

    return this->scriptProxy->LuaHandler->masterState;
}

//-----------------------------------------------------------------------------
ILuaScriptProxy* cpl_LuaProxy::GetImplementation() {
    //@@preconditions
    assert(this->scriptProxy != NULL);
    //@@end preconditions

    return this->scriptProxy;
}

//-----------------------------------------------------------------------------
cpl_LuaProxy::cpl_LuaProxy() {
    this->scriptProxy = NULL;
}

//-----------------------------------------------------------------------------
cpl_LuaProxy::~cpl_LuaProxy() {
    if (this->scriptProxy != NULL) {
        delete this->scriptProxy;
        this->scriptProxy = NULL;
    }
}
