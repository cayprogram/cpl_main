#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxmainstatusbar.h"
#include "cpl_wxcontrols/cpl_wxprogresspanel.h"

//-----------------------------------------------------------------------------
// class cpl_wxMainStatusbar::OutputStatusInfo
//-----------------------------------------------------------------------------
//
class cpl_wxMainStatusbar::OutputStatusInfo : public IOutputStatusInfo {  
public:
    /** status text A */
    void StatusTextA(const char* text);
    void StatusTextB(const char* text);
    void StatusTextC(const char* text);

    /** status progress */
    void SetProgressStatus(int state);
    void SetProgressValue(float value);

public:
    //constructor
    OutputStatusInfo(cpl_wxMainStatusbar* pOwner) : Owner(pOwner) {}

    //destructor.
    virtual ~OutputStatusInfo() {}

protected:
    cpl_wxMainStatusbar* Owner;
};

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusInfo::StatusTextA(const char* text) {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    this->Owner->OutputStatusA(text);
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusInfo::StatusTextB(const char* text) {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    this->Owner->OutputStatusB(text);
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusInfo::StatusTextC(const char* text) {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    this->Owner->OutputStatusC(text);
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusInfo::SetProgressStatus(int state) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(state == 0 || state == 1);
    //@@end preconditions

    this->Owner->SetProgressStatus(state);
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusInfo::SetProgressValue(float value) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(value >= 0);
    //@@end preconditions

    this->Owner->SetProgressValue(value);
}

//-----------------------------------------------------------------------------
// class cpl_wxMainStatusbar
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainStatusbar::Create(int w, int h) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(w > 0);
    assert(h > 0);
    //@@end preconditions

    wxSize sampleSize;
    this->Owner->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);

    int bw = sampleSize.x;
    int bh = sampleSize.y+6;
    this->PPanel = new wxPanel(this->Owner, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    assert(this->PPanel != NULL);

    this->PPanel->SetSize(w, bh);
    this->PPanel->SetMaxSize(wxSize(-1, bh));
    this->PPanel->SetBackgroundColour(wxColour(4, 122, 172));
    //this->PPanel->SetBackgroundColour(wxColour(0, 122, 204));
    //this->PPanel->SetBackgroundColour(wxColour(38, 69, 81));

    //create sub controls.
    this->CreateSubControls(bw, bh);
    this->BindControls();

    return this->PPanel;
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::CreateSubControls(int bw, int bh) {
    //@@preconditions
    assert(bw > 0);
    assert(bh > 0);
    //@@end preconditions

    //icon
    this->Owner->GetIcon("SYS_ICON_STATUSBAR_BUSYON", this->BitmapBusyOn);
    this->Owner->GetIcon("SYS_ICON_STATUSBAR_BUSYOFF", this->BitmapBusyOff);

    //create controls.
    this->PStatusA = new wxStaticText(this->PPanel, wxID_ANY, _T(""));
    this->PStatusB = new wxStaticText(this->PPanel, wxID_ANY, _T(""));
    this->PStatusC = new wxStaticText(this->PPanel, wxID_ANY, _T(""));

    this->PStatusA->SetMinSize(wxSize(bw*3, bh));
    this->PStatusB->SetMinSize(wxSize(bw, bh));
    this->PStatusC->SetMinSize(wxSize(bw, bh));

    this->PStatusA->SetForegroundColour(wxColour(240, 240, 240));
    this->PStatusB->SetForegroundColour(wxColour(240, 240, 240));
    this->PStatusC->SetForegroundColour(wxColour(240, 240, 240));

    wxPanel* _subPanelA = new wxPanel(this->PPanel, wxID_ANY, wxDefaultPosition);
    _subPanelA->SetMinSize(wxSize(bw/2, bh));
    _subPanelA->SetMaxSize(wxSize(bw/2, bh));
    //_subPanelA->SetBackgroundColour(wxColour(240, 240, 240));
    {
        this->PProcessBar = new cpl_wxProgessPanel(_subPanelA);
        this->PProcessBar->SetMinSize(wxSize(bw/2, bh));
        this->PProcessBar->SetMaxSize(wxSize(bw/2, bh));
        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(this->PProcessBar, 1, wxEXPAND | wxALL, 3);
        _subPanelA->SetSizer(vbox);
    }

#ifdef _DEBUGA
    this->PStatusA->SetBackgroundColour(wxColour(177, 177, 177));
    this->PStatusB->SetBackgroundColour(wxColour(177, 177, 177));
    this->PStatusC->SetBackgroundColour(wxColour(200, 177, 177));
#endif

    wxPanel* _subPanel = new wxPanel(this->PPanel, wxID_ANY, wxDefaultPosition, wxSize(bh, bh));
    {
        this->PSignal = new wxStaticBitmap(_subPanel, wxID_ANY, wxNullBitmap, wxPoint(0, 0), wxSize(16, 16));
        this->PSignal->SetBitmap(this->BitmapBusyOff);

        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(this->PSignal, 1, wxEXPAND | wxALL, 0);
        _subPanel->SetSizer(vbox);
    }
 
    wxStaticText* empty = new wxStaticText(this->PPanel, wxID_ANY, _T(""));
    empty->SetMinSize(wxSize(10, bh));

    //do layout
    wxBoxSizer * vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * hbox = new wxBoxSizer(wxHORIZONTAL);
    {        
        wxBoxSizer * vbox1 = new wxBoxSizer(wxVERTICAL);
        {
            wxBoxSizer * hbox1 = new wxBoxSizer(wxHORIZONTAL);
            hbox1->Add(empty,              0, wxALIGN_CENTRE_VERTICAL|wxBOTTOM | wxTOP);
            hbox1->Add(this->PStatusA,     0, wxALIGN_CENTRE_VERTICAL|wxBOTTOM | wxTOP);
            hbox1->Add(this->PStatusB,     0, wxALIGN_CENTRE_VERTICAL|wxBOTTOM | wxTOP);
            hbox1->Add(this->PStatusC,     0, wxALIGN_CENTRE_VERTICAL|wxBOTTOM | wxTOP);
            hbox1->Add(_subPanelA,         0, wxALIGN_CENTRE_VERTICAL|wxBOTTOM | wxTOP);
            vbox1->Add(hbox1, 1, wxEXPAND | wxALL, 2);
        }
        wxBoxSizer * vbox2 = new wxBoxSizer(wxVERTICAL);
        {
            wxBoxSizer * hbox2 = new wxBoxSizer(wxHORIZONTAL);
            hbox2->Add(_subPanel, 0, wxEXPAND | wxALL);
            vbox2->Add(hbox2, 1, wxEXPAND | wxALL, 0);
        }
        hbox->Add(vbox1, 1, wxEXPAND | wxALL, 0);
        hbox->Add(vbox2, 0, wxEXPAND | wxALL, 0);
    }
    vbox->Add(hbox, 1, wxEXPAND | wxALL, 0);
    this->PProcessBar->Hide();
    this->PPanel->SetSizer(vbox);
    this->PPanel->GetSizer()->SetSizeHints(this->PPanel);
    this->PPanel->Layout();
    this->PPanel->Centre();
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::BindControls() {
    //@@preconditions
    assert(this->PPanel != NULL);
    //@@end preconditions
}

//-----------------------------------------------------------------------------
IOutputStatusInfo* cpl_wxMainStatusbar::GetOutputStatusInfoHandler() {
    //@@preconditions
    assert(this->PStatusInfo != NULL);
    //@@end preconditions

    return this->PStatusInfo;
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusA(const char* text) {
    //@@preconditions
    assert(this->PStatusA != NULL);
    //@@end preconditions

    this->PStatusA->SetLabel(text == NULL? wxString(" "): wxString(text));
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusB(const char* text) {
    //@@preconditions
    assert(this->PStatusB != NULL);
    //@@end preconditions

    this->PStatusB->SetLabel(text == NULL? wxString(" "): wxString(text));
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::OutputStatusC(const char* text) {
    //@@preconditions
    assert(this->PStatusC != NULL);
    //@@end preconditions

    this->PStatusC->SetLabel(text == NULL? wxString(" "): wxString(text));
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::SetBusyOnOff(int state) {
    //@@preconditions
    assert(state == 0 || state == 1);
    assert(this->PSignal != NULL);
    //@@end preconditions

    this->PSignal->SetBitmap((state == 0)? this->BitmapBusyOff: this->BitmapBusyOn);
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::SetProgressStatus(int state) {    
    //@@preconditions
    assert(state == 0 || state == 1);
    assert(this->PProcessBar != NULL);
    //@@end preconditions

    this->PProcessBar->Show(state);
    this->PProcessBar->GetParent()->Layout();
}

//-----------------------------------------------------------------------------
void cpl_wxMainStatusbar::SetProgressValue(float value) {
    //@@preconditions
    assert(this->PProcessBar != NULL);
    //@@end preconditions

    this->PProcessBar->SetValue((int)value);
    this->PProcessBar->Update();
}

//-----------------------------------------------------------------------------
cpl_wxMainStatusbar::cpl_wxMainStatusbar(cpl_wxMainFrame* pOwner) : Owner(pOwner), PPanel(0), PSignal(0), PProcessBar(0) {
    this->PStatusA = NULL;
    this->PStatusB = NULL;
    this->PStatusC = NULL;
    this->PStatusInfo = new OutputStatusInfo(this);
}

//-----------------------------------------------------------------------------
cpl_wxMainStatusbar::~cpl_wxMainStatusbar() {
    if (this->PStatusInfo != NULL) {
        delete this->PStatusInfo;
        this->PStatusInfo = NULL;
    }
}
