#ifndef CPL_ICONPROXY_H
#define CPL_ICONPROXY_H

class IResIconProxy;

//////////////////////////////////////////////////////////////////////////
class cpl_IconProxy : public cpl_Controller {
public:
    /** create instance */
    static cpl_IconProxy* New();

public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

public:
    /** load all registered icons */
    int LoadPluginIcons();

public:
    /** set plugin tree proxy */
    void SetPluginTreeProxy(cpl_PluginTreeProxy * pltreePorxy);

    /** set main script proxy */
    void SetLuaScriptProxy(cpl_LuaProxy * luascriptProxy);

public:
    /** get implementation */
    IResImageProxy* GetIconProxy();

protected:        
    //constructor.
    cpl_IconProxy();

    //destructor
    virtual ~cpl_IconProxy();
    
    //implementation.
    class cpl_Implemenation;
    cpl_Implemenation* Implementaion;
};

#endif //CPL_ICONPROXY_H
