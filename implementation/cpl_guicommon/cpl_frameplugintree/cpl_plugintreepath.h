#ifndef CPL_PLUGINTREEPATH_H
#define CPL_PLUGINTREEPATH_H

class cpl_PluginTreePath : public IPluginTreePath, public cpl_PluginTreeNode {

public:
    /** create instance */
    static cpl_PluginTreePath * New();

public:
    /** name */
    virtual void  SetName(const char* name);
    virtual const char* GetName();

    /** path */
    virtual void  SetPath(const char* path);
    virtual const char* GetPath();

    /** user data */
    virtual void  SetUserData(const void* userdata);
    virtual const void* GetUserData();

    /** codon */
    virtual void  SetCodon(IPluginCodon* codon);
    virtual IPluginCodon* GetCodon();

    /**set parent widget. */
    virtual void SetParent(IPluginTreePath* parent);
    virtual IPluginTreePath* GetParent();

public:
    /** allocate. */
    virtual int Allocate(int sz, int ext);

    /** if is composite */
    virtual int IsComposite();

    /** insert node */
    virtual int InsertNextItem(IPluginTreeNode* node);
    
    /** remove node */
    virtual int RemoveItem(IPluginTreeNode* node);
    
    /** remove all node */
    virtual int RemoveAllItems();

    /** get number of node. */
    virtual int GetNumberOfItems();
    
    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestItems();

    /** get specific position plugin */
    virtual IPluginTreeNode* GetItem(int subID);

    /** get specific plugin by name*/
    virtual IPluginTreeNode* GetItem(char* subID);

    /** get specific plugin by codon*/
    virtual IPluginTreeNode* GetItem(IPluginCodon* subID);

public:    
    //constructor
    cpl_PluginTreePath();

    //constructor
    cpl_PluginTreePath(cpl_PluginTreePath* plugin);
    
    //destructor
    virtual ~cpl_PluginTreePath();

    /** operator += */
    cpl_PluginTreePath& operator+=(cpl_PluginTreeNode* node);

    /** operator -= */
    cpl_PluginTreePath& operator-=(cpl_PluginTreeNode* node);

    /** get specific position plugin */
    virtual cpl_PluginTreeNode* GetItemA(int subID);

    /** get specific plugin by name*/
    virtual cpl_PluginTreeNode* GetItemA(char* subID);

protected:        
    //inner structure
    struct _fbNodetem_s {
        cpl_PluginTreeNode* Item;
        int resourceId;
    };
     
    //resize array
    _fbNodetem_s* Reallocate(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_PluginTreeNode* node);

    //get number of nest action
    int GetNestSubItem(cpl_PluginTreePath* node);

    //protected variables
    _fbNodetem_s* Array;
    int Size;
    int MaxId;
    int Extend;
};

//-------------------------------------------------------------------------
inline cpl_PluginTreePath& cpl_PluginTreePath::operator+=(cpl_PluginTreeNode* node) {
    //@@preconditions
    assert(node != NULL);
    //@@end preconditions

    this->InsertNextItem(node);
    return *this;
}

//-------------------------------------------------------------------------
inline cpl_PluginTreePath& cpl_PluginTreePath::operator-=(cpl_PluginTreeNode* node) {
    //@@preconditions
    assert(node != NULL);
    //@@end preconditions

    this->RemoveItem(node);
    return *this;
}

//-------------------------------------------------------------------------
inline int cpl_PluginTreePath::IsComposite() {
    return 1;
}

//-------------------------------------------------------------------------
inline int cpl_PluginTreePath::GetNumberOfItems() {
    return this->MaxId + 1;
}

//-------------------------------------------------------------------------
inline IPluginTreeNode* cpl_PluginTreePath::GetItem(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfItems());
    assert(this->Array != NULL);
    //@@end preconditions
    
    return this->Array[pos].Item;    
}

#endif //CPL_PLUGINTREEPATH_H
