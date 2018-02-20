#ifndef CPL_APPLICATIONMAINWINDOWIMP_H
#define CPL_APPLICATIONMAINWINDOWIMP_H

class cpl_wxMainFrame;
class cpl_ApplicationMainWindowImp: public cpl_MainWindowImp {

public:
    /** Initialize window, create window*/
    virtual void EnterWindowInitialization();

    /** Do clean up, encapsulate window*/
    virtual void LeaveWindowInitialization();

    /** Show window. */
    virtual void ShowWindow(bool bshow);   
    
    /** cleanup */
    virtual void Cleanup();

    /** update gui */
    virtual void UpdateGUI();

public:
    /** set busy on/off */
    virtual void SetBusyOnOff(int state);

    /** output window on/off */
    virtual void SetOutputWindowOnOff();

public:
    /** Get main window handler */
    virtual void* GetMainWindowRawHandler();
       
    /** Get system window hander */
    virtual void* GetSystemWindowRawHandler();

    /** Get session window hander */
    virtual void* GetSessionWindowRawHandler();

    /** set window title */
    virtual void SetWindowTitle(const char* title);

public:
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

    /** get layout implementation */
    virtual ILayoutProxy* GetLayoutProxyImp();

    /** Icon */
    virtual IResImageProxy* GetIconProxy();

    /** Image */
    virtual IResImageProxy* GetImageProxy();

    /** get thread func */
    virtual IThreadFunc* GetThreadFunc();

public:
    /** exec graphic idle callback */
    virtual int ExecGraphicEngineIdleCallback();

public:
    //constructor.
    cpl_ApplicationMainWindowImp(cpl_MainWindow* pOwner);

    //destructor
    virtual ~cpl_ApplicationMainWindowImp();
    
    //main window
    cpl_wxMainFrame* mainWin;
};

#endif //CPL_APPLICATIONMAINWINDOWIMP_H
