#ifndef CPL_WXPROGRESSPANEL_H
#define CPL_WXPROGRESSPANEL_H

#include <wx/wx.h>

class cpl_wxProgessPanel : public wxPanel {
public:
    cpl_wxProgessPanel(wxPanel* parent);
    virtual ~cpl_wxProgessPanel();

    //set value.
    void SetValue(int value);

private:
    void OnPaint(wxPaintEvent& event);

    wxSize max_size;
    int value;
};

#endif //CPL_WXPROGRESSPANEL_H
