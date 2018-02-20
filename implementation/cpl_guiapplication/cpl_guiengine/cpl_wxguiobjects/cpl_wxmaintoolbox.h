#ifndef CPL_WXMAINTOOLBOX_H
#define CPL_WXMAINTOOLBOX_H

class cpl_wxMainToolbox {

public:
    // create.
    wxPanel* Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h);

public:
    // Constructor.
    cpl_wxMainToolbox(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainToolbox();

private:
    //owner.
    cpl_wxMainFrame* Owner;

    //wxWidgets.
    wxPanel *PPanel;
};

#endif //CPL_WXMAINTOOLBOX_H
