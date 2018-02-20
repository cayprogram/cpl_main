#ifndef CPL_PLUGINXMLREADER_H
#define CPL_PLUGINXMLREADER_H

class TiXmlElement;
class cpl_PluginXmlReader : public cpl_Object {

public:
    /** create instance */
    static cpl_PluginXmlReader * New();
    
    /** set plugin */
    virtual void SetPlugin(cpl_Plugin* Plugin);

    /** set filename */
    virtual void SetXmlSource(const char* name);

    /** parse */
    virtual int Parse();

public:
    //constructor.
    cpl_PluginXmlReader();

    //destructor
    virtual ~cpl_PluginXmlReader();

    //parse runtime and extension.
    void ParseRequire(TiXmlElement* element);
    void ParseRuntime(TiXmlElement* element);
    void ParseZScript(TiXmlElement* element);
    void ParseExtensions(TiXmlElement* element);
    void ParseRuntimeAndExtension(TiXmlElement* element);
    void ParseAssembly(TiXmlElement* element, cpl_StringCollection*& collection);
    void ParseCodonCollection(TiXmlElement* element, cpl_PluginExtension* extension);

    //protected variables.
    cpl_Plugin* Plugin;
    char* XmlSource;
};

#endif //CPL_PLUGINXMLREADER_H
