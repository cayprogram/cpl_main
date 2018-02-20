#include "cpl_frameimageincludes.h"

///// static variable and function /////


///// defines
typedef std::map<std::string, cpl_Image *>::iterator imageIt;

//-----------------------------------------------------------------------------
//  class cpl_ImageManager
//-----------------------------------------------------------------------------
//
void cpl_ImageManager::AddImage(const char * ImageId, cpl_Image * image) {
    //@@preconditions
    assert(ImageId != NULL);
    assert(image   != NULL);
    assert(this->m_imageMAP);
    //@@end preconditions

    std::string imgId = ImageId;

    imageIt it = this->m_imageMAP->find(imgId);
    if( it != this->m_imageMAP->end() ) {  //overwrite duplicate name image
        cpl_Image * img = it->second;
        this->delete_image(img);

        this->m_imageMAP->erase(it);
    }

    this->m_imageMAP->insert(std::make_pair(imgId, image));
}

//-----------------------------------------------------------------------------
cpl_Image * cpl_ImageManager::GetImage(const char * ImageId) {
    //@@preconditions
    assert(ImageId != NULL);
    //@@end preconditions

    return this->find_image(ImageId);
}

//-----------------------------------------------------------------------------
void cpl_ImageManager::DeleteImage(const char * ImageId) {
    //@@preconditions
    assert(ImageId != NULL);
    assert(this->m_imageMAP);
    //@@end preconditions

    imageIt it = this->m_imageMAP->find(ImageId);
    if( it == this->m_imageMAP->end() ) return;

    cpl_Image * img = it->second;
    this->delete_image(img);

    this->m_imageMAP->erase(it);
}

//-----------------------------------------------------------------------------
cpl_Image * cpl_ImageManager::find_image(const char * ImageId) {
    //@@preconditions
    assert(ImageId != NULL);
    assert(this->m_imageMAP);
    //@@end preconditions

    imageIt it = this->m_imageMAP->find(std::string(ImageId));
    if( it == this->m_imageMAP->end() ) return NULL;

    return it->second;
}

//-----------------------------------------------------------------------------
void cpl_ImageManager::cleanup_map() {
    //@@preconditions
    assert(this->m_imageMAP);
    //@@end preconditions

    imageIt it = this->m_imageMAP->begin();
    for(; it != this->m_imageMAP->end(); ++it) {
        cpl_Image * img = it->second;
        this->delete_image(img);
    }

    this->m_imageMAP->clear();
}

//-----------------------------------------------------------------------------
void cpl_ImageManager::delete_image(cpl_Image * img) {
    //@@preconditions
    assert(img != NULL);
    //@@end preconditions

    delete img; img = NULL;
}

//-----------------------------------------------------------------------------
cpl_ImageManager::cpl_ImageManager() : m_imageMAP(NULL) {
    this->m_imageMAP  = new std::map<std::string, cpl_Image *>; assert(this->m_imageMAP);
}

//-----------------------------------------------------------------------------
cpl_ImageManager::~cpl_ImageManager() {
    this->cleanup_map();
    delete this->m_imageMAP; this->m_imageMAP = NULL;
}
