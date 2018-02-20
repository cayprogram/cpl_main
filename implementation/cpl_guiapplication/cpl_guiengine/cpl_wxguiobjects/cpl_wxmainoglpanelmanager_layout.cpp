#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxoglpanel.h"
#include "cpl_wxmainoglpanelmanager.h"
#include "cpl_wxmainoglpanelmanager_layout.h"

//-----------------------------------------------------------------------------
// class cpl_wxMainOGLPanelManagerLayout
//-----------------------------------------------------------------------------
//
class cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp : public ILayoutProxy {

public:
    /** get layout active comp */
    virtual int  GetLayoutActiveComp();

    /** set layout active comp */
    virtual int  SetLayoutActiveComp(int compid);

    /** set layout type */
    virtual int  SetLayoutType(int type);

    /** get layout type */
    virtual int  GetLayoutType(); 

    /** set layout mode */
    virtual int  SetLayoutMode(int mode);

    /** get layout mode */
    virtual int  GetLayoutMode();

    /** set exchange mode */
    virtual int SetExchangeMode(int mode);

    /** get exchange mode */
    virtual int GetExchangeMode();

    /** do exchange */
    virtual void DoExchange(int comp_src, int comp_target);

    /** update layout */
    virtual void UpdateLayout();

public:
    //Constructor.
    LayoutProxyImp(cpl_wxMainOGLPanelManagerLayout* pOwner):Owner(pOwner), LastModifiedTime(0) {}

    //Destructor.
    ~LayoutProxyImp() {}
    
    //member
    cpl_wxMainOGLPanelManagerLayout* Owner;

    //modified time.
    unsigned long LastModifiedTime;
};

//-----------------------------------------------------------------------------
int  cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::GetLayoutActiveComp() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    int wid = -1, idx = -1;
    this->Owner->Owner->GetActiveOGLWin(wid, idx);
    return idx;
}

//-----------------------------------------------------------------------------
int  cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::SetLayoutActiveComp(int compid) {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    this->Owner->Owner->ActiveOGLWinByIndex(compid);
    return this->GetLayoutActiveComp();
}

//-----------------------------------------------------------------------------
int  cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::SetLayoutType(int state) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(state >= 0);
    //@@end preconditions

    return this->Owner->SetLayoutType(state);
}

//-----------------------------------------------------------------------------
int  cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::GetLayoutType() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetLayoutType();
}

//-----------------------------------------------------------------------------
int  cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::SetLayoutMode(int state) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(state >= 0);
    //@@end preconditions

    return this->Owner->SetLayoutMode(state);
}

