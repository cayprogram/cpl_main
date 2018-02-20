#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxmainsessionpanel.h"

//-----------------------------------------------------------------------------
// class wxThePanel
//-----------------------------------------------------------------------------
//
class cpl_wxMainSessionPanel::wxThePanel: public wxPanel {

public:
    /** override */
    bool Show(bool);

    /** show direct*/
    bool ShowDirect(bool);

public:
    // constructor.
    wxThePanel(cpl_wxMainSessionPanel* pOwner, wxPanel* parent);

    // destructor
    virtual ~wxThePanel() {}

    cpl_wxMainSessionPanel* Owner;
};

//-----------------------------------------------------------------------------
cpl_wxMainSessionPanel::wxThePanel::wxThePanel(cpl_wxMainSessionPanel* pOwner, wxPanel* parent): wxPanel(parent, wxID_ANY), Owner(pOwner)  {
}

//-----------------------------------------------------------------------------
bool cpl_wxMainSessionPanel::wxThePanel::Show(bool fShow) {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    if (fShow == true) {
        this->Owner->Show();
    }
    else {
        this->Owner->Hide();
    }
    return true;
}

//-----------------------------------------------------------------------------
bool cpl_wxMainSessionPanel::wxThePanel::ShowDirect(bool show) {
    return this->wxPanel::Show(show);
}

//-----------------------------------------------------------------------------
// class cpl_wxMainSessionPanel
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainSessionPanel::Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(mainPanel != NULL);
    assert(mainAuiManager != NULL);  
    assert(w > 0);
    assert(h > 0);
    //@@end preconditions

    //create task panel.
    this->PAuiManager = mainAuiManager;
    this->PPanel = new wxThePanel(this, mainPanel);
    assert(this->PPanel != NULL);
    this->PPanel->SetSize(w, h);
    this->PPanel->SetBackgroundColour(wxColour(227, 227, 228));

    this->PaneInfo.Top();
    this->PaneInfo.CloseButton(false);
    this->PaneInfo.PinButton(false);
    this->PaneInfo.PaneBorder(false);
    this->PaneInfo.MinimizeButton(false);
    this->PaneInfo.MaximizeButton(false);
    this->PaneInfo.BottomDockable(false);
    this->PaneInfo.RightDockable(false);
    this->PaneInfo.TopDockable(false);
    this->PaneInfo.LeftDockable(false);
    this->PaneInfo.Layer(1);
    this->PaneInfo.Caption(wxT("Session")).CaptionVisible(false);
    this->PaneInfo.Name(wxT("Session"));
    this->PaneInfo.MinSize(-1, h);
    //this->PaneInfo.MaxSize(-1, h);
    this->PaneInfo.DockFixed(true);
    mainAuiManager->InsertPane(this->PPanel, this->PaneInfo);

    wxBoxSizer* gs = new wxBoxSizer(wxVERTICAL);
    this->PPanel->SetSizer(gs);
    this->PPanel->Layout();

    return this->PPanel;
}

//-----------------------------------------------------------------------------
void cpl_wxMainSessionPanel::Show() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    ((wxThePanel*)this->PPanel)->ShowDirect(true);
    this->PAuiManager->InsertPane(this->PPanel, this->PaneInfo);
    this->PAuiManager->Update();
}

//-----------------------------------------------------------------------------
void cpl_wxMainSessionPanel::Hide() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    ((wxThePanel*)this->PPanel)->ShowDirect(false);
    this->PAuiManager->DetachPane(this->PPanel);
    this->PAuiManager->Update();
}

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainSessionPanel::GetPanel() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions

    return this->PPanel;
}

//-----------------------------------------------------------------------------
cpl_wxMainSessionPanel::cpl_wxMainSessionPanel(cpl_wxMainFrame* pOwner) : Owner(pOwner), PAuiManager(NULL), PThePanel(NULL), PPanel(NULL) {
}

//-----------------------------------------------------------------------------
cpl_wxMainSessionPanel::~cpl_wxMainSessionPanel() {
    while (this->PPanel-> GetEventHandler() != this->PPanel)
	((wxWindow *) this->PPanel)->PopEventHandler(false);
}
