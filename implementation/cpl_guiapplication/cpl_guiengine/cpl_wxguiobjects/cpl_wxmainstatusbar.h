#ifndef CPL_WXMAINSTATUSBAR_H
#define CPL_WXMAINSTATUSBAR_H

class cpl_wxProgessPanel;
class cpl_wxMainStatusbar {

public:
    // create.
    wxPanel* Create(int w, int h);

public:
    /** GUI services interface implementations */
    virtual IOutputStatusInfo* GetOutputStatusInfoHandler();

public:
    /** interface */
    /** output status */
    void OutputStatusA(const char* text);
    void OutputStatusB(const char* text);
    void OutputStatusC(const char* text);

    /** set busy on/off */
    void SetBusyOnOff(int state);

    /** status progress */
    void SetProgressStatus(int state);

    /** status progress */
    void SetProgressValue(float value);

public:
    cpl_wxMainStatusbar(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainStatusbar();

private:
    //owner.
    cpl_wxMainFrame* Owner;

    //raw pointer.
    wxPanel* PPanel;
    wxStaticText* PStatusA;
    wxStaticText* PStatusB;
    wxStaticText* PStatusC;
    wxStaticBitmap* PSignal;
    cpl_wxProgessPanel* PProcessBar;

    //bitmap
    wxBitmap BitmapBusyOn;
    wxBitmap BitmapBusyOff;

    class OutputStatusInfo;
    OutputStatusInfo* PStatusInfo;

    //create sub controls
    void CreateSubControls(int bw, int bh);

    //bind.
    void BindControls();
};

#endif //CPL_WXMAINSTATUSBAR_H