//-----------------------------------------------------------------------------
int  cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::GetLayoutMode() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetLayoutMode();
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::SetExchangeMode(int mode) {
    //@@preconditions
    assert(mode == 0|| mode == 1);
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->SetExchangeMode(mode);
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::GetExchangeMode() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->GetExchangeMode();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::DoExchange(int comp_src, int comp_target) {
    //@@preconditions
    assert(comp_src >= 0);
    assert(comp_target >= 0);
    assert(this->Owner != NULL);
    //@@end preconditions

    if (comp_src != comp_target) {
        this->Owner->DoExchange(comp_src, comp_target);
    }
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManagerLayout::LayoutProxyImp::UpdateLayout() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions
   
    if (this->Owner->GetMTime() != this->LastModifiedTime) {
        this->Owner->DoLayout();
        this->LastModifiedTime = this->Owner->GetMTime();
    }
}

//-----------------------------------------------------------------------------
// class cpl_wxMainOGLPanelManagerLayout
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
cpl_wxMainOGLPanelManagerLayout * cpl_wxMainOGLPanelManagerLayout::New(cpl_wxMainOGLPanelManager* pOwner) {
    return new cpl_wxMainOGLPanelManagerLayout(pOwner);
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::SetLayoutType(int type) {
    //@@preconditions
    assert(type >= 0);
    //@@end preconditions

    if (this->LayoutType == type) {
        return type;
    }

    this->Modified();
    int old = this->LayoutType;
    this->LayoutType = type;
    return old;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::SetLayoutMode(int mode) {
    //@@preconditions
    assert(mode >= 0);
    //@@end preconditions

    if (this->LayoutMode == mode) {
        return mode;
    }

    this->Modified();
    int old = this->LayoutMode;
    this->LayoutMode = mode;
    return old;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::GetLayoutType() {
    return this->LayoutType;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::GetLayoutMode() {
    return this->LayoutMode;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::SwitchLayoutMode() {
    this->Modified();
    int old = this->LayoutMode;
    this->LayoutMode = !this->LayoutMode;
    return old;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::DoLayout() {
    //@@preconditions
    assert(this->Owner != NULL);
    //@@end preconditions
   
    if (this->GetLayoutMode() == OGL_LAYOUT_MODE_NORMAL) {
        this->DoLayoutByNormalSize();
    }
    else {
        this->DoLayoutByFullSize();
    }
    this->Modified();
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::SetExchangeMode(int mode) {
    //@@preconditions
    assert(mode == 0 || mode == 1);
    //@@end preconditions

    if (this->ExchangeMode == mode) {
        return mode;
    }

    this->Modified();
    int old = this->ExchangeMode;
    this->ExchangeMode = mode;
    return old;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::GetExchangeMode() {
    return this->ExchangeMode;
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::DoExchange(int comp_source, int comp_target) {
    //@@preconditions
    assert(comp_source >= 0);
    assert(comp_target >= 0);
    assert(this->Owner != NULL);
    //@@end preconditions

    return this->Owner->Owner->ExchangeGraphicWindow(comp_source, comp_target);
}

//-----------------------------------------------------------------------------
int cpl_wxMainOGLPanelManagerLayout::DoExchangeDirect(int comp_source, int comp_target) {
    //@@preconditions
    assert(comp_source >= 0);
    assert(comp_target >= 0);
    assert(this->Owner != NULL);
    //@@end preconditions

    cpl_wxOGLPanel* _copy = this->Owner->POGLWins[comp_target];
    this->Owner->POGLWins[comp_target] = this->Owner->POGLWins[comp_source];
    this->Owner->POGLWins[comp_source] = _copy;
    this->DoLayout();
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManagerLayout::DoLayoutByNormalSize() {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->Owner->PPanel != NULL);
    //@@end preconditions
    
    wxSizer* sizer = this->Owner->PPanel->GetSizer();
    if (sizer != NULL) {
        for (int i = 0; i < cpl_wxMainOGLPanelManager::MAX_OGLWIN_NUM; i++) {
            sizer->Detach(this->Owner->POGLWins[i]);
            this->Owner->POGLWins[i]->Hide();
        }
    }

    cpl_wxOGLPanel* OGLWin = NULL;
    this->Owner->GetActiveOGLWin(OGLWin);
    assert(OGLWin != NULL);

    this->Owner->PPanel->SetSizer(NULL);
    switch(this->GetLayoutType()) {
        case OGL_LAYOUT_TYPE_ONE: //[]
            {
                OGLWin->Show();
                wxGridSizer* gs = new wxGridSizer(1, 1, 1, 1);
                gs->Add(OGLWin, 0, wxEXPAND);
                this->Owner->PPanel->SetSizer(gs);
            }
            break;
        case OGL_LAYOUT_TYPE_2VER_SPLIT: //[|]
            {
                wxGridSizer* gs = new wxGridSizer(2, 1, 1, 1);
                for (int i = 0; i < 2; i++) {
                    this->Owner->POGLWins[i]->Show();
                    gs->Add(this->Owner->POGLWins[i], 0, wxEXPAND);
                }
                this->Owner->PPanel->SetSizer(gs);
            }
            break;
        case OGL_LAYOUT_TYPE_2HOR_SPLIT: //[-]
            {
                wxGridSizer* gs = new wxGridSizer(1, 2, 1, 1);
                for (int i = 0; i < 2; i++) {
                    this->Owner->POGLWins[i]->Show();
                    gs->Add(this->Owner->POGLWins[i], 0, wxEXPAND);
                }
                this->Owner->PPanel->SetSizer(gs);
            }
            break;
        case OGL_LAYOUT_TYPE_FOUR: //[+]
            {
                wxGridSizer* gs = new wxGridSizer(2, 2, 1, 1);
                for (int i = 0; i < cpl_wxMainOGLPanelManager::MAX_OGLWIN_NUM; i++) {
                    this->Owner->POGLWins[i]->Show();
                    gs->Add(this->Owner->POGLWins[i], 0, wxEXPAND);
                }
                this->Owner->PPanel->SetSizer(gs);
            }
            break;
        case OGL_LAYOUT_TYPE_3VER_RIGHT2: //[ |-]
            {
                wxGridSizer* gs = new wxGridSizer(1, 2, 1, 1);
                this->Owner->POGLWins[0]->Show();
                gs->Add(this->Owner->POGLWins[0], 0, wxEXPAND);    
                wxGridSizer* subgridsizer = new wxGridSizer(2, 1, 1, 1);
                for (int i = 0; i < 2; i++) {
                    this->Owner->POGLWins[i+1]->Show();
                    subgridsizer->Add(this->Owner->POGLWins[i+1], 0, wxEXPAND);
                }
                gs->Add(subgridsizer, 0, wxEXPAND);
                this->Owner->PPanel->SetSizer(gs);              
            }
            break;
        case OGL_LAYOUT_TYPE_3VER_LEFT2: //[-| ]
            {
                wxGridSizer* gs = new wxGridSizer(1, 2, 1, 1);
                wxGridSizer* subgridsizer = new wxGridSizer(2, 1, 1, 1);
                for (int i = 0; i < 2; i++) {
                    this->Owner->POGLWins[i]->Show();
                    subgridsizer->Add(this->Owner->POGLWins[i], 0, wxEXPAND);
                }
                gs->Add(subgridsizer, 0, wxEXPAND);
                this->Owner->POGLWins[2]->Show();
                gs->Add(this->Owner->POGLWins[2], 0, wxEXPAND);    
                this->Owner->PPanel->SetSizer(gs);      
            }
            break;
        case OGL_LAYOUT_TYPE_3HOR_TOP2: //
            {
                wxGridSizer* gs = new wxGridSizer(2, 1, 1, 1);
                wxGridSizer* subgridsizer = new wxGridSizer(1, 2, 1, 1);
                for (int i = 0; i < 2; i++) {
                    this->Owner->POGLWins[i]->Show();
                    subgridsizer->Add(this->Owner->POGLWins[i], 0, wxEXPAND);
                }
                gs->Add(subgridsizer, 0, wxEXPAND);
                this->Owner->POGLWins[2]->Show();
                gs->Add(this->Owner->POGLWins[2], 0, wxEXPAND);    
                this->Owner->PPanel->SetSizer(gs);  
            }
            break;
        case OGL_LAYOUT_TYPE_3HOR_BOTTOM2: //
            {
                wxGridSizer* gs = new wxGridSizer(2, 1, 1, 1);
                this->Owner->POGLWins[0]->Show();
                gs->Add(this->Owner->POGLWins[0], 0, wxEXPAND);    
                wxGridSizer* subgridsizer = new wxGridSizer(1, 2, 1, 1);
                for (int i = 0; i < 2; i++) {
                    this->Owner->POGLWins[i+1]->Show();
                    subgridsizer->Add(this->Owner->POGLWins[i+1], 0, wxEXPAND);
                }
                gs->Add(subgridsizer, 0, wxEXPAND);
                this->Owner->PPanel->SetSizer(gs);   
            }
            break;
        default:
            assert(0);
            break;
    }
    this->Owner->PPanel->Layout();
}

//-----------------------------------------------------------------------------
void cpl_wxMainOGLPanelManagerLayout::DoLayoutByFullSize() {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->Owner->PPanel != NULL);
    //@@end preconditions

    wxSizer* sizer = this->Owner->PPanel->GetSizer();
    if (sizer != NULL) {
        for (int i = 0; i < cpl_wxMainOGLPanelManager::MAX_OGLWIN_NUM; i++) {
            sizer->Detach(this->Owner->POGLWins[i]);
            this->Owner->POGLWins[i]->Hide();
        }
    }

    cpl_wxOGLPanel* OGLWin = NULL;
    this->Owner->GetActiveOGLWin(OGLWin);
    assert(OGLWin != NULL);

    //do single layout.
    OGLWin->Show();
    this->Owner->PPanel->SetSizer(NULL);
    wxGridSizer* gs = new wxGridSizer(1, 1, 1, 1);
    gs->Add(OGLWin, 0, wxEXPAND);
    this->Owner->PPanel->SetSizer(gs);
    this->Owner->PPanel->Layout();
}

//-----------------------------------------------------------------------------
ILayoutProxy* cpl_wxMainOGLPanelManagerLayout::GetImplementation() {
    //@@preconditions
    assert(this->pLayoutProxy != NULL);
    //@@end preconditions

    return this->pLayoutProxy;
}

//-----------------------------------------------------------------------------
cpl_wxMainOGLPanelManagerLayout::cpl_wxMainOGLPanelManagerLayout(cpl_wxMainOGLPanelManager* pOwner) : LayoutType(OGL_LAYOUT_TYPE_ONE), LayoutMode(OGL_LAYOUT_MODE_NORMAL), ExchangeMode(0), Owner(pOwner) {
    this->pLayoutProxy = new LayoutProxyImp(this);
}

//-----------------------------------------------------------------------------
cpl_wxMainOGLPanelManagerLayout::~cpl_wxMainOGLPanelManagerLayout() {
    if (this->pLayoutProxy) {
        delete this->pLayoutProxy;
        this->pLayoutProxy = NULL;
    }
}
