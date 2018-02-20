#ifndef CPL_MAINWINDOW_H
#define CPL_MAINWINDOW_H

class cpl_MainWindowImp;
class cpl_MainWindow : public cpl_WidgetComposite {

public:
    /** Create instance */
    static cpl_MainWindow* New();

public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();    

    /** Create sub window. */
    virtual void CreateSubWindows();
    
    /** Show */
    virtual void Show(bool bshow);
    
    /** Update command GUI */
    virtual void UpdateCommandGUI();

    /** set window title */
    virtual void SetWindowTitle(const char* title);

public:
    /** set busy on/off */
    virtual void SetBusyOnOff(int state);

    /** output window on/off */
    virtual void SetOutputWindowOnOff();

public:
    /** Get main window raw pointer*/
    virtual void* GetMainWindowRawHandler();

    /** Get system window hander */
    virtual void* GetSystemWindowRawHandler();

    /** Get session window hander */
    virtual void* GetSessionWindowRawHandler();

    /** Set main script proxy */
    virtual void SetMainScripHandler(cpl_Action* handler);

    /** Get main script proxy */
    virtual void GetMainScripHandler(cpl_Action*& handler);

public:
    /** set main plugin tree*/
    virtual void SetMainPluginTree(IPluginTree* plugin);

    /** set main icon proxy*/
    virtual void SetMainIconProxy(IResImageProxy* iconHandler);

    /** set main image proxy*/
    virtual void SetMainImageProxy(IResImageProxy* imageHandler);

public:
    /** GUI services interface implementations */
    /** Panel proxy*/
    virtual IPanelProxy* GetTaskPanelProxy();

    /** get implementation */
    virtual IOutputMessage* GetOutputMessage();

    /** Output status info */
    virtual IOutputStatusInfo* GetOutputStatusInfoHandler();

    /** Graphic window info */
    virtual IGraphicWindowInfo* GetGraphicWindowInfoHandler();

    /** get layout implementation */
    virtual ILayoutProxy* GetLayoutProxy();

    /** Plugin tree */
    virtual IPluginTree* GetPluginTree();

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
    cpl_MainWindow();

    //destructor
    virtual ~cpl_MainWindow();

protected:
    /** Initialize window.*/
    virtual void WindowInitialization();

private:
    //private variables.
    cpl_MainWindowImp   * mainWinImp;
    cpl_Action          * mainScriptHandler;
    IPluginTree        * mainPluginTree;
    IResImageProxy     * mainIconHandler;
    IResImageProxy     * mainImageHandler;
};

#endif //CPL_MAINWINDOW_H
