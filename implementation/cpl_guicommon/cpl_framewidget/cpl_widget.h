#ifndef CPL_WIDGET_H
#define CPL_WIDGET_H

/** dtkWidget class is abstract a widget item.*/

class cpl_Widget {

public:
    /**window operator: set/get text. */
    virtual void SetText(const char* text);
    virtual const char* GetText();

    /**window operator: set window position. */
    virtual void SetWindowPosition(int x, int y);

    /**window operator: set window size. */
    virtual void SetWindowSize(int w, int h);

    /**window operator: set window visible */
    virtual void SetWindowVisibility(int visibility);

    /**window operator: set window user data. */
    virtual void SetWindowUserData(void* usrData);

    /**window operator: set window position. */
    virtual void GetWindowPosition(int& x, int& y);

    /**window operator: get window size. */
    virtual void GetWindowSize(int& w, int& h);

    /**window operator: get window visible */
    virtual void GetWindowVisibility(int& visibility);

    /**window operator: get window user data. */
    virtual void GetWindowUserData(void*& usrData);

    /**window operator: get window user data. */
    virtual void* GetWindowUserData();

public:
	/**window operator: on size support */
    virtual void ResizeWindow(int x, int y, int w, int h);

    /**window operator: set parent widget. */
    virtual void SetParentWidget(cpl_WidgetComposite* parent);
    
    /**window operator: whether is composite widget or not. */
    virtual int IsComposite();
    
public:    
    /**window operator: get parent widget */
    virtual cpl_WidgetComposite* GetParentWidget();

    /**window operator: get top-level widget. */
    virtual cpl_WidgetComposite* GetRootWidget();

public:
    //inner structure.
    struct _fbWidget_s {
        int x;
        int y;
        int width;
        int height;
        int visible;
        char* text;        
        void* userdata;
        cpl_WidgetComposite* parent;
    };

    //constructor. 1
    cpl_Widget();
    
    //constructor. 2
    cpl_Widget(cpl_WidgetComposite* pCompositeWidget);

    //destructor.
    virtual ~cpl_Widget();

    //protected variables   
    _fbWidget_s winData;
};

#endif //CPL_WIDGET_H
