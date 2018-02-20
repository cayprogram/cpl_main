#ifndef CPL_SYSTEMCONFIG_H
#define CPL_SYSTEMCONFIG_H

enum {
    D3PLOT = 0,
    D3PLOTINT ,
    D3EIGV    ,
    DYNAIN    ,
    DYNADAT   ,
    NASTRAN   ,
    NASTRANDAT,
};

enum {
    INVALID_RESOLUTION = 0,
    SMALL_RESOLUTION   = 1,
    MEDIUM_RESOLUTION     ,
    LARGE_RESOLUTION      ,
    HUGE_RESOLUTION       
};
#define SMALL_RESOL     "SMALL"
#define MEDIUM_RESOL    "MEDIUM"
#define LARGE_RESOL     "LARGE"
#define HUGE_RESOL      "HUGE"



class cpl_SystemConfig {
public:
    /** create functions*/
    static cpl_SystemConfig * Instance();

    /** Release */
    static void Delete();

public:
    // wininfo
    /** font type */
    virtual int GetGUIFontType();

    /** font type */
    virtual int GetGUIFontTypeBold();

    /** font type */
    virtual int GetGUIFontTypeFixedWidth();

    /** font size */
    virtual int GetGUIFontHeightFixedWidth();
    
    /** font size */
    virtual int GetGUIFontHeight();

    /** text button width */
    virtual int GetGUITextButtonWidth();

    /** text button width */
    virtual int GetGUITextButtonHeight();

    /** icon button width */
    virtual int GetGUIIconButtonWidth();

    /** icon button width */
    virtual int GetGUIIconButtonHeight();

    /** icon button width */
    virtual int GetGUIHoriGroupGap();

    /** icon button width */
    virtual int GetGUIVertGroupGap();

    /** text title height */
    virtual int GetGUITextTitleHeight();

    /** menu bar height */
    virtual int GetGUIMenubarHeight();

    /** status bar height */
    virtual int GetGUIStatusbarHeight();

    /** font size */
    virtual int GetGUIFontSize();
    
    /** set font size */
    virtual int SetGUIFontSize(int fontSize);

    /** get file open type */
    virtual int GetFileOpenType();
    
    /** set file open type */
    virtual int SetFileOpenType(int type);

    /** get licence info */
    virtual int SetLicenceInfo(int info);

    /** get licence info */
    virtual int GetLicenceInfo();

    /** set layout mode */
    virtual int GetLayoutMode();
    
    /** set layout mode */
    virtual int SetLayoutMode(int mode);

public:
    /** set language type*/
    virtual void SetLanguageType(char* type);
    
    /** get language type*/
    virtual char* GetLanguageType();
    
    /** set language directory*/
    virtual void SetLanguageDirectory(char* dir);
    
    /** get language directory*/
    virtual char* GetLanguageDirectory();
    
    /** set application directory*/
    virtual void SetApplicationDirectory(char* dir);
    
    /** get language directory*/
    virtual char* GetApplicationDirectory();

public:
    /** set main window handler */
    virtual void SetMainWindowHandler(void *handler);

    /** get main window handler */
    virtual void *GetMainWindowHandler();

    /** set main plugin tree handler */
    virtual void SetMainPluginTreeHandler(void *handler);

    /** get main plugin tree handler */
    virtual void *GetMainPluginTreeHandler();

    /** set main properties handler */
    virtual void SetMainPropertiesHandler(void *handler);

    /** get main properties handler */
    virtual void *GetMainPropertiesHandler();

    /** set main resource handler */
    virtual void SetMainResourceHandler(void *handler);

public:
    /** get main resource handler */
    virtual void *GetMainResourceHandler();

    /** set main icon handler */
    virtual void SetMainIconHandler(void *handler);

    /** get main icon handler */
    virtual void *GetMainIconHandler();

    /** Get Product Name */
    virtual char* GetProperProductName();

    /** Get Full Product Name */
    virtual char* GetFullProductName();
    
    /** set full product Name*/
    virtual void  SetFullProductName(char* dir);

    /** get string width */
    virtual int MeasureStringWidth(const char* str) {return 0;}

public:
    enum TFileTypeEnum {
        EFileType_HOME = 0,
        EFileType_SESSION,
        EFileType_UNKNOW2,
        EFileType_UNKNOW3,
        EFileType_UNKNOW4,
        EFileType_UNKNOW5,
        EFileType_UNKNOW6,
        EFileType_UNKNOW7,
        EFileType_UNKNOW8,
        EFileType_UNKNOW9,
        EFileType_Count
    };
public:
    /** Set work directory */
    int SetWorkDirectory(const char* str, int iFileType = EFileType_HOME);

    /** Get work directory */
    int GetWorkDirectory(const char*& dir, int iFileType = EFileType_HOME);

public:
    /** get resolution scheme */
    int  GetResolutionScheme();
    /** get resolution string scheme */
    const char * GetStringResolutionScheme();

protected:
    /** default constructor */
    cpl_SystemConfig();

    /** destructor */
    virtual ~cpl_SystemConfig();

protected:
    int fileOpenType;
    int layoutMode;
    int fontSize;   
    int licenceInfo;

    void* pMainWindowHandler;
    void* pMainPluginTree;
    void* pMainProperties;
    void* pMainResource;
    void* pMainIcon;

    char* productDomain;
    char* productName;
    char* langDirectory;
    char* appDirectory;
    char* langType;
    char* workDirectory[EFileType_Count];

    int   solScheme;        //screen resolution scheme

private:
    static cpl_SystemConfig * instance;
};

#endif // CPL_SYSTEMCONFIG_H
