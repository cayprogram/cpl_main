#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxmainoutputpanel.h"

//-----------------------------------------------------------------------------
// class OutputImp
//-----------------------------------------------------------------------------
//
class cpl_wxMainOutputPanel::OutputImp: public IOutputMessage {

public:
    //[interface]
    /** output text */
    void OutputText(const char* text);

public:
    // constructor.
    OutputImp(cpl_wxMainOutputPanel* pOwner) : Owner(pOwner) {}

    // destructor
    virtual ~OutputImp() {}

    //member variables.
    cpl_wxMainOutputPanel* Owner;
};

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::OutputImp::OutputText(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    assert(this->Owner != NULL);
    //@@end preconditions

    this->Owner->OutputText(text);
}

//-----------------------------------------------------------------------------
// class wxThePanel
//-----------------------------------------------------------------------------
//
class cpl_wxMainOutputPanel::wxThePanel: public wxPanel {

public:
    /** override */
    bool Show(bool);

    /** show direct*/
    bool ShowDirect(bool);

public:
    // constructor.
    wxThePanel(cpl_wxMainOutputPanel* pOwner, wxPanel* parent);

    // destructor
    virtual ~wxThePanel() {}

    cpl_wxMainOutputPanel* Owner;
};

//-----------------------------------------------------------------------------
cpl_wxMainOutputPanel::wxThePanel::wxThePanel(cpl_wxMainOutputPanel* pOwner, wxPanel* parent): wxPanel(parent, wxID_ANY), Owner(pOwner)  {
}

//-----------------------------------------------------------------------------
bool cpl_wxMainOutputPanel::wxThePanel::Show(bool fShow) {
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
bool cpl_wxMainOutputPanel::wxThePanel::ShowDirect(bool show) {
    return this->wxPanel::Show(show);
}

//-----------------------------------------------------------------------------
// class cpl_wxMainOutputPanel
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainOutputPanel::Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(mainPanel != NULL);
    assert(mainAuiManager != NULL);  
    assert(w > 0);
    assert(h > 0);
    //@@end preconditions

    //create output imp
    this->POutput = new OutputImp(this);
    assert(this->POutput != NULL);

    //create task panel.
    this->PAuiManager = mainAuiManager;
    this->PPanel = new wxThePanel(this, mainPanel);
    assert(this->PPanel != NULL);
    this->PPanel->SetSize(w, h);
    this->PPanel->SetBackgroundColour(wxColour(227, 227, 228));

    this->PaneInfo.Bottom();
    this->PaneInfo.CloseButton(false);
    this->PaneInfo.PinButton(false);
    this->PaneInfo.PaneBorder(false);
    this->PaneInfo.MinimizeButton(false);
    this->PaneInfo.MaximizeButton(false);
    this->PaneInfo.RightDockable(false);
    this->PaneInfo.BottomDockable(false);
    this->PaneInfo.TopDockable(false);
    this->PaneInfo.LeftDockable(false);
    this->PaneInfo.Layer(1);
    this->PaneInfo.Caption(wxT("Output")).CaptionVisible(false);
    this->PaneInfo.Name(wxT("Output"));
    this->PaneInfo.MinSize(-1, h);
    this->PaneInfo.MaxSize(-1, h);
    this->PaneInfo.DockFixed(true);
    this->PAuiManager->InsertPane(this->PPanel, this->PaneInfo);

    wxBoxSizer* gs = new wxBoxSizer(wxVERTICAL);
    this->PPanel->SetSizer(gs);
    this->PPanel->Layout();

    //create sub controls.
    this->CreateSubControls(w, h);
    this->BindControls();

    return this->PPanel;
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::Show() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    ((wxThePanel*)this->PPanel)->ShowDirect(true);
    this->PAuiManager->InsertPane(this->PPanel, this->PaneInfo);
    this->PAuiManager->Update();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::Hide() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PAuiManager != NULL);
    //@@end preconditions

    ((wxThePanel*)this->PPanel)->ShowDirect(false);
    this->PAuiManager->DetachPane(this->PPanel);
    this->PAuiManager->Update();
}

