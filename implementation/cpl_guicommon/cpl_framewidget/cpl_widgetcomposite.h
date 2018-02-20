#ifndef CPL_WIDGETCOMPOSITE_H
#define CPL_WIDGETCOMPOSITE_H

class cpl_WidgetComposite : public cpl_Widget {

public:
    /** operator: allocate widget slot according to initial size. */
    virtual int Allocate(int sz, int ext);

    /** operator: if is composite (override)*/
    virtual int IsComposite();

    /** operator: += */
	cpl_WidgetComposite& operator+=(cpl_Widget* widget);

    /** operator: -= */
	cpl_WidgetComposite& operator-=(cpl_Widget* widget);

    /** operator: insert the specific widget.*/
    virtual int InsertNextItem(cpl_Widget* widget);
    
    /** operator: remove the specific widget.*/
    virtual int RemoveItem(cpl_Widget* widget);
    
    /** operator: remove all widget */
    virtual int RemoveAllItems();

    /** operator: get number of sub widgets. */
    virtual int GetNumberOfSubWidgets();
    
    /** operator: get the specific widget by subID. */
    virtual cpl_Widget* GetWidget(int subID);
    
public:    
    //constructor
    cpl_WidgetComposite();

    //constructor
    cpl_WidgetComposite(cpl_WidgetComposite* pWidget);
    
    //destructor
    virtual ~cpl_WidgetComposite();

protected:        
    //inner structure
    struct _fbWidgetItem_s {
        cpl_Widget* WidgetItem;
        int resourceId;
    };
     
    //resize array
    _fbWidgetItem_s* Reallocate(int size);

    //insert at the specific position.
    void InsertItem(int pos, cpl_Widget* Widget);

    //protected variables
    _fbWidgetItem_s* Array;
    int Size;
    int MaxId;
    int Extend;
};

//-----------------------------------------------------------------------------
inline cpl_WidgetComposite& cpl_WidgetComposite::operator+=(cpl_Widget* widget) {
    //@@preconditions
    assert(widget != NULL);
    //@@end preconditions

    this->InsertNextItem(widget);
    return *this;
}

//-----------------------------------------------------------------------------
inline cpl_WidgetComposite& cpl_WidgetComposite::operator-=(cpl_Widget* widget) {
    //@@preconditions
    assert(widget != NULL);
    //@@end preconditions

    this->RemoveItem(widget);
    return *this;
}

//-----------------------------------------------------------------------------
inline int cpl_WidgetComposite::IsComposite() {
    return 1;
}

//-----------------------------------------------------------------------------
inline int cpl_WidgetComposite::GetNumberOfSubWidgets() {
    return this->MaxId + 1;
}
    
//-----------------------------------------------------------------------------
inline cpl_Widget* cpl_WidgetComposite::GetWidget(int pos) {
    //@@preconditions
    assert(pos >= 0);
    assert(pos < this->GetNumberOfSubWidgets());
    assert(this->Array != NULL);
    //@@end preconditions
    
    return this->Array[pos].WidgetItem;    
}

#endif //CPL_WIDGETCOMPOSITE_H
