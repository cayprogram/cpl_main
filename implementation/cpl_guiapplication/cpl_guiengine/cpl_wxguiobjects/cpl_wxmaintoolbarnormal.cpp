#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxmaintoolbar.h"
#include "cpl_wxmaintoolbarnormal.h"
#include <string>

//-----------------------------------------------------------------------------
// static variables: main toolbar path
//-----------------------------------------------------------------------------
//
static char mainToolbarPath[] = "/Workbench/MainToolbar";

//-----------------------------------------------------------------------------
// class cpl_wxMainNormalToolbar
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxPanel* cpl_wxMainNormalToolbar::Create(int w, int h) {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(w > 0);
    assert(h > 0);
    //@@end preconditions

    this->tbBOXw = w;
    this->tbBOXh = h;

    this->PPanel = new wxPanel(this->Owner, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    this->PPanel->SetSize(this->tbBOXw, this->tbBOXh);
    this->PPanel->SetMinSize(wxSize(-1, this->tbBOXh));
    //this->PPanel->SetBackgroundColour(wxColour(223, 226, 229));
   // this->PPanel->SetForegroundColour(wxColour(223, 226, 229));

    //create toolbar
    wxToolBar * toolBar = this->CreateToolbar();

    wxBoxSizer* gs = new wxBoxSizer(wxVERTICAL);
    gs->Add(toolBar, 0,  wxEXPAND | wxALL, 0);
    this->PPanel->SetSizer(gs);
    this->PPanel->Layout();

    //bind event for toolbar
    //this->BindControls();

    return this->PPanel;
}

static std::string getIconPath(const char * iconFileName, const char * pixel, const char * scheme)
{
    assert(iconFileName);

    char * appPath = cpl_SystemConfig::Instance()->GetApplicationDirectory();
    assert(appPath != NULL);

    static std::string iconFullPath;
    iconFullPath.clear();
    
    iconFullPath  = appPath;
    iconFullPath += "/res/icon/";
    iconFullPath += scheme;
    iconFullPath += "/";
    iconFullPath += iconFileName;
    iconFullPath += "_";
    iconFullPath += pixel;
    iconFullPath += "px.png";

    return iconFullPath;
}

//-----------------------------------------------------------------------------
wxToolBar * cpl_wxMainNormalToolbar::CreateToolbar()
{
//     INCBIN(startupIcon, startupICON.c_str());
//     INCBIN_EXTERN(startupIcon);
//     unsigned int iconSz = gstartupIconSize;
    char scheme[] = "small"; //"medium";
    char pixel[]  = "24"; //"32";

    static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_TEXT | wxTB_NODIVIDER;

    wxToolBar * toolBar = new wxToolBar(this->PPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, TOOLBAR_STYLE);
    //toolBar->SetSize(this->tbBOXw, this->tbBOXh);
   // toolBar->SetBackgroundColour(wxColour(223, 226, 229));
   // toolBar->SetForegroundColour(wxColour(223, 226, 229));

    int startupID = wxNewId();
    toolBar->AddTool(startupID, wxT("Start"),
                     wxBitmap(wxString(getIconPath("beginning", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_DROPDOWN,
                     wxT("Start up"), wxT("Start to work"));
    {
        wxMenu* menu = new wxMenu;
        menu->Append(wxID_ANY, wxT("&Open"));
        menu->Append(wxID_ANY, wxT("&Save"));
        menu->AppendSeparator();
        menu->Append(wxID_ANY, wxT("&Print"));
        toolBar->SetDropdownMenu(startupID, menu);
    }

    toolBar->AddSeparator();



    toolBar->AddTool(wxNewId(), wxT("Undo"),

                     wxBitmap(wxString(getIconPath("undo", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
                     wxT("Undo last work"), wxT("Undo last work"));
    toolBar->AddTool(wxNewId(), wxT("Redo"),

                     wxBitmap(wxString(getIconPath("redo", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
                     wxT("Redo previous work"), wxT("Redo previous work"));

    toolBar->AddSeparator();



    toolBar->AddTool(wxNewId(), wxT("Process"),

        wxBitmap(wxString(getIconPath("process", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Process Manager"));
    toolBar->AddTool(wxNewId(), wxT("Design"),

        wxBitmap(wxString(getIconPath("mould_design", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Mould Design"));
    toolBar->AddTool(wxNewId(), wxT("Develop"),

        wxBitmap(wxString(getIconPath("mould_dev", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Mould Develop"));
    toolBar->AddTool(wxNewId(), wxT("Factory"),

        wxBitmap(wxString(getIconPath("mould_factory", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Mould Factory"));
    toolBar->AddTool(wxNewId(), wxT("Feedbk."),

        wxBitmap(wxString(getIconPath("mould_feedback", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Mould Feedback"));
    toolBar->AddTool(wxNewId(), wxT("Make"),

        wxBitmap(wxString(getIconPath("mould_make", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Mould Make"));
    toolBar->AddTool(wxNewId(), wxT("Pilot"),

        wxBitmap(wxString(getIconPath("mould_pilot", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Mould Pilot"));


    toolBar->AddSeparator();



    toolBar->AddTool(wxNewId(), wxT(" Pre. "),

        wxBitmap(wxString(getIconPath("pre", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Preprocessor"));
    toolBar->AddTool(wxNewId(), wxT("  Post  "),

        wxBitmap(wxString(getIconPath("post", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
        wxT("Postprocessor"));




    toolBar->AddStretchableSpace();
    toolBar->AddTool(wxNewId(), wxT("Help"),

                     wxBitmap(wxString(getIconPath("help", pixel, scheme).c_str()), wxBITMAP_TYPE_PNG), wxNullBitmap, wxITEM_NORMAL,
                     wxT("Online Help"), wxT("Online Help"));

    toolBar->Realize();
    wxSize sz = toolBar->GetSize();

    return toolBar;
}

//-----------------------------------------------------------------------------
cpl_wxMainNormalToolbar::cpl_wxMainNormalToolbar(cpl_wxMainFrame* pOwner) : cpl_wxMainToolbar(pOwner) {
}

//-----------------------------------------------------------------------------
cpl_wxMainNormalToolbar::~cpl_wxMainNormalToolbar() {
}
