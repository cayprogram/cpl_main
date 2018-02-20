#ifndef CPL_PLUGINCODONCOLLECTION_H
#define CPL_PLUGINCODONCOLLECTION_H

class cpl_PluginCodonCollection: public cpl_Object {

public:
    /** create instance */
    static cpl_PluginCodonCollection * New();
    
public:
    /** allocate. */
    virtual int  Allocate(int sz, int ext);

    /** get size */
    virtual int  GetNumberOfItem();

    /** add item */
    virtual int  InsertNextItem(cpl_PluginCodon* extension);
    
    /** remove item */
    virtual int  RemoveItem(cpl_PluginCodon* extension);
    
    /** remove all */
    virtual int  RemoveAllItems();
    
    /** get next item */
    virtual int  GetNextItem(cpl_PluginCodon*& extension);

    /** initial traversal */
    virtual void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbCodon_s {
        cpl_PluginCodon* item;
    };
     
    //constructor.
    cpl_PluginCodonCollection();

    //destructor
    virtual ~cpl_PluginCodonCollection();

    //resize array
    _fbCodon_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_PluginCodon* extension);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbCodon_s* Array;
};

#endif //CPL_PLUGINCODONCOLLECTION_H
