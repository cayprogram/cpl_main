#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxmainsystempanel.h"

//-----------------------------------------------------------------------------
// class wxThePanel
//-----------------------------------------------------------------------------
//
class cpl_wxMainSystemPanel::wxThePanel: public wxPanel {

public:
    /** override */
    bool Show(bool);

    /** show direct*/
    bool ShowDirect(bool);

public:
    // constructor.
    wxThePanel(cpl_wxMainSystemPanel* pOwner, wxPanel* parent);

    // destructor
    virtual ~wxThePanel() {}

    cpl_wxMainSystemPanel* Owner;
};

//-----------------------------------------------------------------------------
cpl_wxMainSystemPanel::wxThePanel::wxThePanel(cpl_wxMainSystemPanel* pOwner, wxPanel* parent): wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE), Owner(pOwner)  {
}

//-----------------------------------------------------------------------------
bool cpl_wxMainSystemPanel::wxThePanel::Show(bool fShow) {
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
bool cpl_wxMainSystemPanel::wxThePanel::ShowDirect(bool show) {
    return this->wxPanel::Show(show);
}

//-----------------------------------------------------------------------------
// class cpl_wxMainSystemPanel
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainSystemPanel::Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h) {
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

    this->PaneInfo.Right();
    this->PaneInfo.CloseButton(false);
    this->PaneInfo.PinButton(false);
    this->PaneInfo.PaneBorder(false);
    this->PaneInfo.MinimizeButton(false);
    this->PaneInfo.MaximizeButton(false);
    this->PaneInfo.BottomDockable(false);
    this->PaneInfo.TopDockable(false);
    this->PaneInfo.LeftDockable(false);
    this->PaneInfo.Layer(2).Position(1);
    this->PaneInfo.Caption(wxT("System")).CaptionVisible(false);
    this->PaneInfo.Name(wxT("System"));
    this->PaneInfo.MinSize(w, -1);
    this->PaneInfo.MaxSize(w, -1);
    //this->PaneInfo.DockFixed(true);
    mainAuiManager->InsertPane(this->PPanel, this->PaneInfo);

    wxBoxSizer* gs = new wxBoxSizer(wxVERTICAL);
    this->PPanel->SetSizer(gs);
    this->PPanel->Layout();

    return this->PPanel;
}

//-----------------------------------------------------------------------------
void cpl_wxMainSystemPanel::Show() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    ((wxThePanel*)this->PPanel)->ShowDirect(true);
    this->PAuiManager->InsertPane(this->PPanel, this->PaneInfo);
    this->PAuiManager->Update();
}

//-----------------------------------------------------------------------------
void cpl_wxMainSystemPanel::Hide() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    ((wxThePanel*)this->PPanel)->ShowDirect(false);
    this->PAuiManager->DetachPane(this->PPanel);
    this->PAuiManager->Update();
}

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainSystemPanel::GetPanel() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions

    return this->PPanel;
}

//-----------------------------------------------------------------------------
cpl_wxMainSystemPanel::cpl_wxMainSystemPanel(cpl_wxMainFrame* pOwner) : Owner(pOwner), PAuiManager(NULL), PThePanel(NULL), PPanel(NULL) {
}

//-----------------------------------------------------------------------------
cpl_wxMainSystemPanel::~cpl_wxMainSystemPanel() {
    while (this->PPanel-> GetEventHandler() != this->PPanel)
    ((wxWindow *) this->PPanel)->PopEventHandler(false);
}
