#ifndef CPL_PLUGIN_H
#define CPL_PLUGIN_H

class cpl_Plugin : public IPlugin, public cpl_Object {

public:
    /** create instance */
    static cpl_Plugin * New();

public:
    /** name */
    void  SetName(const char* name);
    const char* GetName();

    /** author */
    void  SetAuthor(const char* name);
    const char* GetAuthor();
    
    /** copyright */
    void  SetCopyright(const char* name);
    const char* GetCopyright();

    /** url */
    void  SetUrl(const char* name);
    const char* GetUrl();

    /** description */
    void  SetDescription(const char* name);
    const char* GetDescription();

    /** version */
    void  SetVersion(const char* name);
    const char* GetVersion();

    /** xml name */
    void  SetXmlName(const char* name);
    const char* GetXmlName();

    /** set requires lib name */
    void SetRequireLibs(cpl_StringCollection* extensions);
    cpl_StringCollection* GetRequireLibs();

    /** set dynamic dll name */
    void SetDynamicFactories(cpl_StringCollection* extensions);
    cpl_StringCollection* GetDynamicFactories();

    /** set zscript lib name */
    void SetZScriptLibs(cpl_StringCollection* extensions);
    cpl_StringCollection* GetZScriptLibs();

    /** extensions */
    void SetExtensions(cpl_PluginExtensionCollection* extensions);
    cpl_PluginExtensionCollection* GetExtensions();

public:
    /**set parent widget. */
    virtual void SetParent(cpl_CompositePlugin* pcWidget);
    
    /**get composite Widget */
    virtual cpl_CompositePlugin* GetParent();
    
    /** is composite or not. */
    virtual int IsComposite() { return 0; }

public:
    struct _fbPlugin_s {
        char* name;
        char* author;
        char* copyright;
        char* url;
        char* description;
        char* version;
        char* xmlname;
        void* userdata;
        cpl_StringCollection* requires;
        cpl_StringCollection* dllnames;
        cpl_StringCollection* libnames;
        cpl_CompositePlugin* parent;
        cpl_PluginExtensionCollection* extensions;
    };
    
    //constructor. 1
    cpl_Plugin();
    
    //constructor. 2
    cpl_Plugin(cpl_CompositePlugin* parent);

    //destructor.
    virtual ~cpl_Plugin();

    //protected variables   
    _fbPlugin_s pluginData;
};

#endif //CPL_PLUGIN_H
