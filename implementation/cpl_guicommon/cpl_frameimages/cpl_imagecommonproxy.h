#ifndef CPL_IMAGECOMMONPROXY_H
#define CPL_IMAGECOMMONPROXY_H

//////////////////////////////////////////////////////////////////////////
class cpl_ImageCommonProxy : public cpl_Object, public IResImageProxy {
public:
    /** create instance */
    static cpl_ImageCommonProxy * New();

public:  
    /** get image  */
    IImage* GetImage(const char *imgId);

public:
    /** load all registered images */
    int LoadPluginImages();

public:
    /** set plugin tree proxy */
    void SetPluginTreeProxy(IPluginTree * pltreePorxy) { this->m_plgtreeProxy = pltreePorxy; }

    /** set lua script proxy */
    void SetLuaScriptProxy(ILuaScriptProxy * luascriptProxy) { this->m_luascriptProxy = luascriptProxy; }

public:
    //constructor
    cpl_ImageCommonProxy();

    //destructor
    virtual ~cpl_ImageCommonProxy();

private:
    cpl_ImageManager  * m_imageManager;

    IPluginTree      * m_plgtreeProxy;
    ILuaScriptProxy  * m_luascriptProxy;
};

#endif //CPL_IMAGECOMMONPROXY_H
