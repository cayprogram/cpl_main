#ifndef CPL_SCRIPTPROXY_H
#define CPL_SCRIPTPROXY_H

class cpl_ScriptProxy : public cpl_Controller {

public:
    /** create instance */
    static cpl_ScriptProxy* New();

public:
    /** Initialize.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

public:    
    /** Get script command handler */
    virtual cpl_Action* GetScriptHandler();

protected:        
    //constructor.
    cpl_ScriptProxy();

    //destructor
    virtual ~cpl_ScriptProxy();

    //protected variables.
    cpl_MenuItem * scriptProxy;
};

#endif //CPL_SCRIPTPROXY_H
