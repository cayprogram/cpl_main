#ifndef GRAPHICWINDOWMANAGERINTERFACE_H
#define GRAPHICWINDOWMANAGERINTERFACE_H

class IGraphicWindowInfo {

public:
    /** operator: get active graphic window id */
    virtual int GetGraphicWindowNumber() = 0;

    /** operator: get active graphic window id */
    virtual int GetActiveGraphicWindowId() = 0;

    /** operator: set active graphic window id */
    virtual int SetActiveGraphicWindowId(int wid) = 0;

    /** operator: get raw pointer from the specific graphic window. */
    virtual int GetGraphicWindowHandle(int wid) = 0;

    /** operator: get function process id from the specific graphic window. */
    virtual int GetGraphicWindowFuncProcess(int wid) = 0;

    /** operator: set function process id for the specific graphic window.*/
    virtual int SetGraphicWindowFuncProcess(int wid, int fid) = 0;

    /** operator: is function window attached to the specific graphic window enabled */
    virtual int IsGraphicWindowFuncWindowEnabled(int wid) = 0;

    /** operator: get function window id from the specific graphic window. */
    virtual int GetGraphicWindowFuncWindow(int wid) = 0;

    /** operator: set function window id for the specific graphic window.*/
    virtual int SetGraphicWindowFuncWindow(int wid, int fid) = 0;    

    /** operator: get tool window id from the specific graphic window. */
    virtual int GetGraphicWindowToolWindow(int wid) = 0;

    /** operator: set tool window id for the specific graphic window.*/
    virtual int SetGraphicWindowToolWindow(int wid, int fid) = 0;  

    /** operator: get function window id from the specific graphic window. */
    virtual int GetGraphicWindowShortCutFuncWindow(int wid) = 0;

    /** operator: set function window id for the specific graphic window.*/
    virtual int SetGraphicWindowShortCutFuncWindow(int wid, int fid) = 0;    

    /** operator: get shortcut window id from the specific graphic window. */
    virtual int GetGraphicWindowContextMenuWindow(int wid) = 0;

    /** operator: set shortcut window id for the specific graphic window.*/
    virtual int SetGraphicWindowContextMenuWindow(int wid, int fid) = 0; 

    /** operator: set graphic window process type. */
    virtual int SetGraphicWindowFuncProcessType(int index, const char* type) = 0;    

    /** operator: get graphic window process type. */
    virtual int GetGraphicWindowFuncProcessType(int index, const char*& type) = 0;    
};

#endif //GRAPHICWINDOWMANAGERINTERFACE_H
