#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxoglpanel.h"
#include "cpl_wxmainoglpanelmanager.h"
#include "cpl_wxmainoglpanelmanager_layout.h"

//-----------------------------------------------------------------------------
// class cpl_wxMainOGLPanelManager
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainOGLPanelManager::Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(mainPanel != NULL);
    assert(mainAuiManager != NULL);
    //@@end preconditions

    //create layout manager.
    this->Layout = cpl_wxMainOGLPanelManagerLayout::New(this);

    //create ogl windows panel.
    this->PPanel = new wxPanel(mainPanel,wxID_ANY);
    this->PPanel->SetBackgroundColour(wxColour(145, 145, 148));    

    wxAuiPaneInfo OglPaneInfo;
    OglPaneInfo.Center();
    OglPaneInfo.CloseButton(false);
    OglPaneInfo.Floatable(false);
    OglPaneInfo.Gripper(false);
    OglPaneInfo.PaneBorder(false);
    OglPaneInfo.Movable(false);
    OglPaneInfo.CaptionVisible(false);
    OglPaneInfo.Layer(0);
    OglPaneInfo.Name(wxT("Opengl"));   
    mainAuiManager->InsertPane(this->PPanel, OglPaneInfo);

    return this->PPanel;
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::CreateOGLPanels() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions

    for (int i = 0; i < MAX_OGLWIN_NUM; i++) {
        this->POGLWins[i] = new cpl_wxOGLPanel(this, this->PPanel);
    }

    //default, the first is actived.
    this->POGLWins[0]->DoActive();
    this->Layout->DoLayout();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::Cleanup() {
    //@@preconditions
    assert(this->Layout != NULL);
    //@@end preconditions

    for (int i = 0; i < MAX_OGLWIN_NUM; i++) {
        this->POGLWins[i]->Cleanup();
    }
    this->Layout->Release();
    this->Layout = NULL;
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::SwitchLayoutMode() {
    //@@preconditions
    assert(this->Layout != NULL);
    //@@end preconditions

    this->Layout->SwitchLayoutMode();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::DoLayout() {
    //@@preconditions
    assert(this->Layout != NULL);
    //@@end preconditions

    this->Layout->DoLayout();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::GetActiveOGLWin(int& wid, int& idx) {
    for (int i = 0; i < MAX_OGLWIN_NUM; i++) {
        if (this->POGLWins[i]->IsActive()) {
            idx = i;
            wid = this->POGLWins[i]->GetWinId();
        }
    }
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::ActiveOGLWinByIndex(int idx) {
    //@@preconditions
    assert(idx != -1);
    //@@end preconditions

    for (int i = 0; i < MAX_OGLWIN_NUM; i++) {
        (i == idx)? this->POGLWins[i]->DoActive(): this->POGLWins[i]->DoDeactive();
    }
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::GetActiveOGLWin(cpl_wxOGLPanel*& OGLWin) {
    //@@preconditions
    assert(OGLWin == NULL);
    //@@end preconditions

    for (int i = 0; i < MAX_OGLWIN_NUM; i++) {
        if (this->POGLWins[i]->IsActive()) {
            OGLWin = this->POGLWins[i];
            break;
        }
    }
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManager::GetOGLWinId(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_OGLWIN_NUM);
    assert(this->POGLWins[idx] != NULL);
    //@@end preconditions

    return this->POGLWins[idx]->GetWinId();
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManager::GetOGLWinIdx(int wID) {
    //@@preconditions
    assert(wID >= 0 );
    //@@end preconditions

    for (int i = 0; i < MAX_OGLWIN_NUM; i++) {
        if (this->POGLWins[i]->GetWinId() == wID) {
            return i;
        }
    }
    assert(0);
    return -1;
}

//-----------------------------------------------------------------------------
ILayoutProxy* cpl_wxMainOGLPanelManager::GetLayoutProxyImp() {
    //@@preconditions
    assert(this->Layout != NULL);
    //@@end preconditions

    return this->Layout->GetImplementation();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManager::DoExchangeOGLWin(int comp_src, int comp_target) {
    //@@preconditions
    assert(comp_src >= 0);
    assert(comp_target >= 0);
    assert(this->Layout != NULL);
    //@@end preconditions

    this->Layout->DoExchangeDirect(comp_src, comp_target);
}

//-----------------------------------------------------------------------------
cpl_wxMainOGLPanelManager::cpl_wxMainOGLPanelManager(cpl_wxMainFrame* pOwner) : Owner(pOwner), Layout(NULL),PPanel(NULL) {
    for (int i = 0; i < MAX_OGLWIN_NUM; i++) {
        this->POGLWins[i] = NULL;
    }
}

//-----------------------------------------------------------------------------
cpl_wxMainOGLPanelManager::~cpl_wxMainOGLPanelManager() {
    //@@postconditons
    assert(Layout == NULL);
    //@@end postconditions

    while (this->PPanel-> GetEventHandler() != this->PPanel)
    ((wxWindow *) this->PPanel)->PopEventHandler(false);
}
