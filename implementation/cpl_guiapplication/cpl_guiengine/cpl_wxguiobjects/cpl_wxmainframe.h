#ifndef CPL_WXMAINFRAME_H
#define CPL_WXMAINFRAME_H

#define MAX_SUPPORT_WIN_NUM 4

class cpl_wxMainFrame : public wxFrame {
public:
    // create.
    void Create();

    // destroy.
    bool Destroy();

    // cleanup
    void Cleanup();

    // get main script handler
    void GetMainScriptHandler(cpl_Action*& handler);

    // set window title 
    void SetWindowTitle(const char* title);

public:
    /** set busy on/off */
    void SetBusyOnOff(int state);

    /** output window on/off */
    void SetOutputWindowOnOff();

public:
    // update gui 
    void UpdateGUI();

    // post update GUI event .
    void PostGUIEvent(const char* hint);

public:
    // wininfo
    // get system panel width
    int GetSystemPanelWidth();

    // get system panel height
    int GetSystemPanelHeight();

    // get session panel width
    int GetSessionPanelWidth();

    // get session panel height
    int GetSessionPanelHeight();

    // get output panel width
    int GetOutputPanelWidth();

    // get output panel height
    int GetOutputPanelHeight();

    // get status bar height 
    int GetStatusBarHeight();

    // get tool bar height.
    int GetToolBarHeight();

    // get tool box width
    int GetToolBoxWidth();

    // get task panel width.
    int GetTaskPanelWidth();

public:
    //services provided.
    /** Panel proxy*/
    virtual IPanelProxy* GetTaskPanelProxy();

    /** get implementation */
    virtual IOutputMessage* GetOutputMessage();

    /** Output status info */
    virtual IOutputStatusInfo* GetOutputStatusInfoHandler();

    /** Graphic window info */
    virtual IGraphicWindowInfo* GetGraphicWindowInfoHandler();

    /** Plugin tree */
    virtual IPluginTree* GetPluginTree();

    /** Icon */
    virtual IResImageProxy* GetIconProxy();

    /** Image */
    virtual IResImageProxy* GetImageProxy();

    /** get layout implementation */
    virtual ILayoutProxy* GetLayoutProxyImp();

    /** get thread func */
    virtual IThreadFunc* GetThreadFunc();

public:
    /** Get system window hander */
    virtual void* GetSystemWindowRawHandler();

    /** Get session window hander */
    virtual void* GetSessionWindowRawHandler();

    // get update menu
    virtual wxMenu* GetContextMenu();

public:
    /** exec graphic idle callback */
    virtual int ExecGraphicEngineIdleCallback();

    /** exchange graphic window*/
    virtual int ExchangeGraphicWindow(int source, int target);

public:
    //icons tools
    virtual void GetIcon(const char* iconId, wxBitmap& bitmap);
    virtual wxBitmap& GetIcon(const char* iconId);

public:
    // Constructor.
    cpl_wxMainFrame(cpl_ApplicationMainWindowImp* pOwner, const wxString& title, wxSize size);

    // Destructor
    virtual ~cpl_wxMainFrame();

protected:
    // create sub windows.
    void CreateSubWindows(int w, int h);

    // measure string display size
    void MeasureStringDisplaySize(const char* string, wxSize& size);

private:
    friend class cpl_wxMainFrameInfo;
    friend class cpl_wxMainStatusbar;
    friend class cpl_wxMainContextMenu;
    friend class cpl_wxOGLPanel;
    friend class cpl_wxMainMenubar;
    friend class cpl_wxWorker;

    //owner.
    cpl_ApplicationMainWindowImp* Owner;

    //wx controls
    wxAuiManager *PAuiManager;
    wxPanel *PPanel;
    wxCriticalSection PThreadCS;    // protects the m_pThread pointer

    //worker thread.
    cpl_wxWorker* PWorker;


    //frame info management.
    cpl_wxMainFrameInfo* mainFrameInfo;

    //gui components
    cpl_wxMainMenubar* mainMenubar;
    cpl_wxMainToolbar* mainToolbar;
    cpl_wxMainToolbox* mainToolbox;
    cpl_wxMainStatusbar* mainStatusbar;
    cpl_wxMainOutputPanel* mainOutput;
    cpl_wxMainContextMenu* mainContextMenu;
    cpl_wxMainSystemPanel* mainSystemPanel;
    cpl_wxMainSessionPanel* mainSessionPanel;
    cpl_wxMainOGLPanelManager* mainOGLPanelManager;
    cpl_wxMainTaskPanelManager* mainTaskPanelManager;

    //title
    char windowTitle[2048];

    //event handler.
    void OnCustomEvent(wxCommandEvent& event);

    //thread event
    void OnThreadEnter(wxThreadEvent& event);
    void OnThreadLeave(wxThreadEvent& event);
    void OnThreadUpdate(wxThreadEvent& event);

    //update gui direct
    void UpdateGUIDirect(const char* hint);

    //init
    void Init();
};

#endif //CPL_WXMAINFRAME_H
