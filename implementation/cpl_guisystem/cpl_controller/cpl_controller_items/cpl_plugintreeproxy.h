#ifndef CPL_PLUGINTREEPROXY_H
#define CPL_PLUGINTREEPROXY_H

class ILuaScriptProxy;
class cpl_Creator;
class cpl_PluginTreeProxy : public cpl_Controller {

public:
    /** create instance */
    static cpl_PluginTreeProxy* New();

public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

    /** set lua VM */
    virtual int SetLuaState(void* luaState);

    /** parse */
    virtual int Parse(const char* path);

    /** load lua script file */
    virtual int LoadLuaScriptPackage();

    /** load lua runtime dlls */
    virtual int LoadLuaRuntimePackage();

    /** load class creator runtime dlls */
    virtual int LoadClassCreatorRuntimePackage(cpl_Creator* pCreator);

public:
    /** get implementation */
    IPluginTree* GetPluginTree();

protected:        
    //constructor.
    cpl_PluginTreeProxy();

    //destructor
    virtual ~cpl_PluginTreeProxy();
    
    //implementation.
    class cpl_Implemenation;
    cpl_Implemenation* Implementaion;
};

#endif //CPL_PLUGINTREEPROXY_H
