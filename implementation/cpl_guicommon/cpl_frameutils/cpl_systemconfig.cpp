#include "cpl_frameutilsincludes.h"
#include "cpl_systemconfig.h"

//-----------------------------------------------------------------------------
// macro definitions
//-----------------------------------------------------------------------------
//
#define VERSION_MAJOR          1
#define VERSION_MINOR          0
#define VERSION_BUILDNO        1
#define VERSION_EXTEND         0

cpl_SystemConfig * cpl_SystemConfig::instance = NULL;

//-----------------------------------------------------------------------------
static char* ProductName() {
    static char product_propername[64];
    sprintf(product_propername, "3D Application Demo %d.%d <wxWidgets>", VERSION_MAJOR, VERSION_MINOR);
    return product_propername;
}

/*
//-----------------------------------------------------------------------------
static int s_resolutionType() {
    int w = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    int h = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);    

    if     (w <= 1920) return SMALL_RESOLUTION;
    else if(w <= 3840) return MEDIUM_RESOLUTION;
    else               return LARGE_RESOLUTION;
}
*/

//-----------------------------------------------------------------------------
cpl_SystemConfig * cpl_SystemConfig::Instance() {
    if (cpl_SystemConfig::instance == NULL) {
        cpl_SystemConfig::instance = new cpl_SystemConfig();
    }
    return cpl_SystemConfig::instance;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::Delete() {
    if (cpl_SystemConfig::instance) {
        delete cpl_SystemConfig::instance;
        cpl_SystemConfig::instance = NULL;
    }
}

//-----------------------------------------------------------------------------
//winfo
//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIMenubarHeight() {
    return ::GetSystemMetrics(SM_CYMENU);
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIStatusbarHeight() {
    return this->GetGUIFontSize()+10;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIFontType() {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIFontTypeBold() {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIFontTypeFixedWidth() {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUITextTitleHeight() {
    return this->GetGUIFontHeight()+8;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIFontHeight() {
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIFontHeightFixedWidth() {
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUITextButtonWidth() {
    return this->GetGUIFontSize()*7;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUITextButtonHeight() {
    return 25;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIIconButtonWidth() {
    return 28;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIIconButtonHeight() {
    return 25;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIHoriGroupGap() {
    return 2;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIVertGroupGap() {
    return 2;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetLayoutMode() {
    return this->layoutMode;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::SetLayoutMode(int mode) {
    this->layoutMode = mode;
    return 1;        
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetGUIFontSize() {
    return this->fontSize;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::SetGUIFontSize(int pointSize) {
    //@@preconditions
    assert(pointSize >0);
    //@@end preconditions
    
    this->fontSize = pointSize;
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetResolutionScheme() {
    //determine resolution scheme here...
    return this->solScheme;        
}

const char * cpl_SystemConfig::GetStringResolutionScheme()
{
    if(this->solScheme == SMALL_RESOLUTION)  return SMALL_RESOL;
    if(this->solScheme == MEDIUM_RESOLUTION) return MEDIUM_RESOL;
    if(this->solScheme == LARGE_RESOLUTION)  return LARGE_RESOL;
    if(this->solScheme == HUGE_RESOLUTION)   return HUGE_RESOL;
    return SMALL_RESOL;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetFileOpenType() {
    return this->fileOpenType;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::SetFileOpenType(int type) {    
    this->fileOpenType = type;
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetLicenceInfo() {
    return this->licenceInfo;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::SetLicenceInfo(int info) {
    int old = this->licenceInfo;
    this->licenceInfo = info;
    return old;
}

//-----------------------------------------------------------------------------
//cache global handlers.
//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetMainWindowHandler(void *handler) {
    this->pMainWindowHandler = handler;
}

//-----------------------------------------------------------------------------
void *cpl_SystemConfig::GetMainWindowHandler() {
    return this->pMainWindowHandler;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetMainPluginTreeHandler(void *handler) {
    this->pMainPluginTree = handler;
}

//-----------------------------------------------------------------------------
void *cpl_SystemConfig::GetMainPluginTreeHandler() {
    return this->pMainPluginTree;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetMainPropertiesHandler(void *handler) {
    this->pMainProperties = handler;
}

//-----------------------------------------------------------------------------
void *cpl_SystemConfig::GetMainPropertiesHandler() {
    return this->pMainProperties;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetMainResourceHandler(void *handler) {
    this->pMainResource = handler;
}

//-----------------------------------------------------------------------------
void *cpl_SystemConfig::GetMainResourceHandler() {
    return this->pMainResource;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetMainIconHandler(void *handler) {
    this->pMainIcon = handler;
}

//-----------------------------------------------------------------------------
void *cpl_SystemConfig::GetMainIconHandler() {
    return this->pMainIcon;
}

//-----------------------------------------------------------------------------
//resource directory
//-----------------------------------------------------------------------------
int cpl_SystemConfig::GetWorkDirectory(const char *& dir, int iFileType) {
    assert(dir == NULL);
    if (dir != NULL) {
        return 0;
    }
    assert(iFileType < EFileType_Count && iFileType >= 0);
    if (this->workDirectory[iFileType] != NULL) {
        dir = this->workDirectory[iFileType];
        return 1;
    }
    dir = this->workDirectory[0];
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_SystemConfig::SetWorkDirectory(const char* str, int iFileType) {
    assert(str != NULL);
    if(str == NULL) {
        return 0;
    }
    if (cpl_SystemTools::IsDirectoryExist(str) == 0) {
        return 0;
    }
    assert(iFileType < EFileType_Count && iFileType >= 0);
    if (this->workDirectory[iFileType] != NULL) {
        delete[] this->workDirectory[iFileType];
        this->workDirectory[iFileType] = NULL;
    }
    this->workDirectory[iFileType] = new char[strlen(str) + 1];
    strcpy(this->workDirectory[iFileType], str);
    return 1;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetLanguageType(char* type) {
    //@@preconditions
    assert(type != NULL);
    //@@end preconditions
    
    if (this->langType != NULL) {
        delete[] this->langType;
        this->langType = NULL;
    }
    int len = (int)strlen(type);
    this->langType = new char[len + 1];
    strncpy(this->langType, type, len);
    this->langType[len] = '\0';
}

//-----------------------------------------------------------------------------
char* cpl_SystemConfig::GetLanguageType() {
    //@@preconditions
    assert(this->langType != NULL);
    //@@end preconditions
    
    return this->langType;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetLanguageDirectory(char* dir) {
    //@@preconditions
    assert(dir != NULL);
    //@@end preconditions
    
    if (this->langDirectory != NULL) {
        delete[] this->langDirectory;
        this->langDirectory = NULL;
    }
    
    int len = (int)strlen(dir);    
    this->langDirectory = new char[len + 1];
    strncpy(this->langDirectory, dir, len);
    this->langDirectory[len] = '\0';
}

//-----------------------------------------------------------------------------
char* cpl_SystemConfig::GetLanguageDirectory() {
    //@@preconditions
    assert(this->langDirectory != NULL);
    //@@end preconditions
    
    return this->langDirectory;
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetApplicationDirectory(char* dir) {
    //@@preconditions
    assert(dir != NULL);
    //@@end preconditions
    
    if (this->appDirectory != NULL) {
        delete[] this->appDirectory;
        this->appDirectory = NULL;
    }    
    int len = (int)strlen(dir);    
    this->appDirectory = new char[len + 1];
    strncpy(this->appDirectory, dir, len);
    this->appDirectory[len] = '\0';
}

//-----------------------------------------------------------------------------
char* cpl_SystemConfig::GetApplicationDirectory() {
    //@@preconditions
    assert(this->appDirectory != NULL);
    //@@end preconditions
    
    return this->appDirectory;
}

//----------------------------------------------------------------------------
//product info.
//-----------------------------------------------------------------------------
char* cpl_SystemConfig::GetProperProductName() {
    return ProductName();
}

//-----------------------------------------------------------------------------
void cpl_SystemConfig::SetFullProductName(char* name) {
    //@@preconditions
    assert(name != NULL);
    //@@end preconditions
    
    if (this->productName != NULL) {
        delete[] this->productName;
        this->productName = NULL;
    }    
    int len = (int)strlen(name);    
    this->productName = new char[len + 1];
    strncpy(this->productName, name, len);
    this->productName[len] = '\0';
}

//-----------------------------------------------------------------------------
char* cpl_SystemConfig::GetFullProductName() {
    //@@preconditions
    assert(this->productName != NULL);
    //@@end preconditions
    
    return this->productName;
}

//-----------------------------------------------------------------------------
//constructor/destructor.
//-----------------------------------------------------------------------------
cpl_SystemConfig::cpl_SystemConfig() {
    this->fontSize           = 8;
    this->layoutMode         = 1;
    this->fileOpenType       = 0;
    this->productDomain      = 0;
    this->productName        = NULL;
    this->appDirectory       = NULL;
    this->licenceInfo        = 0;
    this->solScheme          = SMALL_RESOLUTION;  //MEDIUM_RESOLUTION

    this->pMainWindowHandler = NULL;
    this->pMainPluginTree    = NULL;
    this->pMainProperties    = NULL;
    this->pMainResource      = NULL;
    this->pMainIcon          = NULL;

    for (int i = 0; i < EFileType_Count; i++) {
        this->workDirectory[i] = NULL;
    }
    
    char * documentPath = cpl_SystemTools::GetApplicationPath();
    assert(documentPath != NULL);

    char workdir[1024];
    strcpy(workdir, documentPath);
    if (cpl_SystemTools::IsDirectoryExist(workdir)) {
        cpl_SystemTools::ConvertWindowsPathToUnix(workdir);
        this->SetWorkDirectory(workdir);
        this->SetWorkDirectory(workdir, EFileType_SESSION);
    }
    else {
        this->SetWorkDirectory("C:\\");
        this->SetWorkDirectory("C:\\", EFileType_SESSION);
    }

    char* appPath = cpl_SystemTools::GetApplicationPath();   
    this->SetApplicationDirectory(appPath);

    this->langType = new char[16];
    sprintf(this->langType, "%s", "ENGLISH");
    
    this->langDirectory = new char[16];
    sprintf(this->langDirectory, "%s", "./lang");

    char full_product_name[128];
    sprintf(full_product_name, "Demo %d.%d", VERSION_MAJOR, VERSION_MINOR);
    this->SetFullProductName(full_product_name);
}

//-----------------------------------------------------------------------------
cpl_SystemConfig::~cpl_SystemConfig() {
    for (int i = 0; i < EFileType_Count; i++) {
        if (this->workDirectory[i] != NULL) {
            delete[] this->workDirectory[i];
            this->workDirectory[i] = NULL;
        }
    }
    if (this->langDirectory != NULL) {
        delete[] this->langDirectory;
        this->langDirectory = NULL;
    }
    if (this->appDirectory != NULL) {
        delete[] this->appDirectory;
        this->appDirectory = NULL;
    }
    if (this->langType != NULL) {
        delete[] this->langType;
        this->langType = NULL;
    }
    if (this->productDomain != NULL) {
        delete[] this->productDomain;
        this->productDomain = NULL;
    }
    if (this->productName != NULL) {
        delete[] this->productName;
        this->productName = NULL;
    }
}
