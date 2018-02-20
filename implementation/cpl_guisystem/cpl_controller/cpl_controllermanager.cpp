#include "cpl_controllerframeincludes.h"

//local includes.
#include <cpl_guiengine/cpl_guiengineframe/cpl_guiengineframeincludes.h>
#include "cpl_controller_items/cpl_scriptproxy.h"
#include "cpl_controller_items/cpl_plugintreeproxy.h"
#include "cpl_controller_items/cpl_fileioproxy.h"
#include "cpl_controller_items/cpl_multifileioproxy.h"
#include "cpl_controller_items/cpl_luaproxy.h"
#include "cpl_controller_items/cpl_sessionproxy.h"
#include "cpl_controller_items/cpl_iconproxy.h"
#include "cpl_controller_items/cpl_imageproxy.h"

//script..
//local includes.
#include <lua.hpp>
#include <lunar.h>
#include "cpl_controllermanagerluawrapper.h"

//-----------------------------------------------------------------------------
// class cpl_ControllerManager
//-----------------------------------------------------------------------------
//
cpl_ControllerManager * cpl_ControllerManager::New() {
   return cpl_ControllerObjectFactory::Instance()->CreateControlManager();
}

//-----------------------------------------------------------------------------
void cpl_ControllerManager::LoadServices() {
    //initialize controllers        
    cpl_ScriptProxy* scriptHandler = cpl_ScriptProxy::New();
    scriptHandler->SetControllerManager(this);
    scriptHandler->DoInitialization();
    this->InsertNextItem(scriptHandler);
    this->pControllerScript = scriptHandler;

    //initialize LUA proxy
    cpl_LuaProxy* luaProxy = cpl_LuaProxy::New();
    luaProxy->SetControllerManager(this);    
    luaProxy->DoInitialization();
    this->InsertNextItem(luaProxy);
    this->pControllerLuaScript = luaProxy;
    this->pControllerLuaScript->CreateScriptContext();

    //register lib
    this->RegisterScriptLib();

    //initialize plugin tree proxy     
    cpl_PluginTreeProxy* pluginTreeHandler = cpl_PluginTreeProxy::New();
    pluginTreeHandler->SetControllerManager(this);
    pluginTreeHandler->DoInitialization();
    pluginTreeHandler->Parse("plugins");
    pluginTreeHandler->SetLuaState(luaProxy->GetMainLuaState());
    pluginTreeHandler->LoadLuaScriptPackage();
    pluginTreeHandler->LoadLuaRuntimePackage();
    this->InsertNextItem(pluginTreeHandler);
    this->pControllerPluginTree = pluginTreeHandler;

    //initial session proxy
    cpl_SessionProxy* sessionHandler = cpl_SessionProxy::New();
    assert(sessionHandler != NULL);
    sessionHandler->DoInitialization();
    this->InsertNextItem(sessionHandler);
    this->pControllerSession = sessionHandler;

    //initialize image proxy
    cpl_ImageProxy* imageHandler = cpl_ImageProxy::New();
    assert(imageHandler != NULL);
    imageHandler->DoInitialization();
    imageHandler->SetPluginTreeProxy(this->pControllerPluginTree);
    imageHandler->SetLuaScriptProxy(this->pControllerLuaScript);
    imageHandler->LoadPluginImages();
    this->InsertNextItem(imageHandler);
    this->pControllerImage = imageHandler;

    //initialize icon proxy
    cpl_IconProxy* iconHandler = cpl_IconProxy::New();
    assert(iconHandler != NULL);
    iconHandler->DoInitialization();
    iconHandler->SetPluginTreeProxy(this->pControllerPluginTree);
    iconHandler->SetLuaScriptProxy(this->pControllerLuaScript);
    iconHandler->LoadPluginIcons();
    this->InsertNextItem(iconHandler);
    this->pControllerIcon = iconHandler;

    //register lua script.
    lua_State* _pVM = (lua_State*)luaProxy->GetMainLuaState();
    Lunar<cpl_ControllerManagerLuaWrapper>::Register(_pVM);
    this->luaWrapper = new cpl_ControllerManagerLuaWrapper(NULL);
    this->luaWrapper->DoInitialization(this);

    int userdata_index = Lunar<cpl_ControllerManagerLuaWrapper>::push(_pVM, this->luaWrapper);
    lua_pushliteral(_pVM, "cpl_app");
    lua_pushvalue(_pVM, userdata_index);
    lua_settable(_pVM, LUA_GLOBALSINDEX);
}

