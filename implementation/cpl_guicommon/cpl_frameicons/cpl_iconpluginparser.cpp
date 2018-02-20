#include "cpl_frameiconincludes.h"

///// static variable and function /////



//-----------------------------------------------------------------------------
// class cpl_IconPluginParser
//-----------------------------------------------------------------------------
//
int cpl_IconPluginParser::Parse(const char * plgTreePath) {
    //@@preconditions
    assert(plgTreePath);
    assert(strlen(plgTreePath) > 0);
    //@@end preconditions

    return this->parse_plugin(plgTreePath);
}

//-----------------------------------------------------------------------------
int cpl_IconPluginParser::parse_plugin(const char * path) {
    //@@preconditions
    assert(path);
    assert(strlen(path) > 0);
    assert(this->m_iconManager  != NULL);
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
        if( !strcmp(value, "Icon") ) {
            this->parse_icons(codon);
        }
        else if( !strcmp(value, "ImagePackage") ) {
            this->parse_image_package(codon);
        }
        else if( !strcmp(value, "Image") ) {
            this->parse_image(codon);
        }
        else if( !strcmp(value, "Category") ) {
            const char * catId = codon->GetId(); assert(catId);
            this->m_Category.assign(catId);
        }
    } //end of for(i)

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_IconPluginParser::parse_icons(IPluginCodon * codon) {
    //@@preconditions
    assert(codon);
    assert(this->m_iconManager      != NULL);
    assert(this->m_iconImageManager != NULL);
    //@@end preconditions

    std::string _imageId;
    std::string _cat = this->m_Category;
    std::string _file;

    const char * iconId = codon->GetId(); assert(iconId);

    const char * imageId = codon->GetAttribute("imgid");
    if(imageId && imageId[0] != 0)  _imageId.assign(imageId);
    
    const char * category = codon->GetAttribute("category");
    if(category && category[0] != 0)  _cat.assign(category);

    const char * file = codon->GetAttribute("file");
    if(file && file[0] != 0)  _file.assign(file);

    const char * access = codon->GetAttribute("access");

    assert(_cat.length() > 0);
    const char * uniqueIconId = makeIconUniqueName(iconId, _cat.c_str());
    if( !access || access[0] == 0 ) {
        if(_file.length() == 0) {
            //image was created before, just build the icon vs. image mapping
            assert(_imageId.length() > 0);
            this->m_iconManager->AddIcon(uniqueIconId, _imageId.c_str());
        } else {
            //create a image first
            cpl_Image * newImg = this->create_image(NULL, codon, _cat.c_str());
            if(!newImg) return 0;

            const char * newImgId = newImg->GetName(); assert(newImgId);
            this->m_iconImageManager->AddImage(newImgId, newImg);

            //build the icon vs. image mapping
            this->m_iconManager->AddIcon(uniqueIconId, newImgId);
        }
    }else { //read from image package
        assert(_imageId.length() > 0);

        cpl_Image * img = this->m_iconImageManager->GetImage(_imageId.c_str()); assert(img);

        const char * clstype = img->ClassType();
        const char * p= strstr(clstype, "package"); assert(p);

        cpl_ImagePackage * PkgImage = static_cast<cpl_ImagePackage *>(img);

        cpl_Image * subImage = new cpl_Image(); assert(subImage);
        PkgImage->SetSubImage(subImage);

        int ret1 = PkgImage->Load(access);
        int ret2 = subImage->IsLoaded();
        if(ret1 == 0 || ret2 == 0) return 0;

        const char * imgId = subImage->GetName(); assert(imgId);
        this->m_iconImageManager->AddImage(imgId, subImage);    //add image
        this->m_iconManager->AddIcon(uniqueIconId, imgId);      //add icon
    }

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_IconPluginParser::parse_image(IPluginCodon * codon) {
    //@@preconditions
    assert(codon);
    assert(this->m_iconImageManager != NULL);
    assert(this->m_plgtreeProxy != NULL);
    //@@end preconditions

    const char * imgId = codon->GetId();  assert(imgId);
    cpl_Image * newImg = this->create_image(imgId, codon);
    if( !newImg ) return 0;

    if( IMAGE_SPEEDUP_AND_SAVEMEMORY == 0 ) {
        newImg->Load();
    }

    this->m_iconImageManager->AddImage(imgId, newImg);

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_IconPluginParser::parse_image_package(IPluginCodon * codon) {
    //@@preconditions
    assert(codon);
    assert(this->m_iconImageManager != NULL);
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

    this->m_iconImageManager->AddImage(pkgId, imgPkg);

    return 1;
}

//-----------------------------------------------------------------------------
cpl_Image * cpl_IconPluginParser::create_image(const char * imgId, IPluginCodon * codon, const char * category) {
    //@@preconditions
    assert(codon);
    assert(this->m_plgtreeProxy != NULL);
    //@@end preconditions

    const char * imgfname = codon->GetAttribute("file");
    if(!imgfname || imgfname[0] == 0) return NULL;

    const char * xmlName  = codon->GetPlugin()->GetXmlName();  assert(xmlName);
    cpl_FileFilter::FileFilter((char *)xmlName);
    char * baseDir = cpl_FileFilter::GetFilePath(); assert(baseDir);

    char * fullPath = cpl_SystemTools::AppendPath(baseDir, (imgfname ? (char *)imgfname : ""));
    cpl_SystemTools::ConvertWindowsPathToUnix(fullPath);

    cpl_Image * newImage = new cpl_Image(); assert(newImage);
    //set unique image name
    if(imgId) {
        newImage->SetName(imgId);
    }else {
        char uniqueImgId[64];
        sprintf(uniqueImgId, "%s_Image%d", (category)?category:this->m_Category.c_str(), newImage->GetId());
        newImage->SetName(uniqueImgId);
    }
    //set image full path
    newImage->SetFullPath(fullPath);
    //set image format(parsed by file extension)
    cpl_FileFilter::FileFilter((char *)imgfname);
    char * ext = cpl_FileFilter::GetFileExt();  assert(ext);
    newImage->SetFormat(ext);

    return newImage;
}

//-----------------------------------------------------------------------------
cpl_IconPluginParser::cpl_IconPluginParser() : m_iconManager(NULL), m_iconImageManager(NULL), m_plgtreeProxy(NULL), m_luascriptProxy(NULL) {
    this->m_Category.clear();
}

//-----------------------------------------------------------------------------
cpl_IconPluginParser::~cpl_IconPluginParser() {
}
