#ifndef CPL_PLUGINMANAGER_H
#define CPL_PLUGINMANAGER_H

class cpl_PluginManager: public cpl_Object {

public:
    /** create instance */
    static cpl_PluginManager * New();

public:
    /** initialize */
    virtual int DoInitialization();

    /** cleanup */
    virtual int DoCleanup();
    
    /** parse */
    virtual int Parse(const char* path);

    /** get root path */
    virtual cpl_CompositePlugin* GetRootPath();

public:
    // constructor.
    cpl_PluginManager();

    // destructor
    virtual ~cpl_PluginManager();

    // protected varaibles.
    cpl_CompositePlugin* rootPluginPath;

    // parse plugin 
    int ParseInPath(cpl_CompositePlugin* plugins, const char* path);
    int ParsePlugin(cpl_CompositePlugin* plugins, const char* fname);
};

#endif //CPL_PLUGINMANAGER_H