//-----------------------------------------------------------------------------
void cpl_ControllerManager::DoInitialization(int argc, char ** argv) {
    //@@preconditions
    assert(this->pControllerScript != NULL);
    assert(this->pControllerPluginTree != NULL);
    assert(this->pControllerIcon != NULL);
    assert(this->pControllerImage != NULL);
    //@@end preconditions

    //initialize GUI engine.
    this->mainGUIEngine = cpl_GUIEngine::New();
    this->mainGUIEngine->SetControllerManager(this);
    this->mainGUIEngine->SetMainScripHandler(this->pControllerScript->GetScriptHandler());
    this->mainGUIEngine->SetMainPluginTree(this->pControllerPluginTree->GetPluginTree());
    this->mainGUIEngine->SetMainImageProxy(this->pControllerImage->GetImageProxy());
    this->mainGUIEngine->SetMainIconProxy(this->pControllerIcon->GetIconProxy());
    this->mainGUIEngine->Initialize(argc, argv);
    this->mainGUIEngine->ShowMainWindow(true);
 
    //load gui proxy.    
    cpl_FileIOController* pFileIOProxy = cpl_FileIOController::New();
    pFileIOProxy->SetControllerManager(this);
    pFileIOProxy->DoInitialization();
    this->InsertNextItem(pFileIOProxy);
    this->pControllerFileIO = pFileIOProxy;

    cpl_MultiFileIOController* pMultiFileIOProxy = cpl_MultiFileIOController::New();
    pMultiFileIOProxy->SetControllerManager(this);
    pMultiFileIOProxy->DoInitialization();
    this->InsertNextItem(pMultiFileIOProxy);
    this->pControllerMultiFileIO = pMultiFileIOProxy;  
}

//-----------------------------------------------------------------------------
void cpl_ControllerManager::DoCleanup() {
    //@@preconditions
    assert(this->mainGUIEngine != NULL);
    //@@end preconditions
    
    //release resource for main gui engine
    this->mainGUIEngine->Cleanup();

    //cleanup.
    if (this->luaWrapper != NULL) {
        this->luaWrapper->DoCleanup();
        delete this->luaWrapper;
        this->luaWrapper = NULL;
    }

    //call superclass.
    cpl_ControllerSet::DoCleanup();    
    cpl_ObjectFactory::DeInit();
}

//-----------------------------------------------------------------------------
void cpl_ControllerManager::EnterEventLoop() {
    //@@preconditions
    assert(this->mainGUIEngine != NULL);
    //@@end preconditions

    this->mainGUIEngine->EnterMainLoop();  
}

//-----------------------------------------------------------------------------
void cpl_ControllerManager::SetBreakFlagOn() {
    //@@preconditions
    assert(this->mainGUIEngine != NULL);
    //@@end preconditions

    this->mainGUIEngine->SetBreakFlagOn();
}

//-----------------------------------------------------------------------------
cpl_GUIEngine* cpl_ControllerManager::GetGUIEngine() {
    //@@preconditions
    assert(this->mainGUIEngine != NULL);
    //@@end preconditions

    return this->mainGUIEngine;
}

//-----------------------------------------------------------------------------
int cpl_ControllerManager::RegisterInterfaces(char* path_name, char* name, void* data) {
    //@@preconditions
    assert(path_name != NULL);
    assert(name != NULL);
    assert(this->pControllerPluginTree != NULL);
    //@@end preconditions

    IPluginTree* pluginTree = this->pControllerPluginTree->GetPluginTree();
    assert(pluginTree != NULL);

    IPluginTreePath* path = pluginTree->GetTreePath(path_name);
    if (path == NULL) {    
        path = pluginTree->CreateTreePath(path_name);    
    }  
    assert(path != NULL);    
    path->SetUserData(data);
    return 0;
}

