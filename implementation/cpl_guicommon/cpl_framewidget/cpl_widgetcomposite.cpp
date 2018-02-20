#include "cpl_widgetframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_WidgetComposite
//-----------------------------------------------------------------------------
//
int cpl_WidgetComposite::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].WidgetItem != NULL) {
                    delete this->Array[i].WidgetItem;
                    this->Array[i].WidgetItem = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbWidgetItem_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].WidgetItem = NULL;
             this->Array[i].resourceId = 0;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_WidgetComposite::InsertNextItem(cpl_Widget* Widget) {    
    //@@preconditions
    assert(Widget != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, Widget);
    return this->MaxId;
}

//-----------------------------------------------------------------------------
int cpl_WidgetComposite::RemoveItem(cpl_Widget* Widget) {
    //@@preconditions
    assert(Widget != NULL);
    //@@end preconditions

    int WidgetId = -1;
    for (int i = 0; i < this->MaxId; i++) {
        if (this->Array[i].WidgetItem == Widget) {
            WidgetId = i;
            break;
        }
    }
    assert(WidgetId != -1);

    //exchange position between lnId and MaxId, note: widget is not delete.
    if (WidgetId != this->MaxId) {
        this->Array[WidgetId] = this->Array[this->MaxId];
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-----------------------------------------------------------------------------
int cpl_WidgetComposite::RemoveAllItems(){
    for (int i = 0; i < this->MaxId; i++) {
        if (this->Array[i].WidgetItem != NULL) {
            delete this->Array[i].WidgetItem;
            this->Array[i].WidgetItem = NULL;
        }
    }
    this->MaxId = -1;
    return 1;
}

//-----------------------------------------------------------------------------
void cpl_WidgetComposite::InsertItem(int pos, cpl_Widget* Widget) {
    //@@preconditions
    assert(pos >= 0);
    assert(Widget != NULL);
    //@@end preconditions

    _fbWidgetItem_s * Widgets;

    if (pos >= this->Size) {
        this->Reallocate(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    Widgets = this->Array + pos;
    assert(Widgets != NULL);

    Widgets->WidgetItem = Widget;
    Widgets->resourceId = 0;

    //set as parent.
    Widgets->WidgetItem->SetParentWidget(this);

    return;
}
    
//-----------------------------------------------------------------------------
cpl_WidgetComposite::_fbWidgetItem_s* cpl_WidgetComposite::Reallocate(int sz) {
    //@@preconditions
    assert(sz > 0);
    //@@end preconditions

    int newSize = 0;

    if (sz >= this->Size) {
        newSize = this->Size + sz;
    }
    else {
        assert(0);
        newSize = sz;
    }

    cpl_WidgetComposite::_fbWidgetItem_s * newArray = new cpl_WidgetComposite::_fbWidgetItem_s[newSize];

    for (int j = 0; j < newSize; j++) {
        newArray[j].WidgetItem = NULL;
        newArray[j].resourceId = 0;
    }

    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].WidgetItem = this->Array[i].WidgetItem;
        newArray[i].resourceId = this->Array[i].resourceId;
    }
    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;

    return this->Array;
}

//-----------------------------------------------------------------------------
cpl_WidgetComposite::cpl_WidgetComposite() : cpl_Widget(NULL) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_WidgetComposite::cpl_WidgetComposite(cpl_WidgetComposite * pWidget) : cpl_Widget(pWidget)  {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-----------------------------------------------------------------------------
cpl_WidgetComposite::~cpl_WidgetComposite() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].WidgetItem != NULL) {
                delete this->Array[i].WidgetItem;
                this->Array[i].WidgetItem = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}
