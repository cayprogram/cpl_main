#ifndef CPL_WXMAINSYSTEMPANEL_H
#define CPL_WXMAINSYSTEMPANEL_H

class cpl_wxMainSystemPanel {

public:
    // create.
    wxPanel* Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h);

    // get panel 
    wxPanel* GetPanel();

public:
    // show/hide.
    void Show();
    void Hide();

public:
    // Constructor.
    cpl_wxMainSystemPanel(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainSystemPanel();

private:
    //owner.
    cpl_wxMainFrame* Owner;

    //wxwidgets.
    wxPanel *PPanel;
    wxAuiManager* PAuiManager;
    wxAuiPaneInfo PaneInfo;

    class wxThePanel;
    wxThePanel* PThePanel;
};

#endif //CPL_WXMAINSYSTEMPANEL_H
