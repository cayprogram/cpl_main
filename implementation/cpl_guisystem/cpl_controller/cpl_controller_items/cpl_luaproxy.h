#ifndef CPL_LUAPROXY_H
#define CPL_LUAPROXY_H

class cpl_LuaProxy : public cpl_Controller {

public:
    /** create instance */
    static cpl_LuaProxy* New();

public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

    /** execute command */
    virtual void Execute(const char* buffer) ;

    /** run script file */
    virtual void RunScriptFile(const char* fname) ;

    /** run script buffer */
    virtual void RunScriptString(const char* buffer) ;

    /** create script context */
    virtual void CreateScriptContext();

    /** register lib. */
    virtual void RegisterLib(lua_RegisterLib func);
    
    /** register lib. */
    virtual void RegisterLib(const char* libname);

    /** get main lua state */
    virtual void* GetMainLuaState();

public:
    /** get implementation */
    ILuaScriptProxy* GetImplementation();

protected:        
    //constructor.
    cpl_LuaProxy();

    //destructor
    virtual ~cpl_LuaProxy();

    //protected variables.
    class Implemenation;
    Implemenation * scriptProxy;
};

#endif //CPL_LUAPROXY_H
