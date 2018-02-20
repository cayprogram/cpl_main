#include "cpl_wxguiobjectincludes.h"
#include <wx/evtloop.h>

//-----------------------------------------------------------------------------
// class wxMainEventLoop
//-----------------------------------------------------------------------------
//
class wxMainEventLoop : public wxEventLoop {
public:
    wxMainEventLoop(cpl_wxApp *app);
    virtual void OnExit();

private:
    cpl_wxApp *m_PApp;
};

//-----------------------------------------------------------------------------
wxMainEventLoop::wxMainEventLoop(cpl_wxApp *app) : wxEventLoop() {
    this->m_PApp = app;
}

//-----------------------------------------------------------------------------
void wxMainEventLoop::OnExit() {
    this->m_PApp->SetShouldLeave(true);
}

//-----------------------------------------------------------------------------
// class cpl_wxApp
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool cpl_wxApp::OnInit() {
    wxInitAllImageHandlers();
    this->InitApplicationData();
    return true;
}

//-----------------------------------------------------------------------------
#if 0
int cpl_wxApp::OnRun() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    SetExitOnFrameDelete(true);

    wxMainEventLoop eventLoop(this);
    wxEventLoop::SetActive(&eventLoop);
    this->m_mainLoop = &eventLoop;

    //event loop.
    for (;;) {
        while (!Pending() && ProcessIdle());
        while (Pending()) {
            if (!Dispatch()) {
                this->AppData.bShouldLeave = true;
                break;
            }
        }

        //leave..
        if (this->AppData.bShouldLeave) {
            while (Pending()) {
                Dispatch();
            }
            this->m_mainLoop = NULL;
            return 0;
        }
        wxMilliSleep(10); // dont take up 100% of cpu as usual
    }
    this->m_mainLoop = NULL;
    return 0;
}
#else
//-----------------------------------------------------------------------------
int cpl_wxApp::OnRun() {
    return wxApp::OnRun();
}
#endif

//-----------------------------------------------------------------------------
int cpl_wxApp::OnExit() {
    this->DeinitApplicationData();

    //call parent.
    return wxApp::OnExit();
}

#define DEFAULT_UPDATE_RATE (3000)    

//-----------------------------------------------------------------------------
void cpl_wxApp::OnTimer(wxTimerEvent& event) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->AppData.pTimer != NULL);
    //@@end preconditions

    this->AppData.pTimer->Stop();
    this->AppData.pTimer->Start(this->Owner->ExecGraphicEngineIdleCallback()? (0): (DEFAULT_UPDATE_RATE));
}

//-----------------------------------------------------------------------------
void cpl_wxApp::OnIdle( wxIdleEvent& event ) {
#if 0
    static int counter = 0;
    printf("Called cpl_wxApp::OnIdle %d = \n", counter);
    counter++;
#endif
}

//-----------------------------------------------------------------------------
void cpl_wxApp::SetShouldLeave(bool flag) {
    this->AppData.bShouldLeave = flag;
    if (this->AppData.bShouldLeave) {
        this->ExitMainLoop();
    }
}

//-----------------------------------------------------------------------------
int cpl_wxApp::InitApplicationData() {
    if (this->AppData.nDisplayUpdateRate > 0) {
        this->AppData.pTimer = new wxTimer(this);
        this->AppData.pTimer->Start(DEFAULT_UPDATE_RATE);
        this->Bind(wxEVT_TIMER, &cpl_wxApp::OnTimer, this);
    }
    else {
        this->Bind(wxEVT_IDLE, &cpl_wxApp::OnIdle, this);
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxApp::DeinitApplicationData() {
    if (this->AppData.pTimer ) {
        this->AppData.pTimer->Stop( );
        delete this->AppData.pTimer;
        this->AppData.pTimer = NULL;
    }
    return 0;
}

//-----------------------------------------------------------------------------
cpl_wxApp::cpl_wxApp(cpl_ApplicationGUIEngineImp* pOwner): Owner(pOwner) {
    this->AppData.pTimer = NULL;
    this->AppData.bShouldLeave = false;
    this->AppData.nDisplayUpdateRate = DEFAULT_UPDATE_RATE;
}

//-----------------------------------------------------------------------------
cpl_wxApp::~cpl_wxApp() {
    assert(this->AppData.pTimer == NULL);
}
