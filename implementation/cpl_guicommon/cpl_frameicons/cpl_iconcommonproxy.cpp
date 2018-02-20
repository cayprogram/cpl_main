#include "cpl_frameiconincludes.h"

///// static variable and function /////
static char smallIconPath[]  = "/Workbench/Resource/Icon/SmallIcon";
static char mediumIconPath[] = "/Workbench/Resource/Icon/MediumIcon";
static char largeIconPath[]  = "/Workbench/Resource/Icon/LargeIcon";

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_IconCommonProxy);

//-----------------------------------------------------------------------------
// class cpl_IconCommonProxy
//-----------------------------------------------------------------------------
//
IImage* cpl_IconCommonProxy::GetImage(const char *iconId) {
    //@@preconditions
    assert(iconId != NULL);
    assert(strlen(iconId) > 0);
    assert(this->m_iconManager != NULL);
    //@@end preconditions

    const char * sol = cpl_SystemConfig::Instance()->GetStringResolutionScheme(); assert(sol);
    const char * uniqueIconId = makeIconUniqueName(iconId, sol);

    cpl_Image * img = this->get_image(uniqueIconId);
    if(!img) return NULL;

    const char * clstype = img->ClassType();
    if( strcmp(clstype, "Image") == 1 ) return NULL;

    int ret = img->Load();
    assert(ret == 1);

    return img;
}

//-----------------------------------------------------------------------------
int cpl_IconCommonProxy::LoadPluginIcons() {
    //@@preconditions
    assert(this->m_iconImageManager   != NULL);
    assert(this->m_iconManager        != NULL);
    assert(this->m_plgtreeProxy       != NULL);
    assert(this->m_luascriptProxy     != NULL);
    //@@end preconditions

    cpl_IconPluginParser  pluginIconParser; //icon parser
    pluginIconParser.SetIconImageManager(this->m_iconImageManager);
    pluginIconParser.SetIconManager(this->m_iconManager);
    pluginIconParser.SetPluginTreeProxy(this->m_plgtreeProxy);
    pluginIconParser.SetLuaScriptProxy(this->m_luascriptProxy);

    //////////////////////////////////////////////////////////////////////////
    //parse small icons
    pluginIconParser.Parse(smallIconPath);

    //////////////////////////////////////////////////////////////////////////
    //parse medium icons
    pluginIconParser.Parse(mediumIconPath);

    //////////////////////////////////////////////////////////////////////////
    //parse large icons
    pluginIconParser.Parse(largeIconPath);

    return 1;
}

//-----------------------------------------------------------------------------
cpl_Image * cpl_IconCommonProxy::get_image(const char * iconId) {
    //@@preconditions
    assert(iconId != NULL);
    assert(strlen(iconId) > 0);
    //@@end preconditions

    const char * imageId = this->m_iconManager->GetIcon(iconId);
    if( !imageId ) return NULL;

    return this->m_iconImageManager->GetImage(imageId);
}

//-----------------------------------------------------------------------------
cpl_IconCommonProxy::cpl_IconCommonProxy() : m_iconImageManager(NULL), m_iconManager(NULL), m_plgtreeProxy(NULL), m_luascriptProxy(NULL) {
    this->m_iconImageManager = new cpl_IconImageManager();   assert(this->m_iconImageManager);
    this->m_iconManager      = new cpl_IconManager();        assert(this->m_iconManager);
}

//-----------------------------------------------------------------------------
cpl_IconCommonProxy::~cpl_IconCommonProxy() {
    delete this->m_iconImageManager;   this->m_iconImageManager = NULL;
    delete this->m_iconManager;        this->m_iconManager      = NULL;
}
