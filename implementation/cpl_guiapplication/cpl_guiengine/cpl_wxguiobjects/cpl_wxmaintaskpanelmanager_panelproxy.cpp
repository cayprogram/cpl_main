#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxtaskpanel.h"
#include "cpl_wxmaintaskpanelmanager.h"
#include "cpl_wxmaintaskpanelmanager_panelproxy.h"

//-----------------------------------------------------------------------------
// class cpl_wxMainTaskPanelManager::PanelProxy
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int cpl_wxMainTaskPanelManager::PanelProxy::GetNumberOfPanels() {
    return MAX_SUPPORT_WIN_NUM;
}

//-----------------------------------------------------------------------------
int cpl_wxMainTaskPanelManager::PanelProxy::CreatePanel() {
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxMainTaskPanelManager::PanelProxy::SetCurrentPanel(int wID) {
    return 0;
}

//-----------------------------------------------------------------------------
void* cpl_wxMainTaskPanelManager::PanelProxy::GetPanelWindowHandler(int wID) {
    //@@preonditions
    assert(wID >= 0);
    assert(this->Owner != NULL);
    //@@end preconditions

    cpl_wxTaskPanel* panel = NULL;
    this->Owner->GetTaskPanel(wID, panel);
    assert(panel != NULL);

    return panel->GetRawWin();    
}

//-----------------------------------------------------------------------------
cpl_wxMainTaskPanelManager::PanelProxy::PanelProxy(cpl_wxMainTaskPanelManager* pOwner): Owner(pOwner) {
}

//-----------------------------------------------------------------------------
cpl_wxMainTaskPanelManager::PanelProxy::~PanelProxy() {
}
