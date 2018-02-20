#ifndef CPL_WXTASKPANEL_H
#define CPL_WXTASKPANEL_H

//-----------------------------------------------------------------------------
//class cpl_wxTaskPanel
//-----------------------------------------------------------------------------
//
class cpl_wxTaskPanel : public wxPanel {

public:
    /** do initialization */
    int Initialize();

    /** do cleanup */
    int Cleanup();

    /** get winId */
    int GetWinId();

    /** get raw win */
    wxPanel* GetRawWin();

public:
    /** active window */
    void DoActive();
    
    /** deactivate window */
    void DoDeactive();
    
    /** is active window */
    int  IsActive() {return this->WINInfo.isActived;}

public:
    // constructor.
    cpl_wxTaskPanel(cpl_wxMainTaskPanelManager* pOwner, wxPanel* parent);

    // destructor
    virtual ~cpl_wxTaskPanel();

private:
    //inner structure.
    struct _fbTaskInfo_s {
        int winId;   
        int isActived;
        wxPanel* pWin;
    };

    //owner.
    cpl_wxMainTaskPanelManager* Owner;

    //task panel
    _fbTaskInfo_s WINInfo;

    // create task window
    void CreateTaskWin(_fbTaskInfo_s& pInfo);
};

#endif //CPL_WXTASKPANEL_H
