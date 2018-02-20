#ifndef CPL_PLUGINCOMPOSITE_H
#define CPL_PLUGINCOMPOSITE_H

/**
 * @stereotype container 
 */
class cpl_CompositePlugin : public cpl_Plugin {

public:
    /** create instance */
    static cpl_CompositePlugin * New();

public:
    /** allocate. */
    virtual int Allocate(int sz, int ext);

    /** if is composite */
    virtual int IsComposite();

    /** operator += */
    cpl_CompositePlugin& operator+=(cpl_Plugin* plugin);

    /** operator -= */
    cpl_CompositePlugin& operator-=(cpl_Plugin* plugin);

    /** insert Widget */
    virtual int InsertNextItem(cpl_Plugin* plugin);
    
    /** remove Widget */
    virtual int RemoveItem(cpl_Plugin* plugin);
    
    /** remove all Widget */
    virtual int RemoveAllItems();

    /** get number of plugins. */
    virtual int GetNumberOfPlugins();
    
    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPlugins();

    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPluginsRequireLib();

    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPluginsDLL();

    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestPluginsZScript();

    /** get specific position plugin */
    virtual cpl_Plugin* GetPlugin(int subID);

public:    
    //constructor
    cpl_CompositePlugin();

    //constructor
    cpl_CompositePlugin(cpl_CompositePlugin* plugin);
    
    //destructor
    virtual ~cpl_CompositePlugin();

protected:        
    //inner structure
    struct _fbPluginItem_s {
        cpl_Plugin* PluginItem;
        int resourceId;
    };
     
    //resize array
    _fbPluginItem_s* Reallocate(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_Plugin* plugin);

    //get number of nest action
    int GetNestSubItem(cpl_CompositePlugin* plugin);
    int GetNestSubItemDLL(cpl_CompositePlugin* plugin);
    int GetNestSubItemZScript(cpl_CompositePlugin* plugin);    
    int GetNestSubItemRequireLib(cpl_CompositePlugin* plugin);

    //protected variables
    _fbPluginItem_s* Array;
    int Size;
    int MaxId;
    int Extend;
};

//-------------------------------------------------------------------------
inline cpl_CompositePlugin& cpl_CompositePlugin::operator+=(cpl_Plugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    this->InsertNextItem(plugin);
    return *this;
}

//-------------------------------------------------------------------------
inline cpl_CompositePlugin& cpl_CompositePlugin::operator-=(cpl_Plugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    this->RemoveItem(plugin);
    return *this;
}

//-------------------------------------------------------------------------
inline int cpl_CompositePlugin::IsComposite() {
    return 1;
}

//-------------------------------------------------------------------------
inline int cpl_CompositePlugin::GetNumberOfPlugins() {
    return this->MaxId + 1;
}

//-------------------------------------------------------------------------
inline cpl_Plugin* cpl_CompositePlugin::GetPlugin(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfPlugins());
    assert(this->Array != NULL);
    //@@end preconditons
    
    return this->Array[pos].PluginItem;    
}

#endif //CPL_PLUGINCOMPOSITE_H
