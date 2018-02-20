#include "cpl_frameimageincludes.h"

///// static variable and function /////
static char imagePluginPath[] = "/Workbench/Resource/Image";

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_ImageCommonProxy);

//-----------------------------------------------------------------------------
// class cpl_ImageCommonProxy
//-----------------------------------------------------------------------------
//

IImage* cpl_ImageCommonProxy::GetImage(const char *imgId) {
    //@@preconditions
    assert(imgId != NULL);
    assert(this->m_imageManager != NULL);
    //@@end preconditions

    cpl_Image * img = this->m_imageManager->GetImage(imgId);
    if( !img ) return NULL;

    img->Load();

    return img;
}

//-----------------------------------------------------------------------------
int cpl_ImageCommonProxy::LoadPluginImages() {
    //@@preconditions
    assert(this->m_imageManager   != NULL);
    assert(this->m_plgtreeProxy   != NULL);
    assert(this->m_luascriptProxy != NULL);
   //@@end preconditions

    cpl_ImagePluginParser pluginParser;
    pluginParser.SetImageManager(this->m_imageManager);
    pluginParser.SetPluginTreeProxy(this->m_plgtreeProxy);
    pluginParser.SetLuaScriptProxy(this->m_luascriptProxy);
    pluginParser.Parse(imagePluginPath);
    return 1;
}

//-----------------------------------------------------------------------------
cpl_ImageCommonProxy::cpl_ImageCommonProxy() : m_plgtreeProxy(NULL), m_luascriptProxy(NULL), m_imageManager(NULL) {
    this->m_imageManager = new cpl_ImageManager(); assert(this->m_imageManager);
}

//-----------------------------------------------------------------------------
cpl_ImageCommonProxy::~cpl_ImageCommonProxy() {
    delete this->m_imageManager; this->m_imageManager = NULL;
}
