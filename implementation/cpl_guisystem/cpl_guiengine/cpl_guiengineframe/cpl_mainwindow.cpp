#include "cpl_guiengineframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_MainWindow
//-----------------------------------------------------------------------------
//
cpl_MainWindow* cpl_MainWindow::New() {
    return new cpl_MainWindow;
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::DoInitialization() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    this->WindowInitialization();
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::DoCleanup() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    this->mainWinImp->Cleanup();
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::WindowInitialization() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    //start initialization.
    this->mainWinImp->EnterWindowInitialization();

    //create sub controls
    this->CreateSubWindows();

    //end initialization.
    this->mainWinImp->LeaveWindowInitialization();  
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::CreateSubWindows() {
    //@@preconditions
    //@@end preconditions    
}

//-----------------------------------------------------------------------------
void* cpl_MainWindow::GetMainWindowRawHandler() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetMainWindowRawHandler();
}

//-----------------------------------------------------------------------------
void* cpl_MainWindow::GetSystemWindowRawHandler() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetSystemWindowRawHandler();
}

//-----------------------------------------------------------------------------
void* cpl_MainWindow::GetSessionWindowRawHandler() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetSessionWindowRawHandler();
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::SetMainScripHandler(cpl_Action* handler) {
    //@@preconditions
    assert(handler != NULL);
    //@@end preconditions

    this->mainScriptHandler = handler;
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::GetMainScripHandler(cpl_Action*& handler) {
    //@@preconditions
    assert(handler == NULL);
    //@@end preconditions

    handler = this->mainScriptHandler; 
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::Show(bool bshow) {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    this->mainWinImp->ShowWindow(bshow);
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::UpdateCommandGUI() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    this->mainWinImp->UpdateGUI();
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::SetWindowTitle(const char* hint) {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    this->mainWinImp->SetWindowTitle(hint);
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::SetBusyOnOff(int state) {
    //@@preconditions
    assert(state == 0 || state == 1);
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    this->mainWinImp->SetBusyOnOff(state);
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::SetOutputWindowOnOff() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    this->mainWinImp->SetOutputWindowOnOff();
}

//GUI service interface implementations.
//-----------------------------------------------------------------------------
IPanelProxy* cpl_MainWindow::GetTaskPanelProxy() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetTaskPanelProxy();
}

//-----------------------------------------------------------------------------
IOutputMessage* cpl_MainWindow::GetOutputMessage() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetOutputMessage();
}

//-----------------------------------------------------------------------------
IOutputStatusInfo* cpl_MainWindow::GetOutputStatusInfoHandler() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetOutputStatusInfoHandler(); 
}

//-----------------------------------------------------------------------------
IGraphicWindowInfo* cpl_MainWindow::GetGraphicWindowInfoHandler() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetGraphicWindowInfoHandler(); 
}

//-----------------------------------------------------------------------------
ILayoutProxy* cpl_MainWindow::GetLayoutProxy() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetLayoutProxyImp();
}

//-----------------------------------------------------------------------------
IThreadFunc* cpl_MainWindow::GetThreadFunc() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->GetThreadFunc();
}

//-----------------------------------------------------------------------------
IPluginTree* cpl_MainWindow::GetPluginTree() {
    //@@preconditions
    assert(this->mainPluginTree != NULL);
    //@@end preconditions

    return this->mainPluginTree;
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_MainWindow::GetIconProxy() {
    //@@preconditions
    assert(this->mainIconHandler != NULL);
    //@@end preconditions

    return this->mainIconHandler;
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_MainWindow::GetImageProxy() {
    //@@preconditions
    assert(this->mainImageHandler != NULL);
    //@@end preconditions

    return this->mainImageHandler;
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::SetMainPluginTree(IPluginTree* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    this->mainPluginTree = plugin;
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::SetMainIconProxy(IResImageProxy* iconProxy) {
    //@@preconditions
    assert(iconProxy != NULL);
    //@@end preconditions

    this->mainIconHandler = iconProxy;
}

//-----------------------------------------------------------------------------
void cpl_MainWindow::SetMainImageProxy(IResImageProxy* imageProxy) {
    //@@preconditions
    assert(imageProxy != NULL);
    //@@end preconditions

    this->mainImageHandler = imageProxy;
}

//-----------------------------------------------------------------------------
int cpl_MainWindow::ExecGraphicEngineIdleCallback() {
    //@@preconditions
    assert(this->mainWinImp != NULL);
    //@@end preconditions

    return this->mainWinImp->ExecGraphicEngineIdleCallback();
}

//-----------------------------------------------------------------------------
cpl_MainWindow::cpl_MainWindow(): mainPluginTree(NULL), mainScriptHandler(NULL), mainIconHandler(NULL), mainImageHandler(NULL) {    
    this->mainWinImp = cpl_MainWindowImp::New(this);
}

//-----------------------------------------------------------------------------
cpl_MainWindow::~cpl_MainWindow() {
    if (this->mainWinImp != NULL) {
        delete this->mainWinImp;
        this->mainWinImp = NULL;
    }
}
