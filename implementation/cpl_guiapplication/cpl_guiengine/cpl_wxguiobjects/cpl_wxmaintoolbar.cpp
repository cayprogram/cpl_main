#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxmaintoolbar.h"
#include "cpl_wxmaintoolbarnormal.h"


//-----------------------------------------------------------------------------
// class cpl_wxMainToolbar
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
#if 0
wxPanel* cpl_wxMainToolbar::Create(int w, int h) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(w > 0);
    assert(h > 0);
    //@@end preconditions

    this->PPanel = new wxPanel(this->Owner, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    this->PPanel->SetSize(w, h);
    this->PPanel->SetMinSize(wxSize(-1, h));
    this->PPanel->SetBackgroundColour(wxColour(223, 226, 229));
    //this->PPanel->SetBackgroundColour(wxColour(204, 209, 212));
    //this->PPanel->SetBackgroundColour(wxColour(128, 125, 120));
    //this->PPanel->SetBackgroundColour(wxColour(173, 179, 183));
    //this->PPanel->SetBackgroundColour(wxColour(6, 132, 200));
    //this->PPanel->SetBackgroundColour(wxColour(4, 122, 172));
    //this->PPanel->SetBackgroundColour(wxColour(153, 169, 188));

    //create sub controls.
    //this->CreateSubControls(bw, bh);
    //this->BindControls();

    this->boxw = w;
    this->boxh = h;

    return this->PPanel;
}
#endif

//-----------------------------------------------------------------------------
cpl_wxMainToolbar::cpl_wxMainToolbar(cpl_wxMainFrame* pOwner) : Owner(pOwner), PPanel(0) {
    this->tbBOXw = 0;
    this->tbBOXh = 0;
}

//-----------------------------------------------------------------------------
cpl_wxMainToolbar::~cpl_wxMainToolbar() {
}
