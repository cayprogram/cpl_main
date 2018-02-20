#include "cpl_frameiconincludes.h"

///// static variable and function /////

///// defines
typedef std::map<std::string, cpl_Image *>::iterator imageIt;

//-----------------------------------------------------------------------------
//  class cpl_IconImageManager
//-----------------------------------------------------------------------------
//
void cpl_IconImageManager::AddImage(const char * ImageId, cpl_Image * image) {
    //@@preconditions
    assert(ImageId != NULL);
    assert(image   != NULL);
    assert(this->m_imageMAP);
    //@@end preconditions

    std::string imgId = ImageId;

    imageIt it = this->m_imageMAP->find(imgId);
    if( it != this->m_imageMAP->end() ) {
        assert(0); //duplicate image name ?
        return;
    }

    this->m_imageMAP->insert(std::make_pair(imgId, image));
}
