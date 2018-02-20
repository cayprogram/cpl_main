#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxoglpanel.h"
#include "cpl_wxmainoglpanelmanager.h"
#include "cpl_wxmainoglpanelmanager_layout.h"

//-----------------------------------------------------------------------------
static int IsAtomMode() {
    //TODO: fill judgement codes of your graphics engine atom ...
    return 0;
}

//-----------------------------------------------------------------------------
//Event table.
//-----------------------------------------------------------------------------
//
BEGIN_EVENT_TABLE(cpl_wxOGLPanelEventHandler, wxEvtHandler)
    EVT_LEFT_DOWN(cpl_wxOGLPanelEventHandler::OnLeftButtonClick)
    EVT_RIGHT_DOWN(cpl_wxOGLPanelEventHandler::OnLeftButtonClick)
    EVT_LEFT_DCLICK(cpl_wxOGLPanelEventHandler::OnLeftButtonDBClick)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
// class cpl_wxOGLPanelEventHandler
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void cpl_wxOGLPanelEventHandler::OnLeftButtonClick(wxMouseEvent & event) {
    //@@preconditions
    assert(this->Panel != NULL);
    //@@end preconditions

    if (this->Panel->IsActive() == 0) {
        this->Panel->OnLeftButtonClick(event);
    }
    this->Panel->SetOGLFocus();
    event.Skip();
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanelEventHandler::OnLeftButtonDBClick(wxMouseEvent & event) {
    //@@preconditions
    assert(this->Panel != NULL);
    //@@end preconditions

    this->Panel->OnLeftButtonDBClick(event);
    event.Skip();
}

//-----------------------------------------------------------------------------
cpl_wxOGLPanelEventHandler::cpl_wxOGLPanelEventHandler(cpl_wxOGLPanel *panel): wxEvtHandler(), Panel(panel) {
}

//-----------------------------------------------------------------------------
cpl_wxOGLPanelEventHandler::~cpl_wxOGLPanelEventHandler() {
}

//-----------------------------------------------------------------------------
// class cpl_wxOGLPanel
//-----------------------------------------------------------------------------
//
int cpl_wxOGLPanel::GetWinId() {
    return this->OGLInfo.winId;
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::CreateOGLWin(_fbOGLInfo_s& pInfo) {
    //@@preconditions
    assert(pInfo.glWin == NULL);
    assert(pInfo.winId == -1);
    //@@end preconditions

#ifdef _DEBUG
    static int counter = 0;
    static int ColorTable[][3] = {
        {200, 0, 0},
        {0, 200, 0},
        {0, 0, 200},
        {200, 200, 0},
    };
    pInfo.bkColor[0] = ColorTable[counter%4][0];
    pInfo.bkColor[1] = ColorTable[counter%4][1];
    pInfo.bkColor[2] = ColorTable[counter%4][2];
#endif
    int wId = 0;
    //TODO: create graphics window by your engine...
    //...
   
    //TODO: add function key control...
    //...
#ifdef _DEBUG
    counter++;
#endif

    //TODO: show graphics window by your engine...
    //...

    wxGLCanvas* pCanvas = NULL;
    //TODO: hook-up wxWidgets control with your graphics engine...
    //...
    
    //TODO: link cpl_wxOGLPanel callbacks to your graphics engine...
    //...

    pInfo.winId = wId;
    pInfo.glWin = pCanvas; 

   //@@postconditions
    assert(pInfo.glWin != NULL);
    assert(pInfo.winId != -1);
    //@@end postconditions
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::OnLeftButtonClick(wxMouseEvent & event) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->Owner->Owner != NULL);
    assert(this->OGLInfo.winId >= 0);
    //@@end preconditions

    cpl_Action* handler = NULL;
    this->Owner->Owner->GetMainScriptHandler(handler);
    assert(handler != NULL);
    
    int idx = this->Owner->GetOGLWinIdx(this->OGLInfo.winId);
    assert(idx >= 0);

    handler->SetText("OGLPANEL_CLICKED");
    handler->SetUserData(&idx);
    handler->Execute();    
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::OnLeftButtonDBClick(wxMouseEvent & event) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->Owner->Owner != NULL);
    //@@end preconditions

#if 1
    cpl_Action* handler = NULL;
    this->Owner->Owner->GetMainScriptHandler(handler);
    assert(handler != NULL);
    
    int idx = this->Owner->GetOGLWinIdx(this->OGLInfo.winId);
    assert(idx >= 0);

    handler->SetText("OGLPANEL_DOUBLECLICKED");
    handler->SetUserData(&idx);
    handler->Execute();    
#else
    this->Owner->SwitchLayoutMode();
    this->Owner->DoLayout();
#endif
}


