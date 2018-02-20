#ifndef CPL_WXOGLPANEL_H
#define CPL_WXOGLPANEL_H

//-----------------------------------------------------------------------------
//class cpl_wxOGLPanelEventHandler
//-----------------------------------------------------------------------------
//
class cpl_wxOGLPanelEventHandler: public wxEvtHandler {
public:
	cpl_wxOGLPanelEventHandler(cpl_wxOGLPanel *Panel);
	virtual ~cpl_wxOGLPanelEventHandler();

protected:
	DECLARE_EVENT_TABLE()
	void OnLeftButtonClick(wxMouseEvent &Event);
	void OnLeftButtonDBClick(wxMouseEvent &Event);
	cpl_wxOGLPanel *Panel;
};

//-----------------------------------------------------------------------------
//class cpl_wxOGLPanel
//-----------------------------------------------------------------------------
//
class cpl_wxOGLPanel : public wxPanel {
public:
    /** do initialization */
    int Initialize();

    /** do cleanup */
    int Cleanup();

    /** get winId */
    int GetWinId();

public:
    /** active window */
    void DoActive();
    
    /** deactivate window */
    void DoDeactive();
    
    /** is active window */
    int  IsActive() {return this->OGLInfo.isActived;}

    /** set focus */
    void SetOGLFocus();

public:
    // Constructor.
    cpl_wxOGLPanel(cpl_wxMainOGLPanelManager* pOwner, wxPanel* parent);

    // Destructor
    virtual ~cpl_wxOGLPanel();

private:
    friend class cpl_wxOGLPanelEventHandler;

    //inner structure.
    struct _fbOGLInfo_s {
        int winId;   
        int isActived;
        int bkColor[3];
        wxGLCanvas* glWin;
    };

    //owner.
    cpl_wxMainOGLPanelManager* Owner;
    cpl_wxOGLPanelEventHandler* EventHandler;

    //wx controls
    _fbOGLInfo_s OGLInfo;

    // create ogl window
    void CreateOGLWin(_fbOGLInfo_s& pInfo);

    //event handler
    void OnContextMenuHandler(int x, int y);
    void OnLeftButtonClick(wxMouseEvent &Event);
    void OnLeftButtonDBClick(wxMouseEvent & event);

    //mouse wheel forward callback 
    static void mouseWheelForwardCallback(void* callData, void* clientData);
    static void mouseWheelBackwardCallback(void* callData, void* clientData);
    static void OnContextMenuCallback(void* callData, void* clientData);
};

#endif //CPL_WXOGLPANEL_H