//-----------------------------------------------------------------------------
void* cpl_ControllerManager::GetPluginTree() {
    //@@preconditions
    assert(this->pControllerPluginTree != NULL);
    //@@end preconditions

    return this->pControllerPluginTree->GetPluginTree();
}

//-----------------------------------------------------------------------------
void* cpl_ControllerManager::GetFileIOHandler() {
    //@@preconditions
    assert(this->pControllerFileIO != NULL);
    //@@end preconditions

    return this->pControllerFileIO->GetImplementation();
}

//-----------------------------------------------------------------------------
void* cpl_ControllerManager::GetMultiFileIOHandler() {
    //@@preconditions
    assert(this->pControllerMultiFileIO != NULL);
    //@@end preconditions

    return this->pControllerMultiFileIO->GetImplementation();
}

//-----------------------------------------------------------------------------
void* cpl_ControllerManager::GetLuaScript() {
    //@@preconditions
    assert(this->pControllerLuaScript != NULL);
    //@@end preconditions

    return this->pControllerLuaScript->GetImplementation();
}

//-----------------------------------------------------------------------------
void* cpl_ControllerManager::GetSessionProxy() {
    //@@preconditions
    assert(this->pControllerSession != NULL);
    //@@end preconditions

    return this->pControllerSession->GetImplementation();
}

//-----------------------------------------------------------------------------
void* cpl_ControllerManager::GetIconProxy() {
    //@@preconditions
    assert(this->pControllerIcon != NULL);
    //@@end preconditions

    return this->pControllerIcon->GetIconProxy();
}

//-----------------------------------------------------------------------------
void* cpl_ControllerManager::GetImageProxy() {
    //@@preconditions
    assert(this->pControllerImage != NULL);
    //@@end preconditions

    return this->pControllerImage->GetImageProxy();
}

//-----------------------------------------------------------------------------
void cpl_ControllerManager::RunLuaScriptFile(const char* fname) {
    //@@preconditions
    assert(this->pControllerLuaScript != NULL);
    assert(fname != NULL);
    //@@end preconditions

    this->pControllerLuaScript->RunScriptFile(fname);        
}

//-----------------------------------------------------------------------------
void cpl_ControllerManager::RunLuaScriptCommand(const char* buffer) {
    //@@preconditions
    assert(this->pControllerLuaScript != NULL);
    assert(buffer != NULL);
    //@@end preconditions

    this->pControllerLuaScript->Execute(buffer);        
}

//-----------------------------------------------------------------------------
int cpl_ControllerManager::SetEnabled(int state) {
    int old = this->IsEnabled;
    this->IsEnabled = state;
    return old;
}

//-----------------------------------------------------------------------------
int cpl_ControllerManager::GetEnabled() {
    return this->IsEnabled;
}

//-----------------------------------------------------------------------------
// EVENT HANDLER
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int cpl_ControllerManager::DoCommand(char* scriptcomand, void* userData, char* cmdData) {
    //@@preconditions
    assert(scriptcomand != NULL);
    assert(strlen(scriptcomand) > 0);
    //@@end preconditions

    return 0;
}

//-----------------------------------------------------------------------------
cpl_ControllerManager::cpl_ControllerManager() {
    this->ObjectCreator = NULL;    
    this->mainGUIEngine = NULL;
    this->IsInitialized = 0;
    this->IsEnabled     = 0;

    //
    this->luaWrapper = NULL;

    //controller items.
    this->pControllerScript     = NULL;
    this->pControllerLuaScript  = NULL;
    this->pControllerPluginTree = NULL;
    this->pControllerSession    = NULL;
    this->pControllerFileIO     = NULL;
    this->pControllerIcon       = NULL;
    this->pControllerImage      = NULL;
}

//-----------------------------------------------------------------------------
cpl_ControllerManager::~cpl_ControllerManager() {
    if (this->mainGUIEngine != NULL) {
        this->mainGUIEngine->Release();
        this->mainGUIEngine = NULL;
    }
    if (this->ObjectCreator != NULL) {
        this->ObjectCreator->Release();
        this->ObjectCreator = NULL;
    }
}
