#include <cpl_controller/cpl_controllerframeincludes.h>
#include "cpl_luaproxy.h"
#include "cpl_plugintreeproxy.h"
#include "cpl_imageproxy.h"

//-----------------------------------------------------------------------------
// class cpl_ImageProxy::cpl_Implemenation
//-----------------------------------------------------------------------------
//
class cpl_ImageProxy::cpl_Implemenation : public cpl_ImageCommonProxy {   
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
CPL_StandardNewCommandMacro(cpl_ImageProxy::cpl_Implemenation);

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// class cpl_ImageProxy
//-----------------------------------------------------------------------------
//
cpl_ImageProxy* cpl_ImageProxy::New() {
    return new cpl_ImageProxy;
}

//-----------------------------------------------------------------------------
void cpl_ImageProxy::DoInitialization() {
    //@@preconditions
    assert(this->Implementaion == NULL);
    //@@end preconditions

    this->Implementaion = cpl_Implemenation::New();   
}

//-----------------------------------------------------------------------------
void cpl_ImageProxy::DoCleanup() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->Release();
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
int cpl_ImageProxy::LoadPluginImages() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    return this->Implementaion->LoadPluginImages();
}

//-----------------------------------------------------------------------------
void cpl_ImageProxy::SetPluginTreeProxy(cpl_PluginTreeProxy * pltreePorxy) {
    //@@preconditions
    assert(pltreePorxy != NULL);
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->SetPluginTreeProxy(pltreePorxy->GetPluginTree());
}

//-----------------------------------------------------------------------------
void cpl_ImageProxy::SetLuaScriptProxy(cpl_LuaProxy * luascriptProxy) {
    //@@preconditions
    assert(luascriptProxy != NULL);
    assert(this->Implementaion != NULL);
    //@@end preconditions

    this->Implementaion->SetLuaScriptProxy(luascriptProxy->GetImplementation());
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_ImageProxy::GetImageProxy() {
    return this->Implementaion;
}

//-----------------------------------------------------------------------------
cpl_ImageProxy::cpl_ImageProxy() {
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
cpl_ImageProxy::~cpl_ImageProxy() {
    assert(this->Implementaion == NULL);
}
