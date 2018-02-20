#include "cpl_guiengineframeincludes.h"

//local includes.
#include <cpl_controller/cpl_controllerframeincludes.h>

//-----------------------------------------------------------------------------
// class cpl_GUIEngine
//-----------------------------------------------------------------------------
//
cpl_GUIEngine * cpl_GUIEngine::New() {
    return new cpl_GUIEngine;
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::Release() {
    delete this;
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::Initialize(int argc, char * * argv) {
    //@@preconditions
    assert(this->guiEngineImp != NULL);
    assert(this->mainWindow   != NULL);
    //@@end preconditions

    this->guiEngineImp->Initialize(argc, argv);
    this->mainWindow->DoInitialization();
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::Cleanup() {
    //@@preconditions
    assert(this->guiEngineImp != NULL);
    assert(this->mainWindow   != NULL);
    //@@end preconditions

    this->mainWindow->DoCleanup();
    this->guiEngineImp->Cleanup();
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::ShowMainWindow(bool bshow) {
    //@@preconditions
    assert(this->guiEngineImp != NULL);
    assert(this->mainWindow   != NULL);
    //@@end preconditions
    
    this->mainWindow->Show(bshow);
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::EnterMainLoop(void) {
    //@@preconditions
    assert(this->guiEngineImp != NULL);
    //@@end preconditions
    
    this->guiEngineImp->EnterMainLoop();
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetBusyFlagOn() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    assert(this->controllerManager != NULL);
    //@@end preconditions

    this->mainWindow->SetBusyOnOff(1);
    this->controllerManager->SetEnabled(0);
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetBusyFlagOff() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    assert(this->controllerManager != NULL);
    //@@end preconditions

    this->mainWindow->SetBusyOnOff(0);
    this->controllerManager->SetEnabled(1);
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetOutputWindowOnOff() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    this->mainWindow->SetOutputWindowOnOff();
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetBreakFlagOn() {
    //@@preconditions
    assert(this->guiEngineImp != NULL);
    //@@end preconditions

    this->guiEngineImp->SetBreakFlagOn();
}

//-----------------------------------------------------------------------------
void* cpl_GUIEngine::GetMainWindowHandler() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetMainWindowRawHandler();
}

//-----------------------------------------------------------------------------
void* cpl_GUIEngine::GetSystemWindowRawHandler() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetSystemWindowRawHandler();
}

//-----------------------------------------------------------------------------
void* cpl_GUIEngine::GetSessionWindowRawHandler() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetSessionWindowRawHandler();
}

//-----------------------------------------------------------------------------
ILayoutProxy* cpl_GUIEngine::GetLayoutProxy() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetLayoutProxy();
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_GUIEngine::GetIconProxy() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetIconProxy();
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_GUIEngine::GetImageProxy() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetImageProxy();
}

//-----------------------------------------------------------------------------
IThreadFunc* cpl_GUIEngine::GetThreadFunc() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetThreadFunc();
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::UpdateCommandGUI() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions
    
    this->mainWindow->UpdateCommandGUI();
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetWindowTitle(const char* hint) {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    this->mainWindow->SetWindowTitle(hint);
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetMainScripHandler(cpl_Action* handler) {
    //@@preconditions
    assert(handler != NULL);
    assert(this->mainWindow != NULL);
    //@@end preconditions

    this->mainWindow->SetMainScripHandler(handler);
}

//GUI service interface implementations.
//-----------------------------------------------------------------------------
IPanelProxy* cpl_GUIEngine::GetTaskPanelProxy() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetTaskPanelProxy();
}

//-----------------------------------------------------------------------------
IOutputMessage* cpl_GUIEngine::GetOutputMessage() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetOutputMessage(); 
}

//-----------------------------------------------------------------------------
IOutputStatusInfo* cpl_GUIEngine::GetOutputStatusInfoHandler() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetOutputStatusInfoHandler(); 
}

//-----------------------------------------------------------------------------
IGraphicWindowInfo* cpl_GUIEngine::GetGraphicWindowInfoHandler() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->GetGraphicWindowInfoHandler(); 
}

//-----------------------------------------------------------------------------
IRuntimeContextProxy* cpl_GUIEngine::GetRuntimeContextProxy() {
    //@@preconditions
    assert(this->guiEngineImp != NULL);
    //@@end preconditions

    return this->guiEngineImp->GetRuntimeContextProxy(); 
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetMainPluginTree(IPluginTree* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->SetMainPluginTree(plugin); 
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetMainIconProxy(IResImageProxy* icon) {
    //@@preconditions
    assert(icon != NULL);
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->SetMainIconProxy(icon); 
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetMainImageProxy(IResImageProxy* image) {
    //@@preconditions
    assert(image != NULL);
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->SetMainImageProxy(image); 
}

//-----------------------------------------------------------------------------
int cpl_GUIEngine::ExecGraphicEngineIdleCallback() {
    //@@preconditions
    assert(this->mainWindow != NULL);
    //@@end preconditions

    return this->mainWindow->ExecGraphicEngineIdleCallback();
}

//-----------------------------------------------------------------------------
void cpl_GUIEngine::SetControllerManager(cpl_ControllerManager* pManager) {
    //@@preconditions
    assert(pManager != NULL);
    //@@end preconditions

    this->controllerManager = pManager;
}

//-----------------------------------------------------------------------------
cpl_GUIEngine::cpl_GUIEngine() {
    this->controllerManager = NULL;
    this->guiEngineImp      = cpl_GUIObjectFactory::Instance()->CreateGUIEngineImp();
    this->mainWindow        = cpl_MainWindow::New();

    //link
    this->guiEngineImp->SetGUIEngine(this);
}

//-----------------------------------------------------------------------------
cpl_GUIEngine::~cpl_GUIEngine() {
    if (this->guiEngineImp != NULL) {
        delete this->guiEngineImp;
    }
    if (this->mainWindow != NULL) {
        delete this->mainWindow;
    }
}
