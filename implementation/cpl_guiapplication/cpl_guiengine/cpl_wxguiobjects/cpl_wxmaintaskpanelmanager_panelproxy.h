#ifndef CPL_WXMAINTASKPANELMANAGER_PANEL_PROXY_H
#define CPL_WXMAINTASKPANELMANAGER_PANEL_PROXY_H

//-----------------------------------------------------------------------------
// class cpl_wxMainTaskPanelManager::PanelProxy
//-----------------------------------------------------------------------------
//
class cpl_wxMainTaskPanelManager::PanelProxy: public IPanelProxy {

public:
    /** operator: get number of panel. */
    virtual int   GetNumberOfPanels();
    
    /** operator: create panel */
    virtual int   CreatePanel();

    /** operator: set current panel */
    virtual int   SetCurrentPanel(int wid);
    
    /** operator: get the specific panel handler. */
    virtual void* GetPanelWindowHandler(int wid);

public:
    // Constructor.
    PanelProxy(cpl_wxMainTaskPanelManager* pOwner);

    // Destructor
    virtual ~PanelProxy();

    //member variables.
    cpl_wxMainTaskPanelManager* Owner;
};

#endif //CPL_WXMAINTASKPANELMANAGER_PANEL_PROXY_H
