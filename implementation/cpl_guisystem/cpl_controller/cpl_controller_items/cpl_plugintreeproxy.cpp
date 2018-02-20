#include <cpl_controller/cpl_controllerframeincludes.h>
#include "cpl_plugintreeproxy.h"

//-----------------------------------------------------------------------------
// class cpl_PluginTreeProxy::cpl_Implemenation
//-----------------------------------------------------------------------------
//
class cpl_PluginTreeProxy::cpl_Implemenation : public cpl_PluginTree {   
public:
    /** create instance */
    static cpl_Implemenation* New();

    /** parse */
    virtual int Parse(const char* path);

public:
    //constructor
    cpl_Implemenation() {}

    //destructor.
    virtual ~cpl_Implemenation() {}
};

//-----------------------------------------------------------------------------
CPL_StandardNewCommandMacro(cpl_PluginTreeProxy::cpl_Implemenation);

//-----------------------------------------------------------------------------
int cpl_PluginTreeProxy::cpl_Implemenation::Parse(const char* path) {
    //@@preconditions
    assert(path != NULL);
    //@@end preconditions
    
    char * application_path = cpl_SystemConfig::Instance()->GetApplicationDirectory();
    assert(application_path != NULL);
    
    //parse.
    char* pluginPath = cpl_SystemTools::AppendPath(application_path, "plugins");
    return this->cpl_PluginTree::Parse(pluginPath);
}

//-----------------------------------------------------------------------------
// class cpl_PluginTreeProxy
//-----------------------------------------------------------------------------
//
cpl_PluginTreeProxy* cpl_PluginTreeProxy::New() {
    return new cpl_PluginTreeProxy;
}

//-----------------------------------------------------------------------------
void cpl_PluginTreeProxy::DoInitialization() {
    //@@preconditions
    assert(this->Implementaion == NULL);
    //@@end preconditions

    this->Implementaion = cpl_Implemenation::New();   
}

//-----------------------------------------------------------------------------
void cpl_PluginTreeProxy::DoCleanup() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->Release();
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
int cpl_PluginTreeProxy::Parse(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(this->Implementaion != NULL);
    //@@end preconditions

    return this->Implementaion->Parse(path);
}

//-----------------------------------------------------------------------------
int cpl_PluginTreeProxy::LoadLuaScriptPackage() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    return this->Implementaion->LoadLuaScriptPackage();
}

//-----------------------------------------------------------------------------
int cpl_PluginTreeProxy::LoadLuaRuntimePackage() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    return this->Implementaion->LoadLuaRuntimePackage();
}

//-----------------------------------------------------------------------------
int cpl_PluginTreeProxy::SetLuaState(void* luaState) {
    //@@preconditions
    assert(luaState != NULL);
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->SetLuaState(luaState);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_PluginTreeProxy::LoadClassCreatorRuntimePackage(cpl_Creator* pCreator) {
    //@@preconditions
    assert(pCreator != NULL);
    assert(this->Implementaion != NULL);
    //@@end preconditions

    return this->Implementaion->LoadClassCreatorRuntimePackage(pCreator);
}

//-----------------------------------------------------------------------------
IPluginTree* cpl_PluginTreeProxy::GetPluginTree() {
    return this->Implementaion;
}

//-----------------------------------------------------------------------------
cpl_PluginTreeProxy::cpl_PluginTreeProxy() {
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
cpl_PluginTreeProxy::~cpl_PluginTreeProxy() {
    assert(this->Implementaion == NULL);
}
