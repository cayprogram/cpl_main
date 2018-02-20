#ifndef CPL_PLUGINTREEMAP_H
#define CPL_PLUGINTREEMAP_H

class cpl_PluginTreeMap : public cpl_Object {

public:
    /** create instance */
    static cpl_PluginTreeMap * New();

public:
    /** initialize */
    virtual int DoInitialization();

    /** cleanup */
    virtual int DoCleanup();
   
    /** get node in specific path */
    cpl_PluginTreePath* GetPath(const char* path);
    
    /** create path. */
    cpl_PluginTreePath* CreatePath(const char* path);

public:
    // constructor.
    cpl_PluginTreeMap();

    // destructor
    virtual ~cpl_PluginTreeMap();

    // protected varaibles.
    cpl_PluginTreePath* rootPath;

    //create path.
    cpl_PluginTreePath* CreatePath(cpl_PluginTreePath* path, const char* path_name);
};

#endif //CPL_PLUGINTREEMAP_H
