#ifndef CPL_ICONINTERFACEPROXY_H
#define CPL_ICONINTERFACEPROXY_H

//////////////////////////////////////////////////////////////////////////
class cpl_IconCommonProxy : public cpl_Object, public IResImageProxy {
public:
    /** create instance */
    static cpl_IconCommonProxy * New();

public:  
    /** get image  */
    IImage* GetImage(const char *iconId);

public:
    /** load all registered icons */
    int LoadPluginIcons();

public:
    /** set plugin tree proxy */
    void SetPluginTreeProxy(IPluginTree * pltreePorxy) { this->m_plgtreeProxy = pltreePorxy; }

    /** set lua script proxy */
    void SetLuaScriptProxy(ILuaScriptProxy * luascriptProxy) { this->m_luascriptProxy = luascriptProxy; }

public:
    // constructor.
    cpl_IconCommonProxy();

    // destructor.
    virtual ~cpl_IconCommonProxy();

protected:
    cpl_IconImageManager * m_iconImageManager;
    cpl_IconManager      * m_iconManager;

private:
    IPluginTree     * m_plgtreeProxy;
    ILuaScriptProxy * m_luascriptProxy;

private:
    //get image by icon id
    cpl_Image * get_image(const char * iconId);
};

#endif //CPL_ICONINTERFACEPROXY_H
