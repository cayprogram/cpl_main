#ifndef CPL_ACTIONCOMPOSITE_H
#define CPL_ACTIONCOMPOSITE_H

class cpl_ActionComposite : public cpl_Action {
public:
    /** get number of sub actions*/
    virtual int GetNumberOfSubActions();
    
    /** get number of sub action (nested)*/
    virtual int GetNumberOfNestSubActions();

    /** if is composite */
    virtual int IsComposite();

    /** find specific item */
    virtual cpl_Action* FindSpecificItem(const char* name);

    /** find specific item */
    virtual cpl_Action* FindSpecificItem(int cmdId);

public:
    //[set operator]
    /** allocate. */
    virtual int Allocate(int sz, int ext);

    /** add Action*/
    virtual int InsertNextItem(cpl_Action* action);
    
    /** remove Action */
    virtual int RemoveItem(cpl_Action* action);
    
    /** remove all action */
    virtual int RemoveAllItems();

    /** put action at first */
    virtual int PutItemAtFirst(cpl_Action* action);

    /** is exist */
    virtual int IsExist(cpl_Action* action);

    /** operator += */
    cpl_ActionComposite& operator+=(cpl_Action* action);

    /** operator -= */
    cpl_ActionComposite& operator-=(cpl_Action* action);

    /** get specific action from id */
    virtual cpl_Action* GetAction(int pos);
    
public:    
    //constructor
    cpl_ActionComposite();

    //constructor
    cpl_ActionComposite(cpl_ActionComposite* pAction);
    
    //constructor. 3
    cpl_ActionComposite(const char* text, const char* shortcut, int enable, int type, int cmdid, void * userdata, cpl_ActionComposite* parent);

    //constructor. 3
    cpl_ActionComposite(const char* text, const char* stringid, const char* shortcut, int enable, int type, int cmdid, int checked, char* tooltip, const char * pixmap_name, const char* domain, void * userdata, cpl_ActionComposite* parent);
    
    //destructor
    virtual ~cpl_ActionComposite();

protected:        
    //friend class.
    friend class cpl_ActionCompositeProxy;    

    //inner structure
    struct _fbActionItem_s {
        cpl_Action* actionItem;
        int resourceId; //reserved.
    };
     
    //resize array
    _fbActionItem_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_Action* action);

    //get number of nest action
    int GetNestSubActions(cpl_ActionComposite* pAction);

    //get number of nest action
    cpl_Action* FindSpecificItemInNestSubActions(const char* name, cpl_ActionComposite* pAction);

    //get number of nest action
    cpl_Action* FindSpecificItemInNestSubActions(int id, cpl_ActionComposite* pAction);

    //protected variables
    _fbActionItem_s* Array;
    int Size;
    int MaxId;
    int Extend;
};

#endif //CPL_ACTIONCOMPOSITE_H
