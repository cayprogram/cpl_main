#include "cpl_applicationguiengineimpincludes.h"

//local includes.
#include "cpl_wxguiobjects/cpl_wxguiobjectincludes.h"

//-----------------------------------------------------------------------------
// class cpl_ApplicationMainWindowImp
//-----------------------------------------------------------------------------
//
void cpl_ApplicationMainWindowImp::EnterWindowInitialization() {
    //@@preconditions
    assert(this->mainWin == NULL);
    //@@end preconditions

    int w = wxSystemSettings::GetMetric(wxSYS_SCREEN_X)-50;
    int h = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)-50;    
    this->mainWin = new cpl_wxMainFrame(this, "wxWidgets 3D_Application demo 1.0", wxSize(w,h));
    this->Owner->SetWindowUserData(this->mainWin);

    //store..
    cpl_SystemConfig::Instance()->SetMainWindowHandler(this->mainWin);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationMainWindowImp::LeaveWindowInitialization() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    this->mainWin->Create();
    this->mainWin->Maximize(true);

    //set top window.
    wxTheApp->SetTopWindow(this->mainWin);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationMainWindowImp::ShowWindow(bool bshow) {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    this->mainWin->Show(bshow);
}

//-----------------------------------------------------------------------------
void* cpl_ApplicationMainWindowImp::GetMainWindowRawHandler() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin;
}

//-----------------------------------------------------------------------------
void* cpl_ApplicationMainWindowImp::GetSystemWindowRawHandler() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetSystemWindowRawHandler();
}

//-----------------------------------------------------------------------------
void* cpl_ApplicationMainWindowImp::GetSessionWindowRawHandler() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetSessionWindowRawHandler();
}

//GUI service interface implementations.
//-----------------------------------------------------------------------------
IPanelProxy* cpl_ApplicationMainWindowImp::GetTaskPanelProxy() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetTaskPanelProxy();
}

//-----------------------------------------------------------------------------
IOutputMessage* cpl_ApplicationMainWindowImp::GetOutputMessage() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetOutputMessage();
}

//-----------------------------------------------------------------------------
IOutputStatusInfo* cpl_ApplicationMainWindowImp::GetOutputStatusInfoHandler() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetOutputStatusInfoHandler(); 
}

//-----------------------------------------------------------------------------
IGraphicWindowInfo* cpl_ApplicationMainWindowImp::GetGraphicWindowInfoHandler() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetGraphicWindowInfoHandler(); 
}

//-----------------------------------------------------------------------------
ILayoutProxy* cpl_ApplicationMainWindowImp::GetLayoutProxyImp() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetLayoutProxyImp();
}

//-----------------------------------------------------------------------------
IPluginTree* cpl_ApplicationMainWindowImp::GetPluginTree() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetPluginTree();
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_ApplicationMainWindowImp::GetIconProxy() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetIconProxy();
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_ApplicationMainWindowImp::GetImageProxy() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetImageProxy();
}

//-----------------------------------------------------------------------------
IThreadFunc* cpl_ApplicationMainWindowImp::GetThreadFunc() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->GetThreadFunc();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationMainWindowImp::UpdateGUI() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    this->mainWin->UpdateGUI();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationMainWindowImp::SetWindowTitle(const char* title) {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    this->mainWin->SetWindowTitle(title);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationMainWindowImp::Cleanup() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    this->mainWin->Cleanup();
    delete this->mainWin;
    this->mainWin = NULL;
}

//-----------------------------------------------------------------------------
int cpl_ApplicationMainWindowImp::ExecGraphicEngineIdleCallback() {
    //@@precondition
    assert(this->mainWin != NULL);
    //@@end preconditions

    return this->mainWin->ExecGraphicEngineIdleCallback();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationMainWindowImp::SetBusyOnOff(int state) {
    //@@preconditions
    assert(state == 0 || state == 1);
    assert(this->mainWin != NULL);
    //@@end preconditions

    this->mainWin->SetBusyOnOff(state);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationMainWindowImp::SetOutputWindowOnOff() {
    //@@preconditions
    assert(this->mainWin != NULL);
    //@@end preconditions

    this->mainWin->SetOutputWindowOnOff();
}

//-----------------------------------------------------------------------------
cpl_ApplicationMainWindowImp::cpl_ApplicationMainWindowImp(cpl_MainWindow* pOwner) : cpl_MainWindowImp(pOwner) {
    this->mainWin = NULL;
}

//-----------------------------------------------------------------------------
cpl_ApplicationMainWindowImp::~cpl_ApplicationMainWindowImp() {
    assert(this->mainWin == NULL);
}
