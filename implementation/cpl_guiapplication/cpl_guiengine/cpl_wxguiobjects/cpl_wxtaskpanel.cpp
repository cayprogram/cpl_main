#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxtaskpanel.h"

//-----------------------------------------------------------------------------
// class cpl_wxTaskPanel
//-----------------------------------------------------------------------------
//
int cpl_wxTaskPanel::GetWinId() {
    return this->WINInfo.winId;
}

//-----------------------------------------------------------------------------
void cpl_wxTaskPanel::CreateTaskWin(_fbTaskInfo_s& pInfo) {
    //@@preconditions
    assert(pInfo.pWin == NULL);
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
#endif

    wxColour color;
#ifdef _DEBUG
    color.Set(ColorTable[counter][0], ColorTable[counter][1], ColorTable[counter][2]);
    counter++;
#endif
    static int wID = 1;
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
#ifdef _DEBUGA
    panel->SetBackgroundColour(wxColour(240, 240, 240));
    panel->SetForegroundColour(wxColour(240, 240, 240));
#endif
    assert(panel != NULL);

    wxBoxSizer* gs = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(gs);
    panel->Layout();
    
    pInfo.winId = wID++;
    pInfo.pWin = panel;

   //@@postconditions
    assert(pInfo.pWin != NULL);
    assert(pInfo.winId != -1);
    //@@end postconditions
}

//-----------------------------------------------------------------------------
void cpl_wxTaskPanel::DoActive() {
    this->WINInfo.isActived = 1;
}

//-----------------------------------------------------------------------------
void cpl_wxTaskPanel::DoDeactive() {
    this->WINInfo.isActived = 0;
}

//-----------------------------------------------------------------------------
int cpl_wxTaskPanel::Initialize() {
    this->CreateTaskWin(this->WINInfo);
    wxGridSizer* gs = new wxGridSizer(1, 1, 0, 0);
    gs->Add(this->WINInfo.pWin, 0, wxEXPAND | wxALL);
    this->SetSizer(gs);
    this->Layout();
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxTaskPanel::Cleanup() {
    return 0;
}

//-----------------------------------------------------------------------------
wxPanel* cpl_wxTaskPanel::GetRawWin() {
    //@@postconditions
    assert(this->WINInfo.pWin != NULL);
    //@@end postconditions

    return this->WINInfo.pWin;
}

//-----------------------------------------------------------------------------
cpl_wxTaskPanel::cpl_wxTaskPanel(cpl_wxMainTaskPanelManager* pOwner, wxPanel* parent) : Owner(pOwner), wxPanel(parent, wxID_ANY)  {
    this->WINInfo.winId = -1;
    this->WINInfo.pWin = NULL;
    this->WINInfo.isActived = 0;
    this->Initialize();
}

//-----------------------------------------------------------------------------
cpl_wxTaskPanel::~cpl_wxTaskPanel() {
}
