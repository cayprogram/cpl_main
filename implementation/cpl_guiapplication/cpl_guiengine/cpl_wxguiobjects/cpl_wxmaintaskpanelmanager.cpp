#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxtaskpanel.h"
#include "cpl_wxmaintaskpanelmanager.h"
#include "cpl_wxmaintaskpanelmanager_panelproxy.h"

//-----------------------------------------------------------------------------
// class cpl_wxMainTaskPanelManager
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainTaskPanelManager::Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(mainPanel != NULL);
    assert(mainAuiManager != NULL);
    assert(w > 0);
    assert(h > 0);
    //@@end preconditions

    //create task panel.
    this->PPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    this->PPanel->SetSize(w, h);
    assert(this->PPanel != NULL);

    this->PPanel->SetBackgroundColour(wxColour(227, 227, 228));
    //this->PPanel->SetForegroundColour(wxColour(217, 217, 218));

    wxAuiPaneInfo PaneInfo;
    PaneInfo.Left();
    PaneInfo.CloseButton(false);
    PaneInfo.Floatable(false);
    PaneInfo.PinButton(false);
    PaneInfo.PaneBorder(false);
    PaneInfo.MinimizeButton(false);
    PaneInfo.MaximizeButton(false);
    PaneInfo.BottomDockable(false);
    PaneInfo.TopDockable(false);
    PaneInfo.RightDockable(false);
    PaneInfo.Movable(false);
    PaneInfo.MinSize(w, h/2);
    PaneInfo.MaxSize(w, h);
    PaneInfo.Caption(wxT(" "));
    PaneInfo.CaptionVisible(false);
    //PaneInfo.DockFixed(true);
    PaneInfo.Layer(2);
    PaneInfo.Name(wxT("Explorer"));
    mainAuiManager->InsertPane(this->PPanel, PaneInfo);

    wxGridSizer* gs = new wxGridSizer(1, 1, 0, 0);
    this->PPanel->SetSizer(gs);

    return this->PPanel;
}

//-----------------------------------------------------------------------------
void cpl_wxMainTaskPanelManager::CreatePanels() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PPanelProxy == NULL);
    //@@end preconditions

    this->PPanelProxy = new PanelProxy(this);
    assert(this->PPanelProxy != NULL);

    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        this->PTaskWins[i] = new cpl_wxTaskPanel(this, this->PPanel);
    }

    //default, the first is actived.
    this->PTaskWins[0]->DoActive();
    this->DoLayout();
}

//-----------------------------------------------------------------------------
void cpl_wxMainTaskPanelManager::Cleanup() {
    //@@preconditions
    assert(this->PPanelProxy != NULL);
    //@@end preconditions.

    delete this->PPanelProxy;
    this->PPanelProxy = NULL;
}

//-----------------------------------------------------------------------------
IPanelProxy* cpl_wxMainTaskPanelManager::GetTaskPanelProxy() {
    //@@preconditions
    assert(this->PPanelProxy != NULL);
    //@@end preconditions

    return this->PPanelProxy;
}

//-----------------------------------------------------------------------------
void cpl_wxMainTaskPanelManager::GetTaskPanel(int wid, cpl_wxTaskPanel*& panel) {
    //@@preconditions
    assert(wid >= 0);
    //@@end preconditions

    panel = this->FindPanel(wid);
}

//-----------------------------------------------------------------------------
void cpl_wxMainTaskPanelManager::ActiveTaskWinByIndex(int idx) {
    //@@preconditions
    assert(idx != -1);
    //@@end preconditions

    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        (i == idx)? this->PTaskWins[i]->DoActive(): this->PTaskWins[i]->DoDeactive();
    }
}

//-----------------------------------------------------------------------------
void cpl_wxMainTaskPanelManager::DoLayout() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions

    wxSizer* sizer = this->PPanel->GetSizer();
    assert(sizer != NULL);

    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        sizer->Detach(this->PTaskWins[i]);
        this->PTaskWins[i]->Hide();
    }
    sizer->Clear(true);
    sizer->Layout();

    cpl_wxTaskPanel* pWin = NULL;
    this->GetActiveTaskWin(pWin);
    assert(pWin != NULL);

    //do single layout.
    pWin->Show();
    sizer->Add(pWin, 0, wxEXPAND | wxALL);
    sizer->Layout();
    this->PPanel->Layout();
}

//-----------------------------------------------------------------------------
int cpl_wxMainTaskPanelManager::GetTaskWinId(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_TASKWIN_NUM);
    assert(this->PTaskWins[idx] != NULL);
    //@@end preconditions

    return this->PTaskWins[idx]->GetWinId();
}

//-----------------------------------------------------------------------------
int cpl_wxMainTaskPanelManager::GetTaskWinIdx(int wID) {
    //@@preconditions
    assert(wID >= 0 );
    //@@end preconditions

    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        if (this->PTaskWins[i]->GetWinId() == wID) {
            return i;
        }
    }
    assert(0);
    return -1;
}

//-----------------------------------------------------------------------------
cpl_wxTaskPanel* cpl_wxMainTaskPanelManager::FindPanel(int wid) {
    //@@preconditions
    assert(wid >= 0);
    //@@end preconditions

    cpl_wxTaskPanel* pWin = NULL;
    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        if (this->PTaskWins[i]->GetWinId() == wid) {
            pWin = this->PTaskWins[i];
            break;
        }
    }
    assert(pWin != NULL);
    return pWin;
}

//-----------------------------------------------------------------------------
void cpl_wxMainTaskPanelManager::GetActiveTaskWin(int& wid, int& idx) {
    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        if (this->PTaskWins[i]->IsActive()) {
            idx = i;
            wid = this->PTaskWins[i]->GetWinId();
        }
    }
}

//-----------------------------------------------------------------------------
void cpl_wxMainTaskPanelManager::GetActiveTaskWin(cpl_wxTaskPanel*& TWin) {
    //@@preconditions
    assert(TWin == NULL);
    //@@end preconditions

    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        if (this->PTaskWins[i]->IsActive()) {
            TWin = this->PTaskWins[i];
            break;
        }
    }
}

//-----------------------------------------------------------------------------
cpl_wxMainTaskPanelManager::cpl_wxMainTaskPanelManager(cpl_wxMainFrame* pOwner) : Owner(pOwner), PPanel(NULL), PPanelProxy(NULL) {
    for (int i = 0; i < MAX_TASKWIN_NUM; i++) {
        this->PTaskWins[i] = NULL;
    }
}

//-----------------------------------------------------------------------------
cpl_wxMainTaskPanelManager::~cpl_wxMainTaskPanelManager() {
    assert(this->PPanelProxy == NULL);
    while (this->PPanel-> GetEventHandler() != this->PPanel)
	((wxWindow *) this->PPanel)->PopEventHandler(false);
}
