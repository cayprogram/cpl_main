#ifndef CPL_GUIENGINE_H
#define CPL_GUIENGINE_H

class cpl_ControllerManager;
class cpl_GUIEngine {
public:
    /** create function */
    static cpl_GUIEngine * New();

    /** release this object */
    virtual void Release();

public:
    /** initialize. */
    virtual void Initialize(int argc, char * * argv);

    /** clean up. */
    virtual void Cleanup();

    /** show main window */
    virtual void ShowMainWindow(bool bshow);

    /** enter event loop. */
    virtual void EnterMainLoop(void);
    
    /** set busy flag on/off */
    virtual void SetBusyFlagOn();
    virtual void SetBusyFlagOff();

    /** set break flag. */
    virtual void SetBreakFlagOn();

    /** set window title */
    virtual void SetWindowTitle(const char* title);

    /** update command GUI */
    virtual void UpdateCommandGUI();

public:
    /** output window on/off */
    virtual void SetOutputWindowOnOff();

public:
    /** set main script handler */
    virtual void SetMainScripHandler(cpl_Action* handler);

    /** set main plugin tree*/
    virtual void SetMainPluginTree(IPluginTree* plugin);

    /** set main icon proxy*/
    virtual void SetMainIconProxy(IResImageProxy* icon);

    /** set main image proxy*/
    virtual void SetMainImageProxy(IResImageProxy* image);

    /** set controller manager */
    virtual void SetControllerManager(cpl_ControllerManager* pManager);

public:
    /** exec graphic idle callback */
    virtual int ExecGraphicEngineIdleCallback();

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

    /** Runtime context */
    virtual IRuntimeContextProxy* GetRuntimeContextProxy();

    /** get layout implementation */
    virtual ILayoutProxy* GetLayoutProxy();

    /** Get icon proxy */
    virtual IResImageProxy* GetIconProxy();

    /** Get image proxy */
    virtual IResImageProxy* GetImageProxy();

    /** get thread func */
    virtual IThreadFunc* GetThreadFunc();

public:
    /** get main window handler */
    virtual void* GetMainWindowHandler();
    
    /** Get system window hander */
    virtual void* GetSystemWindowRawHandler();

    /** Get session window hander */
    virtual void* GetSessionWindowRawHandler();

protected:
    /** constructor */
    cpl_GUIEngine();

    /** destructor */
    virtual ~cpl_GUIEngine();

private:
    cpl_GUIEngine(const cpl_GUIEngine &);
    void operator = (const cpl_GUIEngine &);

    //protected;
    cpl_GUIEngineImp* guiEngineImp;
    cpl_MainWindow* mainWindow;
    cpl_ControllerManager* controllerManager;
};

#endif //CPL_GUIENGINE_H
