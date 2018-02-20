#ifndef RUNTIMECONTEXTPROXYINTERFACE_H
#define RUNTIMECONTEXTPROXYINTERFACE_H

//check function.
typedef void (*CHECKFUNC) (void*);

class IRuntimeContextProxy {

public:
    /** Set break flag. */
    virtual void SetBreakFlagOn() = 0;
    
    /** set busy flag on/off */
    virtual void SetBusyFlagOn() = 0;
    virtual void SetBusyFlagOff() = 0;
    
    /** wait for time. */
    virtual void Wait(double ftime) = 0;
    
    /** wait until */
    virtual void WaitUntil(int& status, int& ret, const char* message, int askBeforeExit) = 0;
        
    /** update command GUI */
    virtual void UpdateCommandGUI() = 0;

    /** full screen on/off */
    virtual void FullScreenOn() = 0;    
    virtual void FullScreenOff() = 0;
    
    /** set window title */
    virtual void SetWindowTitle(const char* title) = 0;
    
    /** iconize */
    virtual void Iconize() = 0;

    /** about */
    virtual void About() = 0;

    /** add check function */
    virtual void AddCheckFunction(CHECKFUNC func, void* data) = 0;
    
    /** remove check function */
    virtual void RemoveCheckFunction() = 0;

    /** get console mode */
    virtual int  IsConsoleModeOn() = 0;

    /** asys call */
    virtual void AsysCallFunction(CHECKFUNC func, void* data, float t) = 0;

    /** set gui command context */
    virtual void SetGUICommandContext(const char* context) = 0;

    /** get gui command context */
    virtual void GetGUICommandContext(const char*& context) = 0;

    /** synchronize with outer context */
    virtual void SyncWithOuterContext(const char* context, void* clientData) = 0;

    /** report error */
    virtual void ReportError(const char* text) = 0;

    /** get application path */
    virtual void GetApplicationPath(char szPath[], int mode) = 0;

    /** message (IDYES, IDNO, IDCANCEL) */
    virtual int  Message(const char* text) = 0;

    /** project */
    virtual int  NewProject(const char* projectFilter, const char* initDirectory, int& index, char projectName[], char projectPath[]) = 0;
};

#endif //RUNTIMECONTEXTPROXYINTERFACE_H

