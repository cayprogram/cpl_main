#ifndef CPL_PLUGINCODON_H
#define CPL_PLUGINCODON_H

class TiXmlElement;
class cpl_PluginCodon : public IPluginCodon, public cpl_Object {

public:
    /** create instance */
    static cpl_PluginCodon * New();

public:
    /** name */
    void  SetName(const char* name);
    const char* GetName();

    /** id */
    void  SetId(const char* id);
    const char* GetId();

    /** condition */
    void  SetCondition(const char* condition);
    const char* GetCondition();

    /** attribute */
    void  SetAttribute(const char* key, const char* val);
    const char* GetAttribute(const char* key);

    /** user data */
    void  SetUserData(void* userdata);
    void* GetUserData();

    /** value */
    void  SetXmlValue(const char* value);
    const char* GetXmlValue();
   
    /** plugin */
    void  SetPlugin(IPlugin* value);
    IPlugin* GetPlugin();

public:
    struct _fbCodon_s {
        char* id;
        char* name;
        char* condition;
        char* xmlvalue;
        void* userdata;
        cpl_HashTableStringOneKey* attributes;
        cpl_Plugin* plugin;
    };
    
    //constructor. 1
    cpl_PluginCodon();
    
    //destructor.
    virtual ~cpl_PluginCodon();

    //protected variables   
    _fbCodon_s codonData;
};

#endif //CPL_PLUGINCODON_H
