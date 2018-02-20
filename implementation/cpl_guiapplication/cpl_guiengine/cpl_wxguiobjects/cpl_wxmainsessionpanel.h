#ifndef CPL_WXMAINSESSIONPANEL_H
#define CPL_WXMAINSESSIONPANEL_H

class cpl_wxMainSessionPanel {

public:
    // create.
    wxPanel* Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h);

    // get panel 
    wxPanel* GetPanel();

public:
    // show/hide.
    void Show();
    void Hide();

    //set size
    void SetSize(const wxSize& size);

public:
    // Constructor.
    cpl_wxMainSessionPanel(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainSessionPanel();

private:
    //owner.
    cpl_wxMainFrame* Owner;

    //wxWidgets.
    wxPanel *PPanel;
    wxAuiManager* PAuiManager;
    wxAuiPaneInfo PaneInfo;

    class wxThePanel;
    wxThePanel* PThePanel;
};

#endif //CPL_WXMAINSESSIONPANEL_H
