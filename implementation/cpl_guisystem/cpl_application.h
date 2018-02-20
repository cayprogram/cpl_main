#ifndef CPL_APPLICATION_H
#define CPL_APPLICATION_H

class cpl_ControllerManager;
class cpl_Application {
    
public:
    /** create function */
    static cpl_Application * Instance();
    
    /** release object. */
    static void Delete();
    
    /** set application */
    static void SetApplication(cpl_Application* app);
    
public:    
    /** Initialize. */
    virtual void Initialize(int argc, char * * argv);
    
    /** Cleanup. */
    virtual void Cleanup();
        
    /** Run loop */
    virtual void RunMainLoop();
    
    /** Set break flag. */
    virtual void SetBreakFlagOn();
    
    /** set busy flag on/off */
    virtual void SetBusyFlagOn();
    virtual void SetBusyFlagOff();
           
    /** set window title */
    virtual void SetWindowTitle(const char* title);
    
    /** get control manager */
    cpl_ControllerManager* GetControllerManager() { return this->mainControllerManager; }

public:
    /** run session */
    virtual void RunSessionFile(const char* fname);
    
    /** run lua script */
    virtual void RunLuaScriptFile(const char* fname);

    /** run lua script */
    virtual void RunLuaScriptCommand(const char* buffer);

protected:
    /** constructor */
    cpl_Application();

    /** destructor */
    virtual ~cpl_Application();

    //control managers
    cpl_ControllerManager*  mainControllerManager;
    
private:
    /** singleton instance */
    static cpl_Application * instance;
};

#endif //CPL_APPLICATION_H
