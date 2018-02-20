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
#include "cpl_wxmainoutputpanel.h"
#include "cpl_wxmaincontextmenu.h"

//-----------------------------------------------------------------------------
IPanelProxy* cpl_wxMainFrame::GetTaskPanelProxy() {
    //@@preconditions
    assert(this->mainTaskPanelManager != NULL);
    //@@end preconditions

    return this->mainTaskPanelManager->GetTaskPanelProxy();
}

//-----------------------------------------------------------------------------
IOutputStatusInfo* cpl_wxMainFrame::GetOutputStatusInfoHandler() {
    //@@preconditions
    assert(this->mainStatusbar != NULL);
    //@@end preconditions

    return this->mainStatusbar->GetOutputStatusInfoHandler(); 
}

//-----------------------------------------------------------------------------
IOutputMessage* cpl_wxMainFrame::GetOutputMessage() {
    //@@preconditions
    assert(this->mainOutput != NULL);
    //@@end preconditions

    return this->mainOutput->GetOutputMessageImp();
}

//-----------------------------------------------------------------------------
IGraphicWindowInfo* cpl_wxMainFrame::GetGraphicWindowInfoHandler() {
    //@@preconditions
    assert(this->mainFrameInfo != NULL);
    //@@end preconditions

    return this->mainFrameInfo;
}

//-----------------------------------------------------------------------------
IPluginTree* cpl_wxMainFrame::GetPluginTree() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetPluginTree();
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_wxMainFrame::GetIconProxy() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetIconProxy();
}

//-----------------------------------------------------------------------------
IResImageProxy* cpl_wxMainFrame::GetImageProxy() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetImageProxy();
}

//-----------------------------------------------------------------------------
ILayoutProxy* cpl_wxMainFrame::GetLayoutProxyImp() {
    //@@preconditions
    assert(this->mainOGLPanelManager != NULL);
    //@@end preconditions

    return this->mainOGLPanelManager->GetLayoutProxyImp();
}

//-----------------------------------------------------------------------------
IThreadFunc* cpl_wxMainFrame::GetThreadFunc() {
    //@@preconditions
    assert(this->PWorker != NULL);
    //@@end preconditions

    return this->PWorker;
}

//-----------------------------------------------------------------------------
void* cpl_wxMainFrame::GetSystemWindowRawHandler() {
    //@@preconditions
    assert(this->mainSystemPanel != NULL);
    //@@end preconditions

    return this->mainSystemPanel->GetPanel();
}

//-----------------------------------------------------------------------------
void* cpl_wxMainFrame::GetSessionWindowRawHandler() {
    //@@preconditions
    assert(this->mainSessionPanel != NULL);
    //@@end preconditions

    return this->mainSessionPanel->GetPanel();
}

//-----------------------------------------------------------------------------
wxMenu* cpl_wxMainFrame::GetContextMenu() {
    //@@preconditions
    assert(this->mainContextMenu != NULL);
    //@@end preconditions

    return this->mainContextMenu->GetMenu();
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::GetMainScriptHandler(cpl_Action*& handler) {
    //@@preconditions
    assert(handler == NULL);
    assert(this->Owner != NULL);
    //@@end preconditions

    this->Owner->Owner->GetMainScripHandler(handler);
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::ExecGraphicEngineIdleCallback() {
//#ifdef _DEBUG
    static int counter = 0;
    printf("graphic engine idle callback recieved: %d\n", counter);
    counter++;
//#endif
    ::wxYield();

    //TODO: return your graphics engine idel callback status
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxMainFrame::ExchangeGraphicWindow(int source, int target) {
    //@@preconditions
    assert(source >= 0);
    assert(target >= 0);
    assert(this->mainFrameInfo != NULL);
    //@@end preconditions

    return this->mainFrameInfo->ExchangeGraphicWindow(source, target);
}

//-----------------------------------------------------------------------------
static void exact_rgb_alpha_from_image(unsigned char* bits, size_t len, unsigned char* rgbs, unsigned char* alpha) {
    size_t num = len/4;
    for (size_t i = 0; i < num; i++) {
        unsigned char* _pbits =&bits[i*4];
        unsigned char* _prgb  =&rgbs[i*3];
        _prgb[0] = _pbits[0];
        _prgb[1] = _pbits[1];
        _prgb[2] = _pbits[2];
        alpha[i] = _pbits[3];
    }
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::GetIcon(const char* iconId, wxBitmap& bitmap) {
    //@@preconditions
    assert(iconId != NULL);
    assert(strlen(iconId) > 0);
    //@@end preconditions

    IImage* _image = this->GetIconProxy()->GetImage(iconId);
    if (_image == NULL) {
        bitmap = wxNullBitmap;
    }

    int _w = _image->GetWidth();
    int _h = _image->GetHeight();
    assert(_w > 0);
    assert(_h > 0);

    unsigned char* _buff = new unsigned char [_w*_h*4];
    exact_rgb_alpha_from_image(_image->GetBufferBitsRGBA(), _w*_h*4, _buff, &_buff[_w*_h*3]);
    wxImage image(_w, _h, _buff, &_buff[_w*_h*3], true);
    bitmap = wxBitmap(image);
    delete[] _buff;
}

//-----------------------------------------------------------------------------
wxBitmap& cpl_wxMainFrame::GetIcon(const char* iconId) {
    //@@preconditions
    assert(iconId != NULL);
    assert(strlen(iconId) > 0);
    //@@end preconditions

    static wxBitmap icnBitmap;
    icnBitmap = wxNullBitmap;

    IImage* _image = this->GetIconProxy()->GetImage(iconId);
    if (_image == NULL) {
        return icnBitmap;
    }

    int _w = _image->GetWidth();
    int _h = _image->GetHeight();
    assert(_w > 0);
    assert(_h > 0);

    unsigned char* _buff = new unsigned char [_w*_h*4];
    exact_rgb_alpha_from_image(_image->GetBufferBitsRGBA(), _w*_h*4, _buff, &_buff[_w*_h*3]);
    wxImage image(_w, _h, _buff, &_buff[_w*_h*3], true);
    icnBitmap = wxBitmap(image);
    delete[] _buff;

    return icnBitmap;
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::SetBusyOnOff(int state) {
    //@@preconditions
    assert(state == 0 || state == 1);
    assert(this->mainStatusbar != NULL);
    //@@end preconditions

    if (state == 1) {
        wxBeginBusyCursor();
    }
    else {
        wxEndBusyCursor();
    }
    this->mainStatusbar->SetBusyOnOff(state);
}

//-----------------------------------------------------------------------------
void cpl_wxMainFrame::SetOutputWindowOnOff() {
    //@@preconditions
    assert(this->mainOutput != NULL);
    assert(this->mainOGLPanelManager != NULL);
    //@@end preconditions

    if (this->mainOutput->IsShown()) {
        this->mainOutput->Hide();
    }
    else {
        this->mainOutput->Show();
    }    
}
