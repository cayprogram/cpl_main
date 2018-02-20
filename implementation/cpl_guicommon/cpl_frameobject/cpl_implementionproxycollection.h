#ifndef CPL_IMPLEMENTATIONPROXYCOLLECTION_H
#define CPL_IMPLEMENTATIONPROXYCOLLECTION_H

class cpl_ImplementationProxyCollection : public cpl_Object {
public:
    /** create instance */
    static cpl_ImplementationProxyCollection * New();
    
public:
    /** allocate. */
    int  Allocate(int sz, int ext);

    /** get size */
    int  GetNumberOfItem();

    /** add item */
    int  InsertNextItem(cpl_ImplementationProxy& proxy);
    
    /** remove item */
    int  RemoveItem(cpl_ImplementationProxy& proxy);
    
    /** remove all */
    int  RemoveAllItems();
    
    /** get next item */
    int  GetNextItem(cpl_ImplementationProxy& proxy);

    /** initial traversal */
    void InitTraversal() { this->TraversalPos = 0; }

public:
    //inner structure
    struct _fbImplementationProxy_s {
        cpl_ImplementationProxy proxy;
    };
     
    //constructor.
    cpl_ImplementationProxyCollection();

    //destructor
    virtual ~cpl_ImplementationProxyCollection();

    //resize array
    _fbImplementationProxy_s* Resize(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_ImplementationProxy& proxy);

    //protected variables
    int Size;
    int MaxId;
    int Extend;
    int TraversalPos;
    _fbImplementationProxy_s* Array;
};

#endif //CPL_IMPLEMENTATIONPROXYCOLLECTION_H
