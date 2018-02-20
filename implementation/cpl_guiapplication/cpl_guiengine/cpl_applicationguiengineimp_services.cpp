#include "cpl_applicationguiengineimpincludes.h"

//local includes.
#include "cpl_wxguiobjects/cpl_wxguiobjectincludes.h"
#include "cpl_wxguiobjects/cpl_wxsystemfileio.h"

//-----------------------------------------------------------------------------
// class cpl_ApplicationGUIEngineImp::RuntimeContextProxy
//-----------------------------------------------------------------------------
//
class cpl_ApplicationGUIEngineImp::RuntimeContextProxy : public IRuntimeContextProxy {
public:
    /** set break flag. */
    virtual void SetBreakFlagOn();
    
    /** set busy flag on/off */
    virtual void SetBusyFlagOn();
    virtual void SetBusyFlagOff();
    
    /** wait for time. */
    virtual void Wait(double ftime);
    
    /** wait until */
    virtual void WaitUntil(int& status, int& ret, const char* message, int askBeforeExit);
    
    /** update command gui */
    virtual void UpdateCommandGUI();

    /** full screen on/off */
    virtual void FullScreenOn();    
    virtual void FullScreenOff();

    /** iconize */
    virtual void Iconize();
    
    /** about */
    virtual void About();
    
    /** set window title */
    virtual void SetWindowTitle(const char* title);
    
    /** add check function */
    virtual void AddCheckFunction(CHECKFUNC func, void* data);
    
    /** remove check function */
    virtual void RemoveCheckFunction();

    /** get console mode */
    virtual int  IsConsoleModeOn();

    /** set gui command context */
    virtual void SetGUICommandContext(const char* context);

    /** get gui command context */
    virtual void GetGUICommandContext(const char*& context);

    /** asys call */
    virtual void AsysCallFunction(CHECKFUNC func, void* data, float t);

    /** synchronize with outer context */
    virtual void SyncWithOuterContext(const char* context, void* clientData) {}

    /** report error */
    virtual void ReportError(const char* text);

    /** echo message */
    virtual void EchoMessage(const char* msg);

    /** get application path */
    virtual void GetApplicationPath(char szPath[], int mode);

    /** message */
    virtual int  Message(const char* text);

    /** project */
    virtual int  NewProject(const char* projectFilter, const char* initDirectory, int& index, char projectName[], char projectPath[]);

public:
    //constructor.
    RuntimeContextProxy(cpl_ApplicationGUIEngineImp* _pOwner): pOwner(_pOwner) {}

    //destructor.
    virtual ~RuntimeContextProxy(){}

    //engine.
    cpl_ApplicationGUIEngineImp* pOwner;
};

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::SetBreakFlagOn() {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions

    pOwner->SetBreakFlagOn();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::SetBusyFlagOn() {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions

    pOwner->SetBusyFlagOn();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::SetBusyFlagOff() {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions

    pOwner->SetBusyFlagOff();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::Wait(double ftime) {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions

}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::WaitUntil(int& status, int& ret, const char* message, int askBeforeExit) {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions
    
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::UpdateCommandGUI() {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions
    
    pOwner->UpdateGUI();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::FullScreenOn() {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions

}

//-----------------------------------------------------------------------------  
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::FullScreenOff() {
    //@@preconditions
    assert(pOwner != NULL);
    //@@end preconditions

}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::SetWindowTitle(const char* title) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions
    
    pOwner->SetWindowTitle(title);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::AddCheckFunction(CHECKFUNC func, void* data) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions
    
    pOwner->AddCheckFunction(func, data);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::RemoveCheckFunction() {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions
 
    pOwner->RemoveCheckFunction();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::About() {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions
    
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::Iconize() {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions
    
}

//-----------------------------------------------------------------------------
int  cpl_ApplicationGUIEngineImp::RuntimeContextProxy::IsConsoleModeOn() {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions

    return 0;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::AsysCallFunction(CHECKFUNC func, void* data, float t) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions

}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::ReportError(const char* text) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions

}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::EchoMessage(const char* msg) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions

}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::GetApplicationPath(char szPath[], int mode) {
    char * appPath = cpl_SystemConfig::Instance()->GetApplicationDirectory();
    assert(appPath != NULL);
    sprintf(szPath, appPath);
    cpl_SystemTools::ConvertWindowsPathToUnix(szPath);
}

//-----------------------------------------------------------------------------
int  cpl_ApplicationGUIEngineImp::RuntimeContextProxy::Message(const char* msg) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions

    return 0;
}

//-----------------------------------------------------------------------------
int  cpl_ApplicationGUIEngineImp::RuntimeContextProxy::NewProject(const char* projectFilter, const char* initDirectory, int& index, char projectName[], char projectPath[]) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions

    return 0;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::SetGUICommandContext(const char* context) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions

}

//-----------------------------------------------------------------------------
void cpl_ApplicationGUIEngineImp::RuntimeContextProxy::GetGUICommandContext(const char*& context) {
    //@@precondition
    assert(pOwner != NULL);
    //@@end preconditions
}

//-----------------------------------------------------------------------------
IRuntimeContextProxy* cpl_ApplicationGUIEngineImp::GetRuntimeContextProxy() {
    //@@postconditions
    assert(this->pRuntimeContext != NULL);
    //@@end preconditions

    return this->pRuntimeContext;
}

//-----------------------------------------------------------------------------
cpl_ApplicationGUIEngineImp::cpl_ApplicationGUIEngineImp() {
    this->theApp = NULL;
    this->engineGUI = NULL;
    this->pRuntimeContext = new RuntimeContextProxy(this);

    this->pCheckFunc.checkFunction = NULL;
    this->pCheckFunc.data = NULL;

    this->pIdleFunc.checkFunction = NULL;
    this->pIdleFunc.data = NULL;
}

//-----------------------------------------------------------------------------
cpl_ApplicationGUIEngineImp::~cpl_ApplicationGUIEngineImp() {
    if (this->pRuntimeContext) {
        delete this->pRuntimeContext;
        this->pRuntimeContext = NULL;
    }
}
