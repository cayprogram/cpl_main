#ifndef CPL_IMAGEPLUGINPARSER_H
#define CPL_IMAGEPLUGINPARSER_H

//////////////////////////////////////////////////////////////////////////
class cpl_ImagePluginParser {
public:
    /** parse image from .plugin file */
    int Parse(const char * plugTreePath);

public:
    /** set image manager */
    void SetImageManager(cpl_ImageManager * imageManager) { this->m_imageManager = imageManager; }

public:
    /** set plugin tree proxy */
    void SetPluginTreeProxy(IPluginTree * pltreePorxy) { this->m_plgtreeProxy = pltreePorxy; }

    /** set lua script proxy */
    void SetLuaScriptProxy(ILuaScriptProxy * luascriptProxy) { this->m_luascriptProxy = luascriptProxy; }

public:
    //constructor
    cpl_ImagePluginParser();

    //destructor
    virtual ~cpl_ImagePluginParser();

protected:
    cpl_ImageManager  * m_imageManager;

private:
    IPluginTree      * m_plgtreeProxy;
    ILuaScriptProxy  * m_luascriptProxy;

private:
    //parse image from .plugin file
    int parse_plugin(const char * path);

private:
    //parse image from .plugin file
    int parse_image(IPluginCodon * codon);

    //parse image package from .plugin file
    int parse_image_package(IPluginCodon * codon);
};

#endif //CPL_IMAGEPLUGINPARSER_H
