#include <cpl_guisystemincludes.h>

//local includes.
#include "cpl_applicationrunner.h"

//-----------------------------------------------------------------------------
// class cpl_ApplicationRunner
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int cpl_ApplicationRunner::Initialize(int argc, char * * argv) {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions
    
    //initialize application.
    this->theApp->Initialize(argc, argv); 
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ApplicationRunner::Running() {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions

    if (this->DoCommandLineAction() == 0) {
        this->DoRunningLoop();
    }
    return 1;
}
    
//-----------------------------------------------------------------------------
int cpl_ApplicationRunner::Cleanup() {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions

    this->theApp->Cleanup();    
    return 1;
}

//----------------------------------------------------------------------------- 
int cpl_ApplicationRunner::DoRunningLoop() {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions
    
    this->theApp->RunMainLoop();
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ApplicationRunner::DoCommandLineAction() {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions
    
    if (this->Options[OPT_ID_SESSION]) {   
        this->theApp->RunSessionFile(this->sessionFileName);
        return 0;
    }
    if (this->Options[OPT_ID_LUA]) {   
        this->theApp->RunLuaScriptFile(this->luaFileName);
        return 0;
    }
    if (this->Options[OPT_ID_LUA_BUFFER]) {   
        this->theApp->RunLuaScriptCommand(this->luaCommandBuffer);
        return 0;
    }
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationRunner::SetLuaFileName(const char* fname) {
    //@@preconditions
    assert(fname != NULL);
    //@@end preconditions

    if (this->luaFileName != NULL) {
        delete[] this->luaFileName;
        this->luaFileName = NULL;
    }
    size_t slen = strlen(fname);
    this->luaFileName = new char[slen+1];
    strcpy(this->luaFileName, fname);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationRunner::SetLuaScriptBuffer(const char* script) {
    //@@preconditions
    assert(script != NULL);
    //@@end preconditions

    if (this->luaCommandBuffer != NULL) {
        delete[] this->luaCommandBuffer;
        this->luaCommandBuffer = NULL;
    }
    size_t slen = strlen(script);
    this->luaCommandBuffer = new char[slen+1];
    strcpy(this->luaCommandBuffer, script);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationRunner::SetSessionFileName(const char* fname) {
    //@@preconditions
    assert(fname != NULL);
    //@@end preconditions

    if (this->sessionFileName != NULL) {
        delete[] this->sessionFileName;
        this->sessionFileName = NULL;
    }
    size_t slen = strlen(fname);
    this->sessionFileName = new char[slen+1];
    strcpy(this->sessionFileName, fname);
}

//-----------------------------------------------------------------------------
cpl_ApplicationRunner::cpl_ApplicationRunner(cpl_Application * appInst) {
    for (int i = 0; i < MAX_OPTS; i++) {
        this->Options[i] = 0;
    }
    this->theApp     = appInst;
    this->cmdOptions = new CSimpleOpt();
    this->sessionFileName = 0;
    this->luaFileName = 0;
    this->luaCommandBuffer = 0;    
}

//-----------------------------------------------------------------------------
cpl_ApplicationRunner::~cpl_ApplicationRunner() {
    if (this->cmdOptions) {
        delete this->cmdOptions;
        this->cmdOptions = NULL;
    }
    if (this->luaCommandBuffer) {
        delete[] this->luaCommandBuffer;
        this->luaCommandBuffer = NULL;
    }
    if (this->luaFileName) {
        delete[] this->luaFileName;
        this->luaFileName = NULL;
    }
    if (this->sessionFileName) {
        delete[] this->sessionFileName;
        this->sessionFileName = NULL;
    }
}
