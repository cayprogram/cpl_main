#include <cpl_controller/cpl_controllerframeincludes.h>
#include "cpl_luaproxy.h"
#include "cpl_plugintreeproxy.h"
#include "cpl_iconproxy.h"

//-----------------------------------------------------------------------------
// class cpl_IconProxy::cpl_Implemenation
//-----------------------------------------------------------------------------
//
class cpl_IconProxy::cpl_Implemenation : public cpl_IconCommonProxy {   
public:
    /** create instance */
    static cpl_Implemenation* New();

public:
    //constructor
    cpl_Implemenation() {}

    //destructor.
    virtual ~cpl_Implemenation() {}
};

//-----------------------------------------------------------------------------
CPL_StandardNewCommandMacro(cpl_IconProxy::cpl_Implemenation);

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// class cpl_IconProxy
//-----------------------------------------------------------------------------
//
cpl_IconProxy* cpl_IconProxy::New() {
    return new cpl_IconProxy;
}

//-----------------------------------------------------------------------------
void cpl_IconProxy::DoInitialization() {
    //@@preconditions
    assert(this->Implementaion == NULL);
    //@@end preconditions

    this->Implementaion = cpl_Implemenation::New();   
}

//-----------------------------------------------------------------------------
void cpl_IconProxy::DoCleanup() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->Release();
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
int cpl_IconProxy::LoadPluginIcons() {
    return this->Implementaion->LoadPluginIcons();
}

//-----------------------------------------------------------------------------
void cpl_IconProxy::SetPluginTreeProxy(cpl_PluginTreeProxy * pltreePorxy) {
    //@@preconditions
    assert(pltreePorxy != NULL);
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->SetPluginTreeProxy(pltreePorxy->GetPluginTree());
}

//-----------------------------------------------------------------------------
void cpl_IconProxy::SetLuaScriptProxy(cpl_LuaProxy * luascriptProxy) {
    //@@preconditions
    assert(luascriptProxy != NULL);
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->SetLuaScriptProxy(luascriptProxy->GetImplementation());
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_IconProxy::GetIconProxy() {
    return this->Implementaion;
}

//-----------------------------------------------------------------------------
cpl_IconProxy::cpl_IconProxy() {
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
cpl_IconProxy::~cpl_IconProxy() {
    assert(this->Implementaion == NULL);
}
