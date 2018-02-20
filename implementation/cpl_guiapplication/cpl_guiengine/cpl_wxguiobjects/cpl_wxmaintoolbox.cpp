#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxmaintoolbox.h"

//-----------------------------------------------------------------------------
// class cpl_wxMainToolbox
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainToolbox::Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h) {
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
    PaneInfo.Right();
    PaneInfo.CloseButton(false);
    PaneInfo.PinButton(false);
    PaneInfo.PaneBorder(false);
    PaneInfo.MinimizeButton(false);
    PaneInfo.MaximizeButton(false);
    PaneInfo.BottomDockable(false);
    PaneInfo.TopDockable(false);
    PaneInfo.MinSize(w, h/2);
    PaneInfo.MaxSize(w, h);
    PaneInfo.DockFixed(true);
    PaneInfo.Caption(wxT(" "));
    PaneInfo.CaptionVisible(false);
    PaneInfo.Layer(3);
    PaneInfo.Name(wxT("Toolbox"));
    mainAuiManager->InsertPane(this->PPanel, PaneInfo);

    wxGridSizer* gs = new wxGridSizer(1, 1, 0, 0);
    this->PPanel->SetSizer(gs);
    gs->Layout();

    return this->PPanel;
}

//-----------------------------------------------------------------------------
cpl_wxMainToolbox::cpl_wxMainToolbox(cpl_wxMainFrame* pOwner) : Owner(pOwner), PPanel(NULL) {
}

//-----------------------------------------------------------------------------
cpl_wxMainToolbox::~cpl_wxMainToolbox() {
    while (this->PPanel-> GetEventHandler() != this->PPanel)
	((wxWindow *) this->PPanel)->PopEventHandler(false);
}
