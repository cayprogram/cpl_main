#ifndef PANELPROXYINTERFACE_H
#define PANELPROXYINTERFACE_H

class IPanelProxy {

public:
    /** operator: get number of panel. */
    virtual int   GetNumberOfPanels() = 0;
    
    /** operator: create panel */
    virtual int   CreatePanel() = 0;

    /** operator: set current panel */
    virtual int   SetCurrentPanel(int wid) = 0;
    
    /** operator: get the specific panel handler. */
    virtual void* GetPanelWindowHandler(int wid) = 0;
};

#endif //PANELPROXYINTERFACE_H
