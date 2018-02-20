#ifndef CPL_PLUGINEXTENSIONCOLLECTION_H
#define CPL_PLUGINEXTENSIONCOLLECTION_H

class cpl_PluginExtensionCollection : public cpl_Object {

public:
    /** create instance */
    static cpl_PluginExtensionCollection * New();
    
public:
    /** allocate. */
    virtual int  Allocate(int sz, int ext);

    /** get size */
    virtual int  GetNumberOfItem();

    /** add item */
    virtual int  InsertNextItem(cpl_PluginExtension* extension);
    
    /** remove item */
    virtual int  RemoveItem(cpl_PluginExtension* extension);
    
    /** remove all */
    virtual int  RemoveAllItems();
    
    /** get next item */
    virtual int  GetNextItem(cpl_PluginExtension*& extension);

    /** initial traversal */
    virtual void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbExtension_s {
        cpl_PluginExtension* item;
    };
     
    //constructor.
    cpl_PluginExtensionCollection();

    //destructor
    virtual ~cpl_PluginExtensionCollection();

    //resize array
    _fbExtension_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_PluginExtension* extension);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbExtension_s* Array;
};

#endif //CPL_PLUGINEXTENSIONCOLLECTION_H
