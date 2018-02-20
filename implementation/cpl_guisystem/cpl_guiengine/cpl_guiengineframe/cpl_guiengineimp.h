#ifndef CPL_GUIENGINEIMP_H
#define CPL_GUIENGINEIMP_H

class cpl_GUIEngineImp {

public:
    /** initialize. */
    virtual void Initialize(int argc, char * * argv) = 0;

    /** clean up. */
    virtual void Cleanup() = 0;

    /** enter event loop. */
    virtual void EnterMainLoop(void) = 0;

    /** set busy flag on/off */
    virtual void SetBusyFlagOn()  = 0;
    virtual void SetBusyFlagOff() = 0;

    /** set break flag. */
    virtual void SetBreakFlagOn() = 0;
    
    /** set GUI engine */
    virtual void SetGUIEngine(cpl_GUIEngine* engine) = 0;

    /** Runtime context */
    virtual IRuntimeContextProxy* GetRuntimeContextProxy() = 0;

public:
    /** constructor */
    cpl_GUIEngineImp() {}

    /** destructor */
    virtual ~cpl_GUIEngineImp() {}    
};

#endif //CPL_GUIENGINEIMP_H
