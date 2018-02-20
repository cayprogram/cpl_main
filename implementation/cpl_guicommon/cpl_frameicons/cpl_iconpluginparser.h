#ifndef CPL_ICONPLUGINPARSER_H
#define CPL_ICONPLUGINPARSER_H

//////////////////////////////////////////////////////////////////////////
class cpl_IconPluginParser {

public:
    /** parse image from .plugin file */
    int Parse(const char * plugTreePath);

public:
    /** set icon manager */
    void SetIconManager(cpl_IconManager * iconManager) { this->m_iconManager = iconManager; }

    /** set icon-image manager */
    void SetIconImageManager(cpl_IconImageManager * iconImageManager) { this->m_iconImageManager = iconImageManager; }

public:
    /** set plugin tree proxy */
    void SetPluginTreeProxy(IPluginTree * pltreePorxy) { this->m_plgtreeProxy = pltreePorxy; }

    /** set lua script proxy */
    void SetLuaScriptProxy(ILuaScriptProxy * luascriptProxy) { this->m_luascriptProxy = luascriptProxy; }

public:
    //constructor
    cpl_IconPluginParser();

    //destructor
    virtual ~cpl_IconPluginParser();

protected:
    cpl_IconManager        * m_iconManager;        //icon manager
    cpl_IconImageManager   * m_iconImageManager;   //icon-image manager

private:
    IPluginTree           * m_plgtreeProxy;
    ILuaScriptProxy       * m_luascriptProxy;

private:
    std::string             m_Category;

private:
    //parse plugin
    int parse_plugin(const char * path);

private:
    //parse icon from .plugin file
    int parse_icons(IPluginCodon * codon);

    //parse image from .plugin file
    int parse_image(IPluginCodon * codon);

    //parse image package from .plugin file
    int parse_image_package(IPluginCodon * codon);

private:
    //create image
    cpl_Image * create_image(const char * imageId, IPluginCodon * codon, const char * category = NULL);

};

#endif //CPL_ICONPLUGINPARSER_H
