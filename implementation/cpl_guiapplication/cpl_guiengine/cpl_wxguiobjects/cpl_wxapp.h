#ifndef CPL_WXAPP_H
#define CPL_WXAPP_H

class cpl_wxApp : public wxApp {

public:
    /** override */
    bool OnInit();

    /** on run */
    int OnRun();

    /** on exit */
    int OnExit();

    /** set leave flag */
    void SetShouldLeave(bool flag);

public:
    cpl_wxApp(cpl_ApplicationGUIEngineImp* pOwner);

    // Destructor
    virtual ~cpl_wxApp();

    // When running with "fixed" framerate, called for each timer event (frame)
    void OnTimer( wxTimerEvent& event );
    void OnIdle( wxIdleEvent& event );

private:
    //inner structure
    struct _fbApplicationData {
        wxTimer* pTimer;
        int  nDisplayUpdateRate;
        bool bShouldLeave;
    };

    //owner.
    cpl_ApplicationGUIEngineImp* Owner;

    // the main application data structure
    _fbApplicationData AppData;

    //initialize/deinit app data.
    int InitApplicationData();
    int DeinitApplicationData();
};

#endif //CPL_WXAPP_H