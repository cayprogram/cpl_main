#ifndef CPL_WXMAINOGLPANELMANAGER_H
#define CPL_WXMAINOGLPANELMANAGER_H

//-----------------------------------------------------------------------------
// class cpl_wxMainOGLPanelManager
//-----------------------------------------------------------------------------
//
class cpl_wxMainOGLPanelManager {

public:
    // create.
    wxPanel* Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager);

    // create opengl panel
    void CreateOGLPanels();

    // cleanup 
    void Cleanup();

    // active OpenGL win
    void ActiveOGLWinByIndex(int idx);

    // get active OGL win
    void GetActiveOGLWin(int& wid, int& idx);

public:
    // get OGL win id 
    int GetOGLWinId(int idx);

    // get OGL win idx
    int GetOGLWinIdx(int wID);

public:
    // switch layout mode 
    void SwitchLayoutMode();

    // do layout
    void DoLayout();

    /** do exchange */
    void DoExchangeOGLWin(int comp_src, int comp_target);

public:
    /** get layout implementation */
    ILayoutProxy* GetLayoutProxyImp();

public:
    enum { MAX_OGLWIN_NUM = 4 };

    // Constructor.
    cpl_wxMainOGLPanelManager(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainOGLPanelManager();

private:
    friend class cpl_wxOGLPanel;
    friend class cpl_wxMainOGLPanelManagerLayout;

    cpl_wxMainFrame* Owner;  //owner.
    cpl_wxMainOGLPanelManagerLayout* Layout;

    //wxWidgets.
    wxPanel *PPanel;
    cpl_wxOGLPanel* POGLWins[MAX_OGLWIN_NUM];

    //get active OGL win
    void GetActiveOGLWin(cpl_wxOGLPanel*& OGLWin);
};

#endif //CPL_WXMAINOGLPANELMANAGER_H
