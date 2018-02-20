#ifndef CPL_IMAGEPROXY_H
#define CPL_IMAGEPROXY_H

class IResImageProxy;

//////////////////////////////////////////////////////////////////////////
class cpl_ImageProxy : public cpl_Controller {
public:
    /** create instance */
    static cpl_ImageProxy* New();

public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

public:
    /** load all registered images */
    int LoadPluginImages();

public:
    /** set plugin tree proxy */
    void SetPluginTreeProxy(cpl_PluginTreeProxy * pltreePorxy);

    /** set main script proxy */
    void SetLuaScriptProxy(cpl_LuaProxy * luascriptProxy);

public:
    /** get implementation */
    IResImageProxy* GetImageProxy();

protected:        
    //constructor.
    cpl_ImageProxy();

    //destructor
    virtual ~cpl_ImageProxy();
    
    //implementation.
    class cpl_Implemenation;
    cpl_Implemenation* Implementaion;
};

#endif //CPL_IMAGEPROXY_H
