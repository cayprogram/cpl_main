#include <wx/graphics.h>
#include "cpl_wxprogresspanel.h"
#include "cpl_wxbitmaps.h"

//-----------------------------------------------------------------------------
void cpl_wxProgessPanel::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    if (this->value > 0 && this->value <= 1000) { 
        wxGraphicsContext* gc = wxGraphicsContext::Create(this);
        const wxSize size = GetSize();

        gc->SetBrush(wxBrush(wxColour(220, 220, 220)));
        gc->DrawRectangle(0, 0, size.GetWidth(), size.GetHeight());

        gc->SetBrush(wxBrush(wxColour(0, 211, 40)));       
        int w = size.GetWidth()*float(this->value)/(1000.0);
        gc->DrawRectangle(0, 0, w, size.GetHeight());
        delete gc;
    }
}

//-----------------------------------------------------------------------------
void cpl_wxProgessPanel::SetValue(int value) {
    //@@preconditions
    assert(value >= 0 && value <= 1000);
    //@@end preconditions

    this->value = value;

    // Force a redraw
    this->Refresh();
}

//-----------------------------------------------------------------------------
cpl_wxProgessPanel::cpl_wxProgessPanel(wxPanel* parent) : wxPanel(parent, wxID_ANY), value(0) {
    this->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    this->Bind(wxEVT_PAINT, &cpl_wxProgessPanel::OnPaint, this);
}

//-----------------------------------------------------------------------------
cpl_wxProgessPanel::~cpl_wxProgessPanel() {
}
