#ifndef CPL_PLUGINEXTENSION_H
#define CPL_PLUGINEXTENSION_H

class cpl_PluginExtension: public cpl_Object {

public:
    /** create instance */
    static cpl_PluginExtension * New();

public:
    /** path */
    void SetPath(const char* name);
    const char* GetPath();
   
    /** codons */
    void SetCodons(cpl_PluginCodonCollection* Codons);
    cpl_PluginCodonCollection* GetCodons();

public:
    struct _fbExtension_s {
        char* path;
        cpl_PluginCodonCollection* codons;
    };
    
    //constructor. 1
    cpl_PluginExtension();
    
    //destructor.
    virtual ~cpl_PluginExtension();

    //protected variables   
    _fbExtension_s extensionData;
};

#endif //CPL_PLUGINEXTENSION_H
