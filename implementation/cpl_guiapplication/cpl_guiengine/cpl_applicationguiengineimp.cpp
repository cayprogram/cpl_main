#include "cpl_applicationguiengineimpincludes.h"

//local includes.
#include "cpl_wxguiobjects/cpl_wxguiobjectincludes.h"
#include "cpl_wxguiobjects/cpl_wxsystemfileio.h"
#include "cpl_wxguiobjects/cpl_wxsystemmultifileio.h"

//-----------------------------------------------------------------------------
// class cpl_ApplicationGUIEngineImp
//-----------------------------------------------------------------------------
//
void cpl_ApplicationGUIEngineImp::Initialize(int argc, char * * argv) {   
    //@@preconditions
    assert(this->theApp == NULL);
    //@@end preconditions
    
    //initialize system file io
    cpl_SystemFileIO::SetInstance(new cpl_wxSystemFileIO);
    cpl_SystemMultiFileIO::SetInstance(new cpl_wxSystemMultiFileIO);

    this->theApp = new cpl_wxApp(this);
    wxApp::SetInstance(this->theApp);
    wxEntryStart(argc, argv);
    this->theApp->OnInit();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::Cleanup() {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions

    //release system file io.
    cpl_SystemMultiFileIO::Delete();
    cpl_SystemFileIO::Delete();
    cpl_SystemConfig::Delete();

    //clean app.
    this->theApp->OnExit();
    wxEntryCleanup();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::EnterMainLoop() {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions
    
    this->theApp->OnRun();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::SetBusyFlagOn() {
    //@@preconditions
    assert(this->engineGUI != NULL);
    //@@end preconditions

    this->engineGUI->SetBusyFlagOn();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::SetBusyFlagOff() {
    //@@preconditions
    assert(this->engineGUI != NULL);
    //@@end preconditions

    this->engineGUI->SetBusyFlagOff();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::SetBreakFlagOn() {
    //@@preconditions
    assert(this->theApp != NULL);
    //@@end preconditions

    this->theApp->SetShouldLeave(true);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::UpdateGUI() {
    //@@preconditions
    assert(this->engineGUI != NULL);
    //@@end preconditions

    this->engineGUI->UpdateCommandGUI();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::SetWindowTitle(const char* title) {
    //@@preconditions
    assert(this->engineGUI != NULL);
    //@@end preconditions

    this->engineGUI->SetWindowTitle(title);
}

//-----------------------------------------------------------------------------
int cpl_ApplicationGUIEngineImp::ExecCheckFunction() {
    //@@postconditions
    assert(this->pRuntimeContext != NULL);
    //@@end preconditions

    if (this->pCheckFunc.checkFunction != NULL) {
        this->pCheckFunc.checkFunction(this->pCheckFunc.data);
        return 1;
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_ApplicationGUIEngineImp::ExecIdleFunction() {
    //@@postconditions
    assert(this->pRuntimeContext != NULL);
    //@@end preconditions

    if (this->pIdleFunc.checkFunction != NULL) {
        this->pIdleFunc.checkFunction(this->pCheckFunc.data);
        return 1;
    }
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::AddCheckFunction(CHECKFUNC func, void* data) {
    //@@precondition
    //@@end preconditions

    this->pCheckFunc.checkFunction = func;
    this->pCheckFunc.data          = data;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RemoveCheckFunction() {
    //@@precondition
    //@@end preconditions
    
    this->pCheckFunc.checkFunction = NULL;
    this->pCheckFunc.data = NULL;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::AddIdleFunction(CHECKFUNC func, void* data) {
    //@@precondition
    //@@end preconditions
    
    this->pIdleFunc.checkFunction = func;
    this->pIdleFunc.data          = data;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RemoveIdleFunction() {
    //@@precondition
    //@@end preconditions
    
    this->pIdleFunc.checkFunction = NULL;
    this->pIdleFunc.data = NULL;
}

//-----------------------------------------------------------------------------
int cpl_ApplicationGUIEngineImp::ExecGraphicEngineIdleCallback() {
    //@@precondition
    assert(this->engineGUI != NULL);
    //@@end preconditions

    return this->engineGUI->ExecGraphicEngineIdleCallback();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::SetGUIEngine(cpl_GUIEngine* engine) {
    //@@precondition
    assert(engine != NULL);
    //@@end preconditions

    this->engineGUI = engine;
}