//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::SetOGLFocus() {
    //@@preconditions
    assert(this->OGLInfo.glWin != NULL);
    //@@end preconditions

    this->OGLInfo.glWin->SetFocus();
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::DoActive() {
    this->OGLInfo.isActived = 1;
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::DoDeactive() {
    this->OGLInfo.isActived = 0;
}

//-----------------------------------------------------------------------------
int cpl_wxOGLPanel::Initialize() {
    this->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    this->CreateOGLWin(this->OGLInfo);
#if 1
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(this->OGLInfo.glWin, 1, wxEXPAND | wxALL, 0);
    this->SetSizer(vbox);
    this->Centre();
#else
    wxGridSizer* gs = new wxGridSizer(1, 1, 0, 0);
    gs->Add(this->OGLInfo.glWin, 0, wxEXPAND, 6);
    this->SetSizer(gs);
    this->Centre();
#endif
    this->EventHandler = new cpl_wxOGLPanelEventHandler(this);
    this->OGLInfo.glWin->PushEventHandler(this->EventHandler);
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxOGLPanel::Cleanup() {
    //@@preconditions
    assert(this->OGLInfo.glWin != NULL);
    //@@end preconditions

    this->OGLInfo.glWin->RemoveEventHandler(this->EventHandler);
    return 0;
}

//--------------------------------------------------------------------
void cpl_wxOGLPanel::mouseWheelForwardCallback(void* callData, void* clientData) {
    //@@preconditions
    assert(clientData != NULL);
    assert(callData   != NULL);
    //@@end preconditions
    
    MMM_MESSAGE * pMsg = (MMM_MESSAGE*)callData;
    assert(pMsg != NULL);
    
    //TODO: your graphics engine response here...
}

//--------------------------------------------------------------------
void cpl_wxOGLPanel::mouseWheelBackwardCallback(void* callData, void* clientData) {
    //@@preconditions
    assert(clientData != NULL);
    assert(callData   != NULL);
    //@@end preconditions
    
    MMM_MESSAGE * pMsg = (MMM_MESSAGE*)callData;
    assert(pMsg != NULL);
    
    //TODO: your graphics engine response here...
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::OnContextMenuCallback(void* calldata, void * clientdata) {
    //@@preconditions
    assert(clientdata != NULL);
    assert(calldata != NULL);
    //@@end preconditions
    
    cpl_wxOGLPanel* THIS_IS = (cpl_wxOGLPanel*)clientdata;
    assert(THIS_IS != NULL);
    
    MMM_MESSAGE * pMsg = (MMM_MESSAGE*)calldata;
    assert(pMsg != NULL);
    
    //TODO: your graphics engine response here...
}

//-----------------------------------------------------------------------------
void cpl_wxOGLPanel::OnContextMenuHandler(int x, int y) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->Owner->Owner != NULL);
    //@@end preconditions

    if (this->IsActive() == 0) {
        return;
    }

    cpl_Action* handler = NULL;
    this->Owner->Owner->GetMainScriptHandler(handler);
    assert(handler != NULL);
    
    int idx = this->Owner->GetOGLWinIdx(this->OGLInfo.winId);
    assert(idx >= 0);

    handler->SetText("CONTEXTMENU");
    handler->SetUserData(&idx);
    handler->Execute();   

    //popup menu
    wxMenu* menu = this->Owner->Owner->GetContextMenu();
    assert(menu != NULL);

    //and then display
    this->PopupMenu(menu, x, y);
}

//-----------------------------------------------------------------------------
cpl_wxOGLPanel::cpl_wxOGLPanel(cpl_wxMainOGLPanelManager* pOwner, wxPanel* parent) : Owner(pOwner), wxPanel(parent, wxID_ANY)  {
    this->OGLInfo.winId = -1;
    this->OGLInfo.glWin = NULL;
    this->OGLInfo.isActived = 0;
    this->Initialize();
}

//-----------------------------------------------------------------------------
cpl_wxOGLPanel::~cpl_wxOGLPanel() {
}
