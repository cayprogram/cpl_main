#include "cpl_wxguiobjectincludes.h"

//local includes
#include "cpl_wxworker.h"
#include "cpl_wxoglpanel.h"
#include "cpl_wxtaskpanel.h"
#include "cpl_wxmainmenubar.h"
#include "cpl_wxmaintoolbar.h"
#include "cpl_wxmaintoolbarnormal.h"
#include "cpl_wxmaintoolbox.h"
#include "cpl_wxmainstatusbar.h"
#include "cpl_wxmainoglpanelmanager.h"
#include "cpl_wxmaintaskpanelmanager.h"
#include "cpl_wxmainframeinfo.h"
#include "cpl_wxmainsystempanel.h"
#include "cpl_wxmainsessionpanel.h"
#include "cpl_wxmaincontextmenu.h"

//update GUI event.
//-----------------------------------------------------------------------------
void cpl_wxMainFrame::UpdateGUI() {
    //@@preconditions
    assert(this->mainFrameInfo != NULL);
    //@@end preconditions

    int activeIdx = this->mainFrameInfo->GetActiveGraphicWindowId();
    assert(activeIdx >= 0);

    const char* processType = NULL;
    this->mainFrameInfo->GetGraphicWindowFuncProcessType(activeIdx, processType);
    assert(processType != NULL);

    this->PostGUIEvent(processType);
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::UpdateGUIDirect(const char* hint) {
    //@@preconditions
    assert(this->mainMenubar != NULL);
    assert(this->mainContextMenu != NULL);
    //@@end preconditions

    this->mainMenubar->Update(hint);
    this->mainContextMenu->Update(hint);
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::OnCustomEvent(wxCommandEvent& event) {
    wxString text = event.GetString();  
    printf("my event recieved: %s\n", text.mb_str());
    this->UpdateGUIDirect(text.mb_str());
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::OnThreadUpdate(wxThreadEvent& event) {  
    //@@preconditions
    assert(this->mainStatusbar != NULL);
    //@@end preconditions

    int value = event.GetInt();
    printf("cpl_wxMainFrame::OnThreadUpdate %d\n", value);
    this->mainStatusbar->SetProgressValue((float)value);
} 

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::OnThreadEnter(wxThreadEvent& event) {  
    //@@preconditions
    assert(this->mainStatusbar != NULL);
    //@@end preconditions

    //disable gui state.
    IPluginTreePath* treePath = this->GetPluginTree()->GetTreePath("/Workbench/Interfaces/Services/RuntimeContext");
    if (treePath != NULL) {
        IRuntimeContextProxy* runtime = (IRuntimeContextProxy*)treePath->GetUserData();
        assert(runtime != NULL);
        runtime->SetBusyFlagOn();
    }
    this->mainStatusbar->SetProgressStatus(1);

    //notify client callback.
    this->PWorker->SetExecutingFlag(1);
    this->PWorker->ExecPre();
} 

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::OnThreadLeave(wxThreadEvent& event) {  
    //@@preconditions
    assert(this->mainStatusbar != NULL);
    //@@end preconditions

    //notify client callback
    this->PWorker->ExecPost();
    this->PWorker->SetFunc(0, 0, 0, 0);
    this->PWorker->SetExecutingFlag(0);

    //restore GUI state.
    IPluginTreePath* treePath = this->GetPluginTree()->GetTreePath("/Workbench/Interfaces/Services/RuntimeContext");
    if (treePath != NULL) {
        IRuntimeContextProxy* runtime = (IRuntimeContextProxy*)treePath->GetUserData();
        assert(runtime != NULL);
        runtime->SetBusyFlagOff();
    }
    this->mainStatusbar->SetProgressStatus(0);
} 
