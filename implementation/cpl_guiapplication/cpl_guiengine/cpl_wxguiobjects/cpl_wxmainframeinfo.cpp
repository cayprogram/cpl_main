#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxoglpanel.h"
#include "cpl_wxtaskpanel.h"
#include "cpl_wxmainoglpanelmanager.h"
#include "cpl_wxmaintaskpanelmanager.h"
#include "cpl_wxmainframeinfo.h"


//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowNumber() {
    return MAX_SUPPORT_WIN_NUM;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetActiveGraphicWindowId() {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->Owner->mainOGLPanelManager != NULL);
    //@@end preconditions

    int wid = -1, idx=-1;
    this->Owner->mainOGLPanelManager->GetActiveOGLWin(wid, idx);
    assert(idx != -1);
    return idx;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::SetActiveGraphicWindowId(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    assert(this->Owner->mainOGLPanelManager != NULL);
    //@@end preconditions

    //active ogl windows.
    this->Owner->mainOGLPanelManager->ActiveOGLWinByIndex(idx);

    //active attach panels.
    if (this->FrameInfo[idx].uTaskWinID >= 0) {
        int wid = -1, sub_idx = -1;
        this->Owner->mainTaskPanelManager->GetActiveTaskWin(wid, sub_idx);
        if (this->FrameInfo[idx].uTaskWinID != wid) {
            int _idx = this->Owner->mainTaskPanelManager->GetTaskWinIdx(this->FrameInfo[idx].uTaskWinID);
            assert(_idx >= 0 && _idx < MAX_SUPPORT_WIN_NUM);
            this->Owner->mainTaskPanelManager->ActiveTaskWinByIndex(_idx);
            this->Owner->mainTaskPanelManager->DoLayout();
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowHandle(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    assert(this->Owner->mainOGLPanelManager != NULL);
    //@@end preconditions

    return this->Owner->mainOGLPanelManager->GetOGLWinId(idx);
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowFuncProcess(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->FrameInfo[idx].uFuncProcessID;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::SetGraphicWindowFuncProcess(int idx, int fid) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    int old = this->FrameInfo[idx].uFuncProcessID;
    this->FrameInfo[idx].uFuncProcessID = fid;
    return old;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::IsGraphicWindowFuncWindowEnabled(int idx) {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowFuncWindow(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->FrameInfo[idx].uTaskWinID;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::SetGraphicWindowFuncWindow(int idx, int fid) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    int old = this->FrameInfo[idx].uTaskWinID;
    this->FrameInfo[idx].uTaskWinID = fid;
    return old;
}  

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowToolWindow(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->FrameInfo[idx].uToolWindowID;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::SetGraphicWindowToolWindow(int idx, int fid) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    int old = this->FrameInfo[idx].uToolWindowID;
    this->FrameInfo[idx].uToolWindowID = fid;
    return old;
} 

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowShortCutFuncWindow(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->FrameInfo[idx].uShortCutFuncWindowID;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::SetGraphicWindowShortCutFuncWindow(int idx, int fid) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    int old = this->FrameInfo[idx].uToolWindowID;
    this->FrameInfo[idx].uShortCutFuncWindowID = fid;
    return old;
}  

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowContextMenuWindow(int idx) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->FrameInfo[idx].uContextMenuWindowID;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::SetGraphicWindowContextMenuWindow(int idx, int fid) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    //@@end preconditions

    int old = this->FrameInfo[idx].uContextMenuWindowID;
    this->FrameInfo[idx].uContextMenuWindowID = fid;
    return old;
}
   
//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::SetGraphicWindowFuncProcessType(int idx, const char* type) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(type != NULL);
    assert(this->Owner != NULL);
    //@@end preconditions

    if (this->FrameInfo[idx].uFuncProcessType != NULL) {
        delete[] this->FrameInfo[idx].uFuncProcessType;
        this->FrameInfo[idx].uFuncProcessType = NULL;
    }
    if (type == NULL) {
        return -1;
    }

    //copy
    size_t len = strlen(type);
    this->FrameInfo[idx].uFuncProcessType = new char[len+1];
    assert(this->FrameInfo[idx].uFuncProcessType != NULL);
    strcpy(this->FrameInfo[idx].uFuncProcessType, type);

    return idx;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::GetGraphicWindowFuncProcessType(int idx, const char*& type) {
    //@@preconditions
    assert(idx >= 0 && idx < MAX_SUPPORT_WIN_NUM);
    assert(this->Owner != NULL);
    assert(type == NULL);
    //@@end preconditions

    type = this->FrameInfo[idx].uFuncProcessType;
    return idx;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::ExchangeGraphicWindow(int source, int target) {
    //@@preconditions
    assert(source >= 0);
    assert(target >= 0);
    assert(this->Owner != NULL);
    //@@end preconditions

    _fbFrameInfo copy;
    this->InitFrameInfo(&copy);
    this->CopyFrameInfo(&this->FrameInfo[target], &copy);
    this->CopyFrameInfo(&this->FrameInfo[source], &this->FrameInfo[target]);
    this->CopyFrameInfo(&copy, &this->FrameInfo[source]);
    this->CleanFrameInfo(&copy);

    //switch graphic window.
    this->Owner->mainOGLPanelManager->DoExchangeOGLWin(source, target);
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrameInfo::CopyFrameInfo(_fbFrameInfo* src, _fbFrameInfo* target) {
    //@@preconditions
    assert(target != NULL);
    //@@end preconditions

    this->CleanFrameInfo(target);

    //assign
    target->uOGLWinID             = src->uOGLWinID;
    target->uTaskWinID            = src->uTaskWinID;
    target->uToolWindowID         = src->uToolWindowID;
    target->uShortCutFuncWindowID = src->uShortCutFuncWindowID;
    target->uContextMenuWindowID  = src->uContextMenuWindowID;
    target->uFuncProcessID        = src->uFuncProcessID;

    if (src->uFuncProcessType != NULL) {
        char * type = new char[strlen(src->uFuncProcessType)+1];    
        strcpy(type, src->uFuncProcessType);
        target->uFuncProcessType = type;
    }
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrameInfo::Create() {
    //@@preconditions
    assert(this->Owner->mainOGLPanelManager != NULL);
    assert(this->Owner->mainTaskPanelManager != NULL);
    //@@end preconditions

    for (int i = 0; i < MAX_SUPPORT_WIN_NUM; i++) {
        this->FrameInfo[i].uOGLWinID = this->Owner->mainOGLPanelManager->GetOGLWinId(i);
        this->FrameInfo[i].uTaskWinID = this->Owner->mainTaskPanelManager->GetTaskWinId(i);
        this->FrameInfo[i].uToolWindowID = -1;
        this->FrameInfo[i].uShortCutFuncWindowID = -1;
        this->FrameInfo[i].uContextMenuWindowID = -1;
        this->FrameInfo[i].uFuncProcessID = -1;
        this->FrameInfo[i].uFuncProcessType = NULL;
    }
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrameInfo::InitFrameInfo(_fbFrameInfo* item) {
    //@@preconditions
    assert(item != NULL);
    //@@end preconditions

    item->uOGLWinID             = -1;
    item->uTaskWinID            = -1;
    item->uToolWindowID         = -1;
    item->uShortCutFuncWindowID = -1;
    item->uContextMenuWindowID  = -1;
    item->uFuncProcessID        = -1;
    item->uFuncProcessType      = NULL;
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrameInfo::CleanFrameInfo(_fbFrameInfo* item) {
    //@@preconditions
    assert(item != NULL);
    //@@end preconditions

    item->uOGLWinID             = -1;
    item->uTaskWinID            = -1;
    item->uToolWindowID         = -1;
    item->uShortCutFuncWindowID = -1;
    item->uContextMenuWindowID  = -1;
    item->uFuncProcessID        = -1;

    //..
    if (item->uFuncProcessType != NULL) { 
        delete[] item->uFuncProcessType;
        item->uFuncProcessType = NULL;
    }
}

//-----------------------------------------------------------------------------
cpl_wxMainFrameInfo::cpl_wxMainFrameInfo(cpl_wxMainFrame* pOwner): Owner(pOwner) {
    for (int i = 0; i < MAX_SUPPORT_WIN_NUM; i++) {
        this->InitFrameInfo(&this->FrameInfo[i]);
    }
}

//-----------------------------------------------------------------------------
cpl_wxMainFrameInfo::~cpl_wxMainFrameInfo() {
    for (int i = 0; i < MAX_SUPPORT_WIN_NUM; i++) {
        this->CleanFrameInfo(&this->FrameInfo[i]);     
    }
}
