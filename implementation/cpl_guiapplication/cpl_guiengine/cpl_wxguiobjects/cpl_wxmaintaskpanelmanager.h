#ifndef CPL_WXMAINTASKPANELMANAGER_H
#define CPL_WXMAINTASKPANELMANAGER_H

class cpl_wxMainTaskPanelManager {
public:
    // create.
    wxPanel* Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h);

    // create panels
    void CreatePanels();

    // cleanup 
    void Cleanup();

    // active task win.
    void ActiveTaskWinByIndex(int idx);

    // get active task win
    void GetActiveTaskWin(int& wid, int& idx);

    // get panel
    void GetTaskPanel(int wid, cpl_wxTaskPanel*& panel);

public:
    // get task win id 
    int GetTaskWinId(int idx);

    // get task win idx
    int GetTaskWinIdx(int wID);

public:
    // do layout
    void DoLayout();

public:
    /** Panel proxy*/
    IPanelProxy* GetTaskPanelProxy();

public:
    //constructor.
    cpl_wxMainTaskPanelManager(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainTaskPanelManager();

private:
    enum { MAX_TASKWIN_NUM = 4 };

    //owner.
    cpl_wxMainFrame* Owner;

    //wxwidgets.
    wxPanel *PPanel;

    class PanelProxy;
    PanelProxy* PPanelProxy;

    //sub task windows.
    cpl_wxTaskPanel* PTaskWins[MAX_TASKWIN_NUM];

private:
    //find specifc panel
    cpl_wxTaskPanel* FindPanel(int wid);

    //get active task win
    void GetActiveTaskWin(cpl_wxTaskPanel*& TWin);
};

#endif //CPL_WXMAINTASKPANELMANAGER_H
