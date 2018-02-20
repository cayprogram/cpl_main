#ifndef CPL_CONTROLLERSET_H
#define CPL_CONTROLLERSET_H

class cpl_ControllerSet : public cpl_Object {
    
public:
    /** new instance*/
    static cpl_ControllerSet* New();

public:
    /** allocate. */
    virtual int Allocate(int sz, int ext);

    /** insert new item */
    virtual int InsertNextItem(cpl_Controller* item);
    
    /** remove the specific item */
    virtual int RemoveItem(cpl_Controller* item);
    
    /** remove all items*/
    virtual int RemoveAllItems();

    /** do clean up */
    virtual void DoCleanup();
    
protected:     
    //inner structure
    struct _fbControllerItem_s {
        cpl_Controller* controlItem;
        int resourceId; //reserved.
    };

    //resize array
    _fbControllerItem_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_Controller* item);

    //constructor.
    cpl_ControllerSet();

    //destructor
    virtual ~cpl_ControllerSet();

protected:    
    //protected variables
    _fbControllerItem_s* Array;
    int Size;
    int MaxId;
    int Extend;
};

#endif //CPL_CONTROLLERSET_H
