#include "cpl_pluginframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_Plugin);

//-------------------------------------------------------------------------
// class cpl_Plugin
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void  cpl_Plugin::SetName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    if (this->pluginData.name != NULL) {
        delete[] this->pluginData.name;
        this->pluginData.name = NULL;
    }
    int slen = (int)strlen(name);
    this->pluginData.name = new char[slen+1];
    strcpy(this->pluginData.name, name);
}

//-------------------------------------------------------------------------
const char* cpl_Plugin::GetName() {
    return this->pluginData.name;
}

//-------------------------------------------------------------------------
void  cpl_Plugin::SetAuthor(const char* author) {
    //@@preconditions
    assert(author != NULL);
    assert(strlen(author) >= 0);
    //@@end preconditions

    if (this->pluginData.author != NULL) {
        delete[] this->pluginData.author;
        this->pluginData.author = NULL;
    }
    int slen = (int)strlen(author);
    this->pluginData.author = new char[slen+1];
    strcpy(this->pluginData.author, author);
}

//-------------------------------------------------------------------------
const char* cpl_Plugin::GetAuthor() {
    return this->pluginData.author;
}

//-------------------------------------------------------------------------
void  cpl_Plugin::SetCopyright(const char* copyright) {
    //@@preconditions
    assert(copyright != NULL);
    assert(strlen(copyright) >= 0);
    //@@end preconditions

    if (this->pluginData.copyright != NULL) {
        delete[] this->pluginData.copyright;
        this->pluginData.copyright = NULL;
    }
    int slen = (int)strlen(copyright);
    this->pluginData.copyright = new char[slen+1];
    strcpy(this->pluginData.copyright, copyright);
}

//-------------------------------------------------------------------------
const char* cpl_Plugin::GetCopyright() {
    return this->pluginData.copyright;
}

//-------------------------------------------------------------------------
void  cpl_Plugin::SetUrl(const char* url) {
    //@@preconditions
    assert(url != NULL);
    assert(strlen(url) >= 0);
    //@@end preconditions

    if (this->pluginData.url != NULL) {
        delete[] this->pluginData.url;
        this->pluginData.url = NULL;
    }
    int slen = (int)strlen(url);
    this->pluginData.url = new char[slen+1];
    strcpy(this->pluginData.url, url);
}

//-------------------------------------------------------------------------
const char* cpl_Plugin::GetUrl() {
    return this->pluginData.url;
}

//-------------------------------------------------------------------------
void  cpl_Plugin::SetDescription(const char* description) {
    //@@preconditions
    assert(description != NULL);
    assert(strlen(description) >= 0);
    //@@end preconditions

    if (this->pluginData.description != NULL) {
        delete[] this->pluginData.description;
        this->pluginData.description = NULL;
    }
    int slen = (int)strlen(description);
    this->pluginData.description = new char[slen+1];
    strcpy(this->pluginData.description, description);
}

//-------------------------------------------------------------------------
const char* cpl_Plugin::GetDescription() {
    return this->pluginData.description;        
}

//-------------------------------------------------------------------------
void  cpl_Plugin::SetVersion(const char* version) {
    //@@preconditions
    assert(version != NULL);
    assert(strlen(version) >= 0);
    //@@end preconditions

    if (this->pluginData.version != NULL) {
        delete[] this->pluginData.version;
        this->pluginData.version = NULL;
    }
    int slen = (int)strlen(version);
    this->pluginData.version = new char[slen+1];
    strcpy(this->pluginData.version, version);
}

//-------------------------------------------------------------------------
const char* cpl_Plugin::GetVersion() {
    return this->pluginData.version;
}

//-------------------------------------------------------------------------
void  cpl_Plugin::SetXmlName(const char* xmlname) {
    //@@preconditions
    assert(xmlname != NULL);
    assert(strlen(xmlname) >= 0);
    //@@end preconditions

    if (this->pluginData.xmlname != NULL) {
        delete[] this->pluginData.xmlname;
        this->pluginData.xmlname = NULL;
    }
    int slen = (int)strlen(xmlname);
    this->pluginData.xmlname = new char[slen+1];
    strcpy(this->pluginData.xmlname, xmlname);
}

