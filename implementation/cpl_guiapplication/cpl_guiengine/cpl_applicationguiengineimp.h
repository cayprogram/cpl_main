#ifndef CPL_APPLICATIONGUIENGINEIMP_H
#define CPL_APPLICATIONGUIENGINEIMP_H

//check function.
typedef void (*CHECKFUNC) (void*);

class cpl_wxApp;
class cpl_FileIOProxy;
class cpl_ApplicationGUIEngineImp : public cpl_GUIEngineImp {

public:
    /** Initialize the rendering window. */
    virtual void Initialize(int argc, char * * argv);

    /** clean up before leaving. */
    virtual void Cleanup();

    /** enter event loop. */
    virtual void EnterMainLoop(void);

    /** set busy flag on/off */
    virtual void SetBusyFlagOn();
    virtual void SetBusyFlagOff();

    /** Set break flag. */
    virtual void SetBreakFlagOn();

    /** set GUI engine */
    virtual void SetGUIEngine(cpl_GUIEngine* engine);    

    /** update */
    virtual void UpdateGUI();

    /** set window title */
    virtual void SetWindowTitle(const char* title);

public:
    /** exec check function */
    virtual int  ExecCheckFunction();

    /** exec idle function */
    virtual int  ExecIdleFunction();

    /** exec graphic idle callback */
    virtual int  ExecGraphicEngineIdleCallback();

public:
    /** add check function */
    virtual void AddCheckFunction(CHECKFUNC func, void* data);
    
    /** remove check function */
    virtual void RemoveCheckFunction();

    /** add idle function */
    virtual void AddIdleFunction(CHECKFUNC func, void* data);

    /** remove idle function */
    virtual void RemoveIdleFunction();

public:
    /** get runtime context */
    IRuntimeContextProxy* GetRuntimeContextProxy();

public:
    struct _fbCheckFunc {
        CHECKFUNC checkFunction; 
        void* data;
    };

    /** constructor */
    cpl_ApplicationGUIEngineImp();

    /** destructor */
    virtual ~cpl_ApplicationGUIEngineImp();

    //protected variables.
    cpl_GUIEngine* engineGUI;

    //wxwidgets..
    cpl_wxApp* theApp;

    //callback.
    _fbCheckFunc  pCheckFunc;
    _fbCheckFunc  pIdleFunc;

    class RuntimeContextProxy;
    RuntimeContextProxy* pRuntimeContext;
};

#endif //CPL_APPLICATIONGUIENGINEIMP_H
