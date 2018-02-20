#ifndef CPL_MAINWINDOWIMP_H
#define CPL_MAINWINDOWIMP_H

class cpl_MainWindowImp {

public:
    /** create instance */
    static cpl_MainWindowImp* New(cpl_MainWindow* pOwner);

public:
    /** Initialize window.*/
    virtual void EnterWindowInitialization() = 0;

    /** Do clean up */
    virtual void LeaveWindowInitialization() = 0;

    /** show window. */
    virtual void ShowWindow(bool bshow) = 0;

    /** cleanup */
    virtual void Cleanup() = 0;

    /** Update command GUI */
    virtual void UpdateGUI() = 0;

    /** set window title */
    virtual void SetWindowTitle(const char* title) = 0;

public:
    /** set busy on/off */
    virtual void SetBusyOnOff(int state) = 0;

    /** output window on/off */
    virtual void SetOutputWindowOnOff() = 0;

public:
    /** Get main window raw pointer*/
    virtual void* GetMainWindowRawHandler() = 0;

    /** Get system window hander */
    virtual void* GetSystemWindowRawHandler() = 0;

    /** Get session window hander */
    virtual void* GetSessionWindowRawHandler() = 0;

public:
    /** GUI services interface implementations */
    /** Panel proxy*/
    virtual IPanelProxy* GetTaskPanelProxy() = 0;

    /** get implementation */
    virtual IOutputMessage* GetOutputMessage() = 0;

    /** Output status info */
    virtual IOutputStatusInfo* GetOutputStatusInfoHandler() = 0;

    /** Graphic window info */
    virtual IGraphicWindowInfo* GetGraphicWindowInfoHandler() = 0;

    /** get layout implementation */
    virtual ILayoutProxy* GetLayoutProxyImp() = 0;

    /** get thread func */
    virtual IThreadFunc* GetThreadFunc() = 0;

public:
    /** exec graphic idle callback */
    virtual int ExecGraphicEngineIdleCallback() = 0;

public:
    //constructor.
    cpl_MainWindowImp(cpl_MainWindow* pOwner);

    //destructor
    virtual ~cpl_MainWindowImp();

    //protected variables.
    cpl_MainWindow* Owner;
};

#endif //CPL_MAINWINDOWIMP_H

