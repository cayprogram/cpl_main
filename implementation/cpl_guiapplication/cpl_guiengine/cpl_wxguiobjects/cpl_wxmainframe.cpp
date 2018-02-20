#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxworker.h"
#include "cpl_wxoglpanel.h"
#include "cpl_wxtaskpanel.h"
#include "cpl_wxmainmenubar.h"
#include "cpl_wxmaintoolbar.h"
#include "cpl_wxmaintoolbarnormal.h"
#include "cpl_wxmaintoolbox.h"
#include "cpl_wxmainstatusbar.h"
#include "cpl_wxmainoglpanelmanager.h"
#include "cpl_wxmaintaskpanelmanager.h"
#include "cpl_wxmainframeinfo.h"
#include "cpl_wxmainsystempanel.h"
#include "cpl_wxmainsessionpanel.h"
#include "cpl_wxmainoutputpanel.h"
#include "cpl_wxmaincontextmenu.h"

/* XPM */
static const char *const sample_xpm[] = {
/* columns rows colors chars-per-pixel */
"32 32 6 1",
"  c black",
". c navy",
"X c red",
"o c yellow",
"O c gray100",
"+ c None",
/* pixels */
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++              ++++++++++",
"++++++++ ............ ++++++++++",
"++++++++ ............ ++++++++++",
"++++++++ .OO......... ++++++++++",
"++++++++ .OO......... ++++++++++",
"++++++++ .OO......... ++++++++++",
"++++++++ .OO......              ",
"++++++++ .OO...... oooooooooooo ",
"         .OO...... oooooooooooo ",
" XXXXXXX .OO...... oOOooooooooo ",
" XXXXXXX .OO...... oOOooooooooo ",
" XOOXXXX ......... oOOooooooooo ",
" XOOXXXX ......... oOOooooooooo ",
" XOOXXXX           oOOooooooooo ",
" XOOXXXXXXXXX ++++ oOOooooooooo ",
" XOOXXXXXXXXX ++++ oOOooooooooo ",
" XOOXXXXXXXXX ++++ oOOooooooooo ",
" XOOXXXXXXXXX ++++ oooooooooooo ",
" XOOXXXXXXXXX ++++ oooooooooooo ",
" XXXXXXXXXXXX ++++              ",
" XXXXXXXXXXXX ++++++++++++++++++",
"              ++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++"
};

//----------------------------------------------------------------------------
static int InitGL() {
    //initialize graphic engine.
    int bkcolor1[3] = {45, 45, 48};
    int bkcolor2[3] = {45, 45, 48};

    //lighting. model.    
    float _ambient[]  = { 0.0, 0.0, 0.0, 1.0 };
    float _diffuse[]  = { 0.6, 0.6, 0.6, 1.0 };
    float _specular[] = { 0.4, 0.4, 0.4, 1.0 };
    float _direct[] = {25, 10};

    //initialize graphic engine.
    //TODO: do your graphics engine initialization...
    //...
    return 0;
}

//----------------------------------------------------------------------------
static int DeinitGL() {
    //shutdown.
    //TODO: shutdown your graphics engine
    //...
    return 0;
}

//----------------------------------------------------------------------------
//UserDefined Event.
//----------------------------------------------------------------------------
wxDECLARE_EVENT(CPL_CUSTOM_EVENT, wxCommandEvent);
wxDEFINE_EVENT(CPL_CUSTOM_EVENT, wxCommandEvent);

