#include "cpl_pluginframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginExtension);

//-------------------------------------------------------------------------
// class cpl_PluginExtension
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
void cpl_PluginExtension::SetPath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) >= 0);
    //@@end preconditions

    if (this->extensionData.path != NULL) {
        delete[] this->extensionData.path;
        this->extensionData.path = NULL;
    }
    int slen = (int)strlen(path);
    this->extensionData.path = new char[slen+1];
    strcpy(this->extensionData.path, path);
}

//-------------------------------------------------------------------------
const char* cpl_PluginExtension::GetPath() {
    return this->extensionData.path;
}

//-------------------------------------------------------------------------
void cpl_PluginExtension::SetCodons(cpl_PluginCodonCollection* codons) {
    //@@preconditions
    assert(codons != NULL);
    //@@end preconditions

    this->extensionData.codons = codons;
}

//-------------------------------------------------------------------------
cpl_PluginCodonCollection* cpl_PluginExtension::GetCodons() {
    return this->extensionData.codons;
}

//-------------------------------------------------------------------------
cpl_PluginExtension::cpl_PluginExtension() {
    memset(&this->extensionData, 0, sizeof(_fbExtension_s));
}

//-------------------------------------------------------------------------
cpl_PluginExtension::~cpl_PluginExtension() {
    if (this->extensionData.path != NULL) {
        delete[] this->extensionData.path;
        this->extensionData.path = NULL;
    }
    if (this->extensionData.codons) {
        this->extensionData.codons->Release();
        this->extensionData.codons = NULL;
    }
}