//-----------------------------------------------------------------------------
int cpl_wxMainOutputPanel::IsShown() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions

    return this->PPanel->IsShown();
}

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainOutputPanel::GetPanel() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions

    return this->PPanel;
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::CreateSubControls(int bw, int bh) {
    //@@preconditions
    assert(bw > 0);
    assert(bh > 0);
    //@@end preconditions

    //parent.
    wxPanel* container = new wxPanel(this->PPanel, wxID_ANY);
    container->SetBackgroundColour(wxColour(27, 27, 28));

    //sub controls.
    {
        //left.
        wxPanel* leftPanel = new wxPanel(container, wxID_ANY);
        leftPanel->SetBackgroundColour(this->PPanel->GetBackgroundColour());
    #ifdef _DEBUGA
        leftPanel->SetBackgroundColour(wxColour(45, 45, 48));
    #endif
        wxBoxSizer* itemStaticBoxSizer1 = new wxBoxSizer(wxVERTICAL);
        leftPanel->SetSizer(itemStaticBoxSizer1);
        
        this->PTextCommand = new wxTextCtrl(leftPanel, wxID_ANY, _(""), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
        this->PTextCommand->SetBackgroundColour(this->PPanel->GetBackgroundColour());
        this->PTextCommand->SetMinSize(wxSize(-1, bh));
        wxStaticText* itemStatic = new wxStaticText(leftPanel, wxID_ANY, _(">"), wxDefaultPosition, wxDefaultSize, 0 );
        itemStatic->SetMinSize(wxSize(-1, bh));
        wxBoxSizer * hbox1 = new wxBoxSizer(wxHORIZONTAL);
        hbox1->Add(itemStatic, 0, wxGROW|wxALL, 0);
        hbox1->Add(this->PTextCommand, 1, wxGROW|wxALL, 0);
        itemStaticBoxSizer1->Add(hbox1, 0, wxGROW|wxALL,5);

        //right
        wxPanel* rightPanel = new wxPanel(container, wxID_ANY);
        rightPanel->SetBackgroundColour(this->PPanel->GetBackgroundColour());
    #ifdef _DEBUGA
        rightPanel->SetBackgroundColour(wxColour(45, 45, 48));
    #endif
        wxBoxSizer* itemStaticBoxSizer2 = new wxBoxSizer(wxVERTICAL);
        rightPanel->SetSizer(itemStaticBoxSizer2);

        wxPanel* _subPanel = new wxPanel(rightPanel, wxID_ANY, wxDefaultPosition);
        {
            this->POutputMessage[0] = new wxStaticText(_subPanel, wxID_ANY, _("aaaaa"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
            wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
            vbox->Add(this->POutputMessage[0], 0, wxEXPAND | wxALL, 2);
            _subPanel->SetSizer(vbox);
        }
        this->POutputScrollBar = new wxScrollBar(rightPanel, wxID_ANY, wxDefaultPosition, wxSize(bh, bh), wxSB_VERTICAL);
        this->POutputScrollBar->SetBackgroundColour(this->PPanel->GetBackgroundColour());
        this->POutputScrollBar->SetScrollbar(0, 1, MAX_STRING_NUM, 1);
        wxBoxSizer * hbox2 = new wxBoxSizer(wxHORIZONTAL);
        hbox2->Add(_subPanel, 1, wxALIGN_CENTRE_VERTICAL|wxBOTTOM | wxTOP, 0);
        hbox2->Add(this->POutputScrollBar, 0, wxEXPAND | wxALL, 0);
        itemStaticBoxSizer2->Add(hbox2, 0, wxGROW|wxALL,0);

        //pack..
        wxGridSizer* gs = new wxGridSizer(1, 2, 1, 1);
        gs->Add(leftPanel, 0, wxEXPAND | wxALL, 0);
        gs->Add(rightPanel, 0, wxEXPAND | wxALL, 0);
        container->SetSizer(gs);
    }

    wxSizer* pSizer = this->PPanel->GetSizer();
    assert(pSizer != NULL);

    pSizer->Add(container, 0, wxEXPAND | wxALL);
    pSizer->Layout();

    //layout
    this->PPanel->Layout();
    this->PPanel->Centre();

    //display records.
    this->numDisplayRecords = 1;
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::BindControls() {
    //@@preconditions
    assert(this->PPanel != NULL);
    assert(this->PTextCommand != NULL);
    //@@end preconditions

    //bind 
    this->PPanel->Bind(wxEVT_COMMAND_TEXT_ENTER, &cpl_wxMainOutputPanel::OnInputCommand, this, this->PTextCommand->GetId());
    this->PPanel->Bind(wxEVT_SCROLL_LINEUP, &cpl_wxMainOutputPanel::OnScrollCommand, this, this->POutputScrollBar->GetId());
    this->PPanel->Bind(wxEVT_SCROLL_LINEDOWN, &cpl_wxMainOutputPanel::OnScrollCommand, this, this->POutputScrollBar->GetId());
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::OnInputCommand(wxCommandEvent& event) {
    //@@preconditions
    assert(this->PTextCommand != NULL);
    //@@end preconditions

    wxString command = this->PTextCommand->GetValue();
    const char* input = command.mb_str();
    if (input == NULL || input[0] == '\0') {
        return;
    }

    //execute command.
    this->PTextCommand->SetLabelText(wxString::Format("%s", ""));
    cpl_Action* handler = NULL;
    this->Owner->GetMainScriptHandler(handler);
    assert(handler != NULL);
   
    handler->SetText(command.mb_str());
    handler->Execute();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::OnScrollCommand(wxScrollEvent& event) {

    int posOnScroll = event.GetPosition();
    int posLookup   = this->posInsert - this->numDisplayRecords;
    if (posLookup < 0) {
        posLookup = 0;
    }
    
    //compare with scroll position.
    if (posOnScroll > posLookup) {
        this->posLookup = posLookup;
    }
    else {
        this->posLookup = posOnScroll;
    }
    this->SynchorizeWithDisplay();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::OutputText(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions

    //input text first.
    cpl_OutputProxyImp::OutputText(text);

    int pos = this->posInsert-this->numDisplayRecords;
    if (pos > 0) {
        this->posLookup = pos;
    }
    else {
        this->posLookup = 0;
    }

    //synchronize with display.
    this->SynchorizeWithDisplay();    
}

//-----------------------------------------------------------------------------
void cpl_wxMainOutputPanel::SynchorizeWithDisplay() {
    //@@preconditions
    assert(this->posLookup >= 0);
    //@@end preconditions

    for (int i = 0; i < this->numDisplayRecords; i++) {
        const char* itemString = this->stringBuffer->GetItemText(this->posLookup+i);
        if (itemString != NULL) {        
            this->POutputMessage[i]->SetLabel(wxString::Format("%s", itemString));
            this->POutputMessage[i]->Refresh();
            this->POutputMessage[i]->Update();
        }   
    }

    //.
    this->POutputScrollBar->SetScrollbar(this->posLookup, this->numDisplayRecords, this->posInsert, this->numDisplayRecords);
}

//-----------------------------------------------------------------------------
IOutputMessage* cpl_wxMainOutputPanel::GetOutputMessageImp() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions

    return (IOutputMessage*)this->POutput;
}

//-----------------------------------------------------------------------------
cpl_wxMainOutputPanel::cpl_wxMainOutputPanel(cpl_wxMainFrame* pOwner) : Owner(pOwner), PAuiManager(NULL), PThePanel(NULL), PPanel(NULL), PTextCommand(NULL), POutput(NULL), POutputScrollBar(NULL) {
    this->numDisplayRecords = 0;
}

//-----------------------------------------------------------------------------
cpl_wxMainOutputPanel::~cpl_wxMainOutputPanel() {
    while (this->PPanel-> GetEventHandler() != this->PPanel)
	((wxWindow *) this->PPanel)->PopEventHandler(false);

    if (this->POutput) delete this->POutput;
}
