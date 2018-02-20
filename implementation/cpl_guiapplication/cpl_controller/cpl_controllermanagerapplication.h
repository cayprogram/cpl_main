#ifndef CPL_APPLICATIONPOSTCONTROLLERMANAGER_H
#define CPL_APPLICATIONPOSTCONTROLLERMANAGER_H

class cpl_ApplicationControllerManager : public cpl_ControllerManager {
public:
    /** create Instance */
    static cpl_ApplicationControllerManager * New();
    
public:    
    /** Initialize */
    virtual void DoInitialization(int argc, char * * argv);
    
    /** cleanup */
    virtual void DoCleanup();
    
public:
    /** Do Command Id */
    virtual int DoCommand(char* scriptcomand, void* userData, char* cmdData);
    
    /** load gui object factory */
    virtual int LoadGUIObjectFactory();

    /** load component */
    virtual int LoadComponents();

    /** register script lib */
    virtual int RegisterScriptLib();

public:
    /** run session */
    virtual void RunSessionFile(const char* fname);

public:
    //constructor.
    cpl_ApplicationControllerManager() {}

    //destructor
    virtual ~cpl_ApplicationControllerManager();    

protected:
    //handle callback
    void OnGraphicWindowClicked(void* data);
    void OnGraphicWindowContextMenu(void* data);
    void OnGraphicWindowDoubleClicked(void* data);

    //inner method
    void LuaScript(const char* command);

    //test thread callback.
    void OnThreadTest();
    static void OnThreadTestCallback(void* callData, void* clientData);
};

#endif //CPL_APPLICATIONPOSTCONTROLLERMANAGER_H
