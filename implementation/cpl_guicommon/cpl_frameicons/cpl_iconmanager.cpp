#include "cpl_frameiconincludes.h"

///// static variable and function /////

///// defines
typedef std::map<std::string, std::string>::iterator iconIt;

//------------------------------------------------------------------------
//  class cpl_IconManager
//------------------------------------------------------------------------

const char * cpl_IconManager::GetIcon(const char * iconId) {
    //@@preconditions
    assert(iconId != NULL);
    assert(strlen(iconId) > 0);
    //@@end preconditions

    return this->find_icon(iconId);
}

//------------------------------------------------------------------------
int cpl_IconManager::AddIcon(const char * iconId, const char * imageId) {
    //@@preconditions
    assert(iconId  != NULL);
    assert(imageId != NULL);
    assert(this->m_iconMap);
    //@@end preconditions

    std::string icnId = iconId;
    assert(icnId.length() > 0);

    iconIt it = this->m_iconMap->find(icnId);
    if( it != this->m_iconMap->end() ) {
        assert(0); //duplicated icon name?
        return 0;
    }

    std::string imgId = imageId; assert(imgId.length() > 0);
    this->m_iconMap->insert(std::make_pair(icnId, imgId));
    return 1;
}

//------------------------------------------------------------------------
int cpl_IconManager::DeleteIcon(const char * iconId) {
    //@@preconditions
    assert(iconId != NULL);
    assert(strlen(iconId) > 0);
    assert(this->m_iconMap);
    //@@end preconditions

    std::string icnId = iconId;
    assert(icnId.length() > 0);

    iconIt it = this->m_iconMap->find(icnId);
    if (it == this->m_iconMap->end() ) return 0;

    this->m_iconMap->erase(it);
    return 1;
}

//------------------------------------------------------------------------
const char * cpl_IconManager::find_icon(const char * iconId) {
    //@@preconditions
    assert(iconId != NULL);
    assert(strlen(iconId) > 0);
    assert(this->m_iconMap);
    //@@end preconditions

    iconIt it = this->m_iconMap->find(std::string(iconId));
    if( it == this->m_iconMap->end() ) return NULL;

    return (it->second).c_str();
}

//------------------------------------------------------------------------
void cpl_IconManager::cleanup_map() {
    //@@preconditions
    assert(this->m_iconMap);
    //@@end preconditions

    this->m_iconMap->clear();
}

//------------------------------------------------------------------------
cpl_IconManager::cpl_IconManager() {
    this->m_iconMap  = new std::map<std::string, std::string>; assert(this->m_iconMap);
}

//------------------------------------------------------------------------
cpl_IconManager::~cpl_IconManager() {
    this->cleanup_map();
    delete this->m_iconMap;  this->m_iconMap = NULL;
}
