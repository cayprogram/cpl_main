#include "cpl_wxguiobjectincludes.h"

//local includes.
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

//-----------------------------------------------------------------------------
static void MeasureStringSize(const char* text, wxFont& font, wxSize& size) {
    wxScreenDC dc;
    dc.SetFont(font);
    wxString tempString(text);
    wxCoord width, height;
    dc.GetTextExtent(tempString, &width, &height);
    size.x = width;
    size.y = height;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetStatusBarHeight() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);
    return sampleSize.y;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetToolBarHeight() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);
    return 57; //sampleSize.y*4/*3*/;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetToolBoxWidth() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);
    return sampleSize.y*3;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetTaskPanelWidth() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);
    return sampleSize.x;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetSystemPanelWidth() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMM", sampleSize);
    return sampleSize.x;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetSystemPanelHeight() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);
    return sampleSize.x;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetSessionPanelWidth() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);
    return sampleSize.x*2;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetSessionPanelHeight() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMM", sampleSize);
    return sampleSize.x;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetOutputPanelWidth() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMMMMMMMMMMMMMMMMMMMMMMMM", sampleSize);
    return sampleSize.x*2;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::GetOutputPanelHeight() {
    wxSize sampleSize;
    this->MeasureStringDisplaySize("MMMMM", sampleSize);
    return sampleSize.y*2;
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::MeasureStringDisplaySize(const char* string, wxSize& size) {
    //get default font.
    wxFont StaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

    //get sample text size.
    wxSize sampleSize;
    MeasureStringSize(string, StaticText1Font, size);
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::SetWindowTitle(const char* title) {
    //@@preconditions
    assert(this->mainFrameInfo != NULL);
    //@@end preconditions

    char* produceName = cpl_SystemConfig::Instance()->GetProperProductName();
    assert(produceName != NULL);

#ifndef _DEBUG
    if (title == NULL) {
        sprintf(this->windowTitle, "%s", produceName);
    }
    else {
        sprintf(this->windowTitle, "%s - %s", title, produceName);
    }
#else
    int activeIdx = this->mainFrameInfo->GetActiveGraphicWindowId();
    assert(activeIdx >= 0);

    const char* processType = NULL;
    this->mainFrameInfo->GetGraphicWindowFuncProcessType(activeIdx, processType);
    assert(processType);

    if (title == NULL) {
        sprintf(this->windowTitle, "[%s] %s", processType, produceName);
    }
    else {
        sprintf(this->windowTitle, "[%s] %s - %s", processType, title, produceName);
    }
#endif

    this->SetTitle(this->windowTitle);
}
