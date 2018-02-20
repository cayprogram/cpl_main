#include "cpl_frameimageincludes.h"

///// static variable and function /////

//-----------------------------------------------------------------------------
// class cpl_ImagePluginParser
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int cpl_ImagePluginParser::Parse(const char * plgTreePath) {
    //@@preconditions
    assert(plgTreePath);
    assert(strlen(plgTreePath) > 0);
    //@@end preconditions

    return this->parse_plugin(plgTreePath);
}

//-----------------------------------------------------------------------------
int cpl_ImagePluginParser::parse_plugin(const char * path) {
    //@@preconditions
    assert(path);
    assert(this->m_plgtreeProxy != NULL);
    //@@end preconditions

    IPluginTree* pluginTreeHandler = this->m_plgtreeProxy;
    assert(pluginTreeHandler);

    IPluginTreePath* treepath = pluginTreeHandler->GetTreePath(path);
    if (treepath == NULL) return 0;

    int numItem = treepath->GetNumberOfItems();
    for (int i = 0; i < numItem; i++) {
        IPluginTreeNode * node = treepath->GetItem(i);
        if (node->IsComposite()) continue;

        IPluginCodon* codon = node->GetCodon(); assert(codon != NULL);

        const char * value = codon->GetName(); assert(value);
        if( !strcmp(value, "Image") ) {
            this->parse_image(codon);
        }
        else if( !strcmp(value, "ImagePackage") ) {
            this->parse_image_package(codon);
        }
    } //end of for(i)

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ImagePluginParser::parse_image(IPluginCodon * codon) {
    //@@preconditions
    assert(codon);
    assert(this->m_imageManager != NULL);
    assert(this->m_plgtreeProxy != NULL);
    //@@end preconditions

    const char * imgId    = codon->GetId();  assert(imgId);
    const char * imgfname = codon->GetAttribute("file");
    if(!imgfname || imgfname[0] == 0) return 0;

    const char * xmlName  = codon->GetPlugin()->GetXmlName();  assert(xmlName);
    cpl_FileFilter::FileFilter((char *)xmlName);
    char * baseDir = cpl_FileFilter::GetFilePath(); assert(baseDir);

    char * fullPath = cpl_SystemTools::AppendPath(baseDir, (imgfname ? (char *)imgfname : ""));
    cpl_SystemTools::ConvertWindowsPathToUnix(fullPath);

    cpl_Image * img = new cpl_Image(); assert(img);
    //set unique image name
    img->SetName(imgId);
    //set image full path
    img->SetFullPath(fullPath);
    //set image format(parsed by file extension)
    cpl_FileFilter::FileFilter((char *)imgfname);
    char * ext = cpl_FileFilter::GetFileExt();  assert(ext);
    img->SetFormat(ext);

    if( IMAGE_SPEEDUP_AND_SAVEMEMORY == 0 ) {
        img->Load();
    }

    this->m_imageManager->AddImage(imgId, img);

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_ImagePluginParser::parse_image_package(IPluginCodon * codon) {
    //@@preconditions
    assert(codon);
    assert(this->m_imageManager != NULL);
    assert(this->m_plgtreeProxy != NULL);
    //@@end preconditions

    const char * pkgId    = codon->GetId();                  assert(pkgId);
    const char * pkgfname = codon->GetAttribute("file");     assert(pkgfname);
    const char * type     = codon->GetAttribute("type");     assert(type);

    if(!pkgfname || pkgfname[0] == 0) return 0;

    const char * xmlName  = codon->GetPlugin()->GetXmlName();  assert(xmlName);
    cpl_FileFilter::FileFilter((char *)xmlName);
    char * baseDir = cpl_FileFilter::GetFilePath(); assert(baseDir);

    char * fullPath = cpl_SystemTools::AppendPath(baseDir, (pkgfname ? (char *)pkgfname : ""));
    cpl_SystemTools::ConvertWindowsPathToUnix(fullPath);

    cpl_ImagePackage * imgPkg = cpl_ImagePackageObjectFactory::NewPackage(type);
    if(!imgPkg) return 0;

    //set unique image package name
    imgPkg->SetName(pkgId);
    //set image package full path
    imgPkg->SetFullPath(fullPath);
    //set image package format(parsed by file extension)
    cpl_FileFilter::FileFilter((char *)pkgfname);
    char * ext = cpl_FileFilter::GetFileExt();  assert(ext);
    imgPkg->SetFormat(ext);

    if( !strcmp(type, "blender") ) {
        //set parameters of blender package
        const char * xoff = codon->GetAttribute("offx");  assert(xoff);
        const char * yoff = codon->GetAttribute("offy");  assert(yoff);
        const char * grid = codon->GetAttribute("grid");  assert(grid);
        const char * cut  = codon->GetAttribute("cut");   assert(cut);

        std::string params;
        params += xoff; params += ",";
        params += yoff; params += ",";
        params += grid; params += ",";
        params += cut;
        imgPkg->SetParams(params.c_str());
    }

    this->m_imageManager->AddImage(pkgId, imgPkg);

    return 1;
}

//-----------------------------------------------------------------------------
cpl_ImagePluginParser::cpl_ImagePluginParser() : m_imageManager(NULL), m_plgtreeProxy(NULL), m_luascriptProxy(NULL) {
}

//-----------------------------------------------------------------------------
cpl_ImagePluginParser::~cpl_ImagePluginParser() {
}