//-----------------------------------------------------------------------------
// class cpl_wxMainFrame
//-----------------------------------------------------------------------------
//
void cpl_wxMainFrame::Create() {
    //@@preconditions
    assert(this->mainTaskPanelManager != NULL);
    assert(this->mainTaskPanelManager != NULL);
    assert(this->mainFrameInfo != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    //init graphic lib.
    InitGL();

    //create opengl window / task panels, frame info.
    this->mainOGLPanelManager->CreateOGLPanels();
    this->mainTaskPanelManager->CreatePanels();
    this->mainFrameInfo->Create();
    this->PAuiManager->Update();
    
    //hide panel
    this->mainSystemPanel->Hide();
    this->mainSessionPanel->Hide();
    this->mainOutput->Hide();

    //bind.
    this->Bind(wxEVT_THREAD, &cpl_wxMainFrame::OnThreadEnter, this, WORKER_START);
    this->Bind(wxEVT_THREAD, &cpl_wxMainFrame::OnThreadLeave, this, WORKER_DONE);
    this->Bind(wxEVT_THREAD, &cpl_wxMainFrame::OnThreadUpdate, this, WORKER_INPROCESS);
    this->Bind(CPL_CUSTOM_EVENT, &cpl_wxMainFrame::OnCustomEvent, this, this->GetId());  

    // build worker thread 
    this->PWorker = new cpl_wxWorker(this);

    // start the thread
    if (this->PWorker->Run() != wxTHREAD_NO_ERROR) {
        this->PWorker = NULL;
        wxExit();
    } 
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::Cleanup() {
    //@@preconditions
    assert(this->mainOGLPanelManager != NULL);
    assert(this->mainTaskPanelManager != NULL);
    //@@end preconditions

    this->mainOGLPanelManager->Cleanup();
    this->mainTaskPanelManager->Cleanup();

    //deinit graphic lib.
    DeinitGL();
}

//-----------------------------------------------------------------------------
bool cpl_wxMainFrame::Destroy() {
    //release worker thread.
    {        
        wxCriticalSectionLocker enter(this->PThreadCS);    
        if (this->PWorker != NULL) {
            this->PWorker->SetBreakOn();
            this->PWorker = NULL;
        }
    }

    cpl_Action* handler = NULL;
    this->GetMainScriptHandler(handler);
    assert(handler != NULL);

    handler->SetText("_EXIT");
    handler->Execute();   
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::PostGUIEvent(const char* hint) {
    //@@preconditions
    assert(hint != NULL);
    //@@end preconditions

    wxCommandEvent event(CPL_CUSTOM_EVENT, this->GetId());  
    event.SetEventObject(this);  
    event.SetString(hint);
    this->ProcessWindowEvent(event); 
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::CreateSubWindows(int w, int h) {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    // creating another panel to enable holding multiple ogl windows.
    this->mainOGLPanelManager = new cpl_wxMainOGLPanelManager(this);
    this->mainOGLPanelManager->Create(this->PPanel, this->PAuiManager);

    // create output panel
    this->mainOutput = new cpl_wxMainOutputPanel(this);
    this->mainOutput->Create(this->PPanel, this->PAuiManager, this->GetOutputPanelWidth(), this->GetOutputPanelHeight());

    // create session panel
    this->mainSessionPanel = new cpl_wxMainSessionPanel(this);
    this->mainSessionPanel->Create(this->PPanel, this->PAuiManager, this->GetSessionPanelWidth(), this->GetSessionPanelHeight());

    // create another panel to enable holding multiple task panel.
    this->mainTaskPanelManager = new cpl_wxMainTaskPanelManager(this);
    this->mainTaskPanelManager->Create(this->PPanel, this->PAuiManager, this->GetTaskPanelWidth(), h);

    // create system panel.
    this->mainSystemPanel = new cpl_wxMainSystemPanel(this);
    this->mainSystemPanel->Create(this->PPanel, this->PAuiManager, this->GetSystemPanelWidth(), this->GetSystemPanelHeight());

    // create toolbox.
    this->mainToolbox = new cpl_wxMainToolbox(this);
    this->mainToolbox->Create(this->PPanel, this->PAuiManager, this->GetToolBoxWidth(), h);

    // create status bar.
    this->mainStatusbar = new cpl_wxMainStatusbar(this);

    // create context menu
    this->mainContextMenu = new cpl_wxMainContextMenu(this);
    this->mainContextMenu->Create();
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::Init() {
    // get client size.
    wxSize client_size = this->GetClientSize();

    this->mainFrameInfo = new cpl_wxMainFrameInfo(this);
    assert(this->mainFrameInfo != NULL);

    // create menubar.
    this->mainMenubar = new cpl_wxMainMenubar(this);
    this->mainMenubar->Create();

    // create toolbar
    this->mainToolbar = new cpl_wxMainNormalToolbar(this);
    wxPanel* toolbarPanel = this->mainToolbar->Create(client_size.x, this->GetToolBarHeight());
    assert(toolbarPanel != NULL);

    // creating a panel to enable the frame to hold multiple controls.
    this->PPanel = new wxPanel(this, wxID_ANY, wxPoint(client_size.x, client_size.y), wxDefaultSize);
    this->PAuiManager = new wxAuiManager(this->PPanel, wxAUI_MGR_DEFAULT |wxAUI_MGR_TRANSPARENT_DRAG);
    
    // create subwindow.
    this->CreateSubWindows(client_size.x, client_size.y);

    this->PPanel->Freeze();
    this->PPanel->Thaw();

    // set layout
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(toolbarPanel, 0, wxEXPAND|wxTOP);
    sizer->Add(this->PPanel, 1, wxEXPAND|wxGROW);  
    sizer->Add(this->mainStatusbar->Create(client_size.x, this->GetStatusBarHeight()), 0, wxEXPAND|wxBOTTOM);
    this->SetSizer(sizer);

    // center.
    this->Centre();
}

//-----------------------------------------------------------------------------
cpl_wxMainFrame::cpl_wxMainFrame(cpl_ApplicationMainWindowImp* pOwner, const wxString& title, wxSize size) : Owner(pOwner), PWorker(NULL), wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size, wxDEFAULT_FRAME_STYLE | wxSIMPLE_BORDER) {    
    this->windowTitle[0] ='\0';
    this->SetIcon(wxIcon(sample_xpm));
    this->Init();    
}

//-----------------------------------------------------------------------------
cpl_wxMainFrame::~cpl_wxMainFrame() {
    //shutdown.
    this->PAuiManager->UnInit();

    //clean
    while (PPanel -> GetEventHandler() != PPanel)
    ((wxWindow *) PPanel) -> PopEventHandler(false);
    while (GetEventHandler() != this)
    ((wxWindow *) this) -> PopEventHandler(true);

    delete this->mainOGLPanelManager;
    delete this->mainTaskPanelManager;
    delete this->mainFrameInfo;
    delete this->mainMenubar;
    delete this->mainToolbar;
    delete this->mainToolbox;
    delete this->mainStatusbar;
    delete this->mainSystemPanel;
    delete this->mainSessionPanel;
    delete this->mainOutput;
    delete this->mainContextMenu;
    delete this->PAuiManager;
}

