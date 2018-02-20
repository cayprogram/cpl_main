#ifndef CPL_WXMAINFRAMEINFO_H
#define CPL_WXMAINFRAMEINFO_H

class cpl_wxMainFrameInfo : public IGraphicWindowInfo {

public:
    /** operator: get active graphic window id */
    virtual int GetGraphicWindowNumber();

    /** operator: get active graphic window id */
    virtual int GetActiveGraphicWindowId();

    /** operator: set active graphic window id */
    virtual int SetActiveGraphicWindowId(int index);

    /** operator: get raw pointer from the specific graphic window. */
    virtual int GetGraphicWindowHandle(int index);

    /** operator: get function process id from the specific graphic window. */
    virtual int GetGraphicWindowFuncProcess(int index);

    /** operator: set function process id for the specific graphic window.*/
    virtual int SetGraphicWindowFuncProcess(int index, int fid);

    /** operator: is function window attached to the specific graphic window enabled */
    virtual int IsGraphicWindowFuncWindowEnabled(int index);

    /** operator: get function window id from the specific graphic window. */
    virtual int GetGraphicWindowFuncWindow(int index);

    /** operator: set function window id for the specific graphic window.*/
    virtual int SetGraphicWindowFuncWindow(int index, int fid);    

    /** operator: get tool window id from the specific graphic window. */
    virtual int GetGraphicWindowToolWindow(int index);

    /** operator: set tool window id for the specific graphic window.*/
    virtual int SetGraphicWindowToolWindow(int index, int fid);  

    /** operator: get function window id from the specific graphic window. */
    virtual int GetGraphicWindowShortCutFuncWindow(int index);

    /** operator: set function window id for the specific graphic window.*/
    virtual int SetGraphicWindowShortCutFuncWindow(int index, int fid);    

    /** operator: get shortcut window id from the specific graphic window. */
    virtual int GetGraphicWindowContextMenuWindow(int index);

    /** operator: set shortcut window id for the specific graphic window.*/
    virtual int SetGraphicWindowContextMenuWindow(int index, int fid); 

    /** operator: set graphic window process type. */
    virtual int SetGraphicWindowFuncProcessType(int index, const char* type);    

    /** operator: get graphic window process type. */
    virtual int GetGraphicWindowFuncProcessType(int index, const char*& type);     
    
public:
    /** exchange graphic window*/
    int ExchangeGraphicWindow(int source, int target);

public:
    /** create */
    int Create();

public:
    cpl_wxMainFrameInfo(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainFrameInfo();

private:
    //owner.
    cpl_wxMainFrame* Owner;

    //inner structure.
    struct _fbFrameInfo {
        int uOGLWinID;
        int uTaskWinID;
        int uToolWindowID;
        int uShortCutFuncWindowID;
        int uContextMenuWindowID;
        int uFuncProcessID;
        char* uFuncProcessType;
    };

    _fbFrameInfo FrameInfo[MAX_SUPPORT_WIN_NUM];

    //frame info operation
    void InitFrameInfo(_fbFrameInfo* item);
    void CopyFrameInfo(_fbFrameInfo* src, _fbFrameInfo* target);
    void CleanFrameInfo(_fbFrameInfo* item);
};

#endif //CPL_WXMAINFRAMEINFO_H
