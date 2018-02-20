#include "cpl_guisystemincludes.h"
#include "cpl_application.h"

//local includes.
#include <cpl_controller/cpl_controllerframeincludes.h>
#include <cpl_guiengine/cpl_guiengineframe/cpl_guiengineframeincludes.h>

//-----------------------------------------------------------------------------
// class cpl_Application
//-----------------------------------------------------------------------------
//
cpl_Application * cpl_Application::instance = NULL;

//-----------------------------------------------------------------------------
cpl_Application * cpl_Application::Instance() {
    if (cpl_Application::instance == NULL) {
        cpl_Application::instance = new cpl_Application;
    }
    return cpl_Application::instance;
}

//-----------------------------------------------------------------------------
void cpl_Application::Delete() {
    if (cpl_Application::instance) {
        delete cpl_Application::instance;
        cpl_Application::instance = NULL;
    }
}

//-----------------------------------------------------------------------------
void cpl_Application::SetBreakFlagOn() {
    //@@preconditions
    assert(this->mainControllerManager != NULL);
    //@@end preconditions

    this->mainControllerManager->SetBreakFlagOn();
}

//-----------------------------------------------------------------------------
void cpl_Application::SetBusyFlagOn() {
    //@@preconditions
    assert(this->mainControllerManager != NULL);
    //@@end preconditions

    this->mainControllerManager->GetGUIEngine()->SetBusyFlagOn();   
}

//-----------------------------------------------------------------------------
void cpl_Application::SetBusyFlagOff() {
    //@@preconditions
    assert(this->mainControllerManager != NULL);
    //@@end preconditions

    this->mainControllerManager->GetGUIEngine()->SetBusyFlagOff();   
}

//-----------------------------------------------------------------------------
void cpl_Application::SetApplication(cpl_Application* app) {
    cpl_Application::instance = app;
}

//-----------------------------------------------------------------------------
void cpl_Application::Initialize(int argc, char * * argv) {
    this->mainControllerManager = cpl_ControllerManager::New();	
    this->mainControllerManager->DoInitialization(argc, argv);    
}

//-----------------------------------------------------------------------------
void cpl_Application::Cleanup() {
    //@@preconditions
    assert(this->mainControllerManager != NULL);
    //@@end preconditions

    //clean main control manager.
    this->mainControllerManager->DoCleanup();

    //shutdown man control manager.
    if (this->mainControllerManager != NULL) {
        this->mainControllerManager->Release();
        this->mainControllerManager = NULL;
    }
}

//-----------------------------------------------------------------------------
void cpl_Application::RunMainLoop() {
    //@@preconditions
    assert(this->mainControllerManager != NULL);
    //@@end preconditions
    
    this->mainControllerManager->EnterEventLoop();
}

//-----------------------------------------------------------------------------
void cpl_Application::SetWindowTitle(const char* title) {
    //@@preconditions
    assert(this->mainControllerManager != NULL);
    //@@end preconditions 

    this->mainControllerManager->GetGUIEngine()->SetWindowTitle(title);
}

//-----------------------------------------------------------------------------
void cpl_Application::RunSessionFile(const char* fname) {
    //@@preconditions
    assert(fname != NULL);
    assert(this->mainControllerManager != NULL);
    //@@end preconditions
    
    this->mainControllerManager->RunSessionFile(fname);
}

//-----------------------------------------------------------------------------
void cpl_Application::RunLuaScriptFile(const char* fname) {
    //@@preconditions
    assert(fname != NULL);
    assert(this->mainControllerManager != NULL);
    //@@end preconditions
    
    this->mainControllerManager->RunLuaScriptFile(fname);
}

//-----------------------------------------------------------------------------
void cpl_Application::RunLuaScriptCommand(const char* buffer) {
    //@@preconditions
    assert(buffer != NULL);
    assert(this->mainControllerManager != NULL);
    //@@end preconditions
    
    this->mainControllerManager->RunLuaScriptCommand(buffer);
}

//-----------------------------------------------------------------------------
cpl_Application::cpl_Application(): mainControllerManager(0) {
}

//-----------------------------------------------------------------------------
cpl_Application::~cpl_Application() {
    assert(this->mainControllerManager == NULL);
}
