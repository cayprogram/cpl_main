#ifndef CPL_PLUGINTREE_H
#define CPL_PLUGINTREE_H

class ILuaScriptProxy;
class cpl_Creator;
class cpl_PluginTree : public cpl_Object, public IPluginTree {
public:
    /** create instance */
    static cpl_PluginTree * New();

public:
    /** parse */
    virtual int Parse(const char* path);

    /** set lua VM */
    virtual int SetLuaState(void* luaState);

    /** load lua script files */
    virtual int LoadLuaScriptPackage();

    /** load lua runtime dlls */
    virtual int LoadLuaRuntimePackage();

    /** load class creator runtime dlls */
    virtual int LoadClassCreatorRuntimePackage(cpl_Creator* pCreator);

public:
    /** get node in specific path */
    virtual IPluginTreePath* GetTreePath(const char* path);

    /** create path. */
    virtual IPluginTreePath* CreateTreePath(const char* path);

public:
    //inner structure.
    struct _fbPluginDLL_s {
        int libCount;
        int libSize;
        void** libHandlers;
    };

    //inner structure.
    struct _fbPluginZScript_s {
        int libCount;
        int libSize;
        char** libHandlers;
    };

    //constructor.
    cpl_PluginTree();

    //destructor
    virtual ~cpl_PluginTree();

    //protected variables.
    void* pLuaState;
    _fbPluginDLL_s DLLRequired;
    _fbPluginDLL_s DLLResource;
    _fbPluginZScript_s ZScriptResource;

    //plugin manager.
    cpl_PluginManager* PluginManager;
    cpl_PluginTreeMap* PathManager;

    //load dynamic factories.
    void LoadLibRequired();
    void LoadDllRuntimes();
    void UnLoadDynamicFactories();
    void LoadZScriptPackage();
    void AssemblyExtensions();

    //get number of nest action
    void GetNestSubItemLibRequired(cpl_CompositePlugin* plugin);
    void GetNestSubItemDllRuntimes(cpl_CompositePlugin* plugin);
    void GetNestSubItemScriptName(cpl_CompositePlugin* plugin);
    void GetNestSubItemExtensions(cpl_CompositePlugin* plugin);

    //link.
    void AddExtensionIntoPath(cpl_PluginExtension* extension, cpl_PluginTreePath* path, cpl_Plugin* plugin);
};

#endif //CPL_PLUGINTREE_H
