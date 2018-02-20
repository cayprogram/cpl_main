#ifndef CPL_WXMAINOUTPUTPANEL_H
#define CPL_WXMAINOUTPUTPANEL_H

class cpl_wxMainOutputPanel: public cpl_OutputProxyImp {

public:
    // create.
    wxPanel* Create(wxPanel* mainPanel, wxAuiManager* mainAuiManager, int w, int h);

    // get panel 
    wxPanel* GetPanel();

public:
    // show/hide.
    void Show();
    void Hide();

    /** is shown */
    int IsShown();

    //set size
    void SetSize(const wxSize& size);

    /** synchorize with display */
    virtual void SynchorizeWithDisplay();

public:
    /** get implementation */
    IOutputMessage* GetOutputMessageImp();

public:
    // Constructor.
    cpl_wxMainOutputPanel(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainOutputPanel();

private:
    enum { MAX_NUM_LABEL = 2};

    //owner.
    cpl_wxMainFrame* Owner;

    //wxwidgets.
    wxPanel *PPanel;   
    wxAuiManager* PAuiManager;
    wxAuiPaneInfo PaneInfo;
    wxTextCtrl* PTextCommand;
    wxScrollBar* POutputScrollBar;
    wxStaticText* POutputMessage[MAX_NUM_LABEL];

    class wxThePanel;
    wxThePanel* PThePanel;

    class OutputImp;
    OutputImp* POutput;

    //number of display records.
    int numDisplayRecords;

    //create sub controls
    void CreateSubControls(int bw, int bh);

    //bind.
    void BindControls();

    //callback.
    void OnInputCommand(wxCommandEvent& event);
    void OnScrollCommand(wxScrollEvent& event);

    //output text 
    void OutputText(const char* text);
};

#endif //CPL_WXMAINOUTPUTPANEL_H
