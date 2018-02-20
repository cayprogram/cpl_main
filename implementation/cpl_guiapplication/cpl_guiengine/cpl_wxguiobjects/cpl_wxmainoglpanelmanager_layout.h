#ifndef CPL_WXMAINOGLPANELMANAGERLAYOUT_H
#define CPL_WXMAINOGLPANELMANAGERLAYOUT_H

//-----------------------------------------------------------------------------
// macro definitions
//-----------------------------------------------------------------------------
//
#define OGL_LAYOUT_TYPE_ONE          0 
#define OGL_LAYOUT_TYPE_2HOR_SPLIT   1
#define OGL_LAYOUT_TYPE_2VER_SPLIT   2
#define OGL_LAYOUT_TYPE_3VER_RIGHT2  3
#define OGL_LAYOUT_TYPE_3VER_LEFT2   4
#define OGL_LAYOUT_TYPE_3HOR_TOP2    5
#define OGL_LAYOUT_TYPE_3HOR_BOTTOM2 6
#define OGL_LAYOUT_TYPE_FOUR         7

#define OGL_LAYOUT_MODE_NORMAL      0
#define OGL_LAYOUT_MODE_FULL        1

//-----------------------------------------------------------------------------
// class cpl_wxMainOGLPanelManagerLayout
//-----------------------------------------------------------------------------
//
class cpl_wxMainOGLPanelManagerLayout : public cpl_Object {

public:
    /** create function */
    static cpl_wxMainOGLPanelManagerLayout * New(cpl_wxMainOGLPanelManager* pOwner);

public:
    /** set layout type */
    int SetLayoutType(int type);

    /** set layout mode */
    int SetLayoutMode(int mode);

    /** get layout type */
    int GetLayoutType();

    /** get layout mode */
    int GetLayoutMode();

    /** switch layout mode */
    int SwitchLayoutMode();

    /** do layout */
    int DoLayout();

    /** set exchange mode */
    int SetExchangeMode(int mode);

    /** get exchange mode */
    int GetExchangeMode();

    /** do exchange */
    int DoExchange(int comp_src, int comp_target);

public:
    /** get implementation */
    ILayoutProxy* GetImplementation();

protected:
    cpl_wxMainOGLPanelManagerLayout(cpl_wxMainOGLPanelManager* pOwner);

    // Destructor
    virtual ~cpl_wxMainOGLPanelManagerLayout();

private:
    friend class cpl_wxMainOGLPanelManager;

    cpl_wxMainOGLPanelManager* Owner;  //owner.

    int LayoutType; //type.
    int LayoutMode; //layout mode.
    int ExchangeMode;
    
    class LayoutProxyImp;
    LayoutProxyImp* pLayoutProxy;

    //do layout
    void DoLayoutByNormalSize();
    void DoLayoutByFullSize();

    /** do exchange */
    int DoExchangeDirect(int comp_src, int comp_target);
};

#endif //CPL_WXMAINOGLPANELMANAGERLAYOUT_H