//-------------------------------------------------------------------------
const char* cpl_Plugin::GetXmlName() {
    return this->pluginData.xmlname;
}

//-------------------------------------------------------------------------
void cpl_Plugin::SetParent(cpl_CompositePlugin* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    this->pluginData.parent = parent;
}
   
//-------------------------------------------------------------------------
cpl_CompositePlugin* cpl_Plugin::GetParent() {
    return this->pluginData.parent;
}

//-------------------------------------------------------------------------
void cpl_Plugin::SetExtensions(cpl_PluginExtensionCollection* extensions) {
    //@@preconditions
    assert(extensions != NULL);
    //@@end preconditions

    this->pluginData.extensions = extensions;
}

//-------------------------------------------------------------------------
cpl_PluginExtensionCollection* cpl_Plugin::GetExtensions() {
    return this->pluginData.extensions;    
}

//-------------------------------------------------------------------------
void cpl_Plugin::SetRequireLibs(cpl_StringCollection* names) {
    //@@preconditions
    assert(names != NULL);
    //@@end preconditions

    this->pluginData.requires = names;
}

//-------------------------------------------------------------------------
cpl_StringCollection* cpl_Plugin::GetRequireLibs() {
    return this->pluginData.requires;   
}

//-------------------------------------------------------------------------
void cpl_Plugin::SetDynamicFactories(cpl_StringCollection* names) {
    //@@preconditions
    assert(names != NULL);
    //@@end preconditions

    this->pluginData.dllnames = names;
}

//-------------------------------------------------------------------------
cpl_StringCollection* cpl_Plugin::GetDynamicFactories() {
    return this->pluginData.dllnames;   
}

//-------------------------------------------------------------------------
void cpl_Plugin::SetZScriptLibs(cpl_StringCollection* names) {
    //@@preconditions
    assert(names != NULL);
    //@@end preconditions

    this->pluginData.libnames = names;
}

//-------------------------------------------------------------------------
cpl_StringCollection* cpl_Plugin::GetZScriptLibs() {
    return this->pluginData.libnames;   
}

//-------------------------------------------------------------------------
cpl_Plugin::cpl_Plugin() {
    memset(&this->pluginData, 0, sizeof(_fbPlugin_s));
}

//-------------------------------------------------------------------------
cpl_Plugin::cpl_Plugin(cpl_CompositePlugin* parent) {
    memset(&this->pluginData, 0, sizeof(_fbPlugin_s));
    this->pluginData.parent = parent;
}

//-------------------------------------------------------------------------
cpl_Plugin::~cpl_Plugin() {
    if (this->pluginData.name != NULL) {
        delete[] this->pluginData.name;
        this->pluginData.name = NULL;
    }
    if (this->pluginData.author != NULL) {
        delete[] this->pluginData.author;
        this->pluginData.author = NULL;
    }
    if (this->pluginData.copyright != NULL) {
        delete[] this->pluginData.copyright;
        this->pluginData.copyright = NULL;
    }
    if (this->pluginData.url != NULL) {
        delete[] this->pluginData.url;
        this->pluginData.url = NULL;
    }
    if (this->pluginData.description != NULL) {
        delete[] this->pluginData.description;
        this->pluginData.description = NULL;
    }
    if (this->pluginData.version != NULL) {
        delete[] this->pluginData.version;
        this->pluginData.version = NULL;
    }
    if (this->pluginData.xmlname) {
        delete[] this->pluginData.xmlname;
        this->pluginData.xmlname = 0;
    }
    if (this->pluginData.extensions != NULL) {
        this->pluginData.extensions->Release();
        this->pluginData.extensions = 0;
    }
    if (this->pluginData.dllnames != NULL) {
        this->pluginData.dllnames->Release();
        this->pluginData.dllnames = 0;
    }
    if (this->pluginData.requires != NULL) {
        this->pluginData.requires->Release();
        this->pluginData.requires = 0;
    }
    if (this->pluginData.libnames != NULL) {
        this->pluginData.libnames->Release();
        this->pluginData.libnames = 0;
    }
}
