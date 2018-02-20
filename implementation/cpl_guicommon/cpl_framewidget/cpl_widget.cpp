#include "cpl_widgetframeincludes.h"

//-----------------------------------------------------------------------------
//global static data.
static cpl_Widget::_fbWidget_s WinData = {0, 0, 0, 0, 0, NULL, NULL, NULL};

//-----------------------------------------------------------------------------
// class cpl_Widget
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void cpl_Widget::SetText(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions
    
    if (this->winData.text != NULL) {
        delete[] this->winData.text;
        this->winData.text = NULL;
    }
    size_t len = strlen(text);
    this->winData.text = new char[len+1];
    assert(this->winData.text != NULL);
    strcpy(this->winData.text, text);
    this->winData.text[len] ='\0';
}

//-----------------------------------------------------------------------------
const char* cpl_Widget::GetText() {
    //@@postconditions
    assert(this->winData.text != NULL);
    //@@end postconditions
    
    return this->winData.text;
}

//-----------------------------------------------------------------------------
void cpl_Widget::SetWindowPosition(int x, int y) {
    this->winData.x = x;
    this->winData.y = y;
}

//-----------------------------------------------------------------------------
void cpl_Widget::SetWindowSize(int w, int h) {
    this->winData.width  = w;
    this->winData.height = h;
}

//-----------------------------------------------------------------------------
void cpl_Widget::SetWindowUserData(void* usrData) {
    this->winData.userdata = usrData;
}
 
//-----------------------------------------------------------------------------
void cpl_Widget::GetWindowPosition(int& x, int& y) {
    x = this->winData.x;
    y = this->winData.y;
}

//-----------------------------------------------------------------------------
void cpl_Widget::GetWindowSize(int& w, int& h) {
    w = this->winData.width;
    h = this->winData.height;
}

//-----------------------------------------------------------------------------
void cpl_Widget::GetWindowUserData(void*& usrData) {
    //@@postconditions
    assert(usrData == NULL);
    //@@end postconditions

    usrData = this->winData.userdata;
}
   
//-----------------------------------------------------------------------------
void* cpl_Widget::GetWindowUserData() {
    return this->winData.userdata;
}
    
//-----------------------------------------------------------------------------
void cpl_Widget::SetParentWidget(cpl_WidgetComposite* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    this->winData.parent = parent;
}
    
//-----------------------------------------------------------------------------
cpl_WidgetComposite* cpl_Widget::GetParentWidget() {
    return this->winData.parent;
}

//-----------------------------------------------------------------------------
cpl_WidgetComposite* cpl_Widget::GetRootWidget() {
    cpl_WidgetComposite* tmpWidget = NULL;
    while(1) {
        cpl_WidgetComposite* parentWidget = tmpWidget->GetParentWidget();
        if (parentWidget == NULL) {
            break;
        }
        else {
            tmpWidget = parentWidget;
        }
    }
    return tmpWidget;
}

//-----------------------------------------------------------------------------
void cpl_Widget::SetWindowVisibility(int visibility) {
    //@@preconditions
    assert(visibility == 0 || visibility == 1);
    //@@end preconditions

    this->winData.visible = visibility;
}

//-----------------------------------------------------------------------------
void cpl_Widget::GetWindowVisibility(int& visibility) {
    //@@postconditions
    assert(this->winData.visible == 0 || this->winData.visible == 1) ;
    //@@end postconditions

    visibility = this->winData.visible;
}

//-----------------------------------------------------------------------------
int cpl_Widget::IsComposite() {
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_Widget::ResizeWindow(int x, int y, int w, int h) {
    this->winData.x = x;
    this->winData.y = y;
    this->winData.width  = w;
    this->winData.height = h;
}

//-----------------------------------------------------------------------------
cpl_Widget::cpl_Widget() {
    this->winData = WinData;
}

//-----------------------------------------------------------------------------
cpl_Widget::cpl_Widget(cpl_WidgetComposite* pWidget) {
    this->winData        = WinData;
    this->winData.parent = pWidget;
}

//-----------------------------------------------------------------------------
cpl_Widget::~cpl_Widget() {
    if (this->winData.text) {
        delete[] this->winData.text;
        this->winData.text = NULL;
    }
}
