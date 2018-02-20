#include "cpl_pluginframeincludes.h"
#include <tinyxml.h>

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginXmlReader);

//-----------------------------------------------------------------------------
// class cpl_PluginXmlReader
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::SetPlugin(cpl_Plugin* Plugin) {
    //@@preconditions
    assert(Plugin != NULL);
    //@@end preconditions

    this->Plugin = Plugin;
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::SetXmlSource(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    if (this->XmlSource != NULL) {
        delete[] this->XmlSource;
        this->XmlSource = NULL;
    }
    int slen = (int)strlen(name);
    this->XmlSource = new char[slen+1];
    strcpy(this->XmlSource, name);
}

//-----------------------------------------------------------------------------
int cpl_PluginXmlReader::Parse() {
    //@@preconditions
    assert(this->Plugin != NULL);
    assert(this->XmlSource != NULL);
    //@@end preconditions

    TiXmlDocument doc(this->XmlSource);
    if (doc.LoadFile() == false){
        return 0;
    }

    TiXmlElement* root = doc.FirstChildElement("Plugin");
    if (root != NULL) {
        const char* name        = root->Attribute("name");
        const char* author      = root->Attribute("author");
        const char* copyright   = root->Attribute("copyright");
        const char* url         = root->Attribute("url");
        const char* description = root->Attribute("description");
        const char* version     = root->Attribute("version");

        if (name)        this->Plugin->SetName(name);
        if (author)      this->Plugin->SetAuthor(author);
        if (copyright)   this->Plugin->SetCopyright(copyright);
        if (url)         this->Plugin->SetUrl(url);
        if (description) this->Plugin->SetDescription(description);
        if (version)     this->Plugin->SetVersion(version);     
        
        TiXmlElement* elem = root->FirstChildElement();
        if (elem != NULL) {
            this->ParseRuntimeAndExtension(elem);
        }        
        return 1;
    }    
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::ParseRuntimeAndExtension(TiXmlElement* elem) {
    //@@preconditions
    assert(elem != NULL);
    //@@end preconditions

    TiXmlElement* currentElem = elem;
    do {
        if (strcmp(currentElem->Value(), "Require") == 0) { 
            this->ParseRequire(currentElem);
        }
        if (strcmp(currentElem->Value(), "Runtime") == 0) { 
            this->ParseRuntime(currentElem);
        }
        if (strcmp(currentElem->Value(), "ZScript") == 0) {
            this->ParseZScript(currentElem);
        }
        if (strcmp(currentElem->Value(), "Extension") == 0) {
            this->ParseExtensions(currentElem);
        }        
        currentElem = currentElem->NextSiblingElement();
    } while (currentElem != NULL);
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::ParseRequire(TiXmlElement* elem) {
    //@@preconditions
    assert(elem != NULL);
    assert(this->Plugin != NULL);
    //@@end preconditions

    cpl_StringCollection* collection = NULL;
    this->ParseAssembly(elem, collection);
    this->Plugin->SetRequireLibs(collection);
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::ParseRuntime(TiXmlElement* elem) {
    //@@preconditions
    assert(elem != NULL);
    assert(this->Plugin != NULL);
    //@@end preconditions

    cpl_StringCollection* collection = NULL;
    this->ParseAssembly(elem, collection);
    this->Plugin->SetDynamicFactories(collection);
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::ParseZScript(TiXmlElement* elem) {
    //@@preconditions
    assert(elem != NULL);
    assert(this->Plugin != NULL);
    //@@end preconditions

    cpl_StringCollection* collection = NULL;
    this->ParseAssembly(elem, collection);
    this->Plugin->SetZScriptLibs(collection);
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::ParseAssembly(TiXmlElement* elem, cpl_StringCollection*& collection) {
    //@@preconditions
    assert(elem != NULL);
    assert(collection == NULL);
    //@@end preconditions

    TiXmlElement* _current = elem->FirstChildElement("Import");
    if (_current == NULL) {
        return;
    }
    assert(_current != NULL);

    cpl_StringCollection* _collection = cpl_StringCollection::New();
    assert(_collection != NULL);
    _collection->Allocate(10, 10);
    while  (_current) {
        if (_current->Attribute("assembly") != 0) { 
            _collection->InsertNextItem(_current->Attribute("assembly"));
        }       
        _current = _current->NextSiblingElement();
    }
    if (_collection->GetNumberOfItem() == 0) {
        _collection->Release();
        _collection = NULL;
    }
    collection = _collection;
   
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::ParseExtensions(TiXmlElement* elem) {
    //@@preconditions
    assert(elem != NULL);
    //@@end preconditions

    const char* path = elem->Attribute("path");   
    if (path == NULL) {
        return;
    }
    assert(path != NULL);
    cpl_PluginExtensionCollection* extensions = this->Plugin->GetExtensions();
    if (extensions == NULL) {
        extensions = new cpl_PluginExtensionCollection();
        extensions->Allocate(4, 4);
    }

    cpl_PluginExtension* extension = new cpl_PluginExtension();
    extension->SetPath(path);
    extensions->InsertNextItem(extension);
    {
        TiXmlElement* codonElem = elem->FirstChildElement();
        if (codonElem != NULL) {
            this->ParseCodonCollection(codonElem, extension);
        } 
    }
    this->Plugin->SetExtensions(extensions);
}

//-----------------------------------------------------------------------------
static void SetXmlElementToCodon(TiXmlElement* elem, cpl_PluginCodon* codon) {
    //@@preconditions
    assert(elem  != NULL);
    assert(codon != NULL);
    //@@end preconditions
  
    //get key attributes.
    const char* name      = elem->Value();
    const char* id        = elem->Attribute("id");
    const char* condition = elem->Attribute("condition");
    if (name)      codon->SetName(name);
    if (id  )      codon->SetId(id);
    if (condition) codon->SetCondition(condition);

    TiXmlPrinter printer;
    elem->Accept(&printer);
    codon->SetXmlValue(printer.CStr());
    for (const TiXmlAttribute* attrib = elem->FirstAttribute(); attrib; attrib = attrib->Next()) {
        codon->SetAttribute(attrib->Name(), attrib->Value());
    }
}

//-----------------------------------------------------------------------------
void cpl_PluginXmlReader::ParseCodonCollection(TiXmlElement* element, cpl_PluginExtension* extension) {
    //@@preconditions
    assert(element != NULL);
    assert(extension != NULL);
    //@@end preconditions

    cpl_PluginCodonCollection* codons = extension->GetCodons();
    if (codons == NULL) {
        codons = new cpl_PluginCodonCollection();
        codons->Allocate(4, 4);
        extension->SetCodons(codons);
    }    
    TiXmlElement* currentElem = element;
    do {
        cpl_PluginCodon* codon = new cpl_PluginCodon;
        SetXmlElementToCodon(currentElem, codon);
        codons->InsertNextItem(codon);
        currentElem = currentElem->NextSiblingElement();
    } while (currentElem != NULL);
}

//-----------------------------------------------------------------------------
cpl_PluginXmlReader::cpl_PluginXmlReader() {
    this->Plugin = 0;
    this->XmlSource = 0; 
}

//-----------------------------------------------------------------------------
cpl_PluginXmlReader::~cpl_PluginXmlReader() {
    if (this->XmlSource != NULL) {
        delete[] this->XmlSource;
        this->XmlSource = NULL;
    }
}
