#include "cpl_pluginframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginManager);

//-----------------------------------------------------------------------------
// class cpl_PluginManager
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int cpl_PluginManager::DoInitialization() {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_PluginManager::DoCleanup() {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_PluginManager::Parse(const char* path) {
    //@@precondition
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(this->rootPluginPath == NULL);
    //@@end preconditions
    
    char _path[2048]= {0};
    sprintf(_path, "%s", path);
    cpl_SystemTools::ConvertWindowsPathToUnix(_path);
    assert(strlen(_path) > 0);

    this->rootPluginPath = cpl_CompositePlugin::New();
    this->rootPluginPath->Allocate(10, 10);
    this->rootPluginPath->SetXmlName(_path);
    this->rootPluginPath->SetName(_path);   

    return this->ParseInPath(this->rootPluginPath, _path);
}

//-----------------------------------------------------------------------------
int cpl_PluginManager::ParseInPath(cpl_CompositePlugin* plugins, const char* path) {
    //@@precondition
    assert(path != NULL);
    assert(plugins != NULL);
    //@@end preconditions

    cpl_Directory* dir = cpl_Directory::New();
    if (!dir->Open(path)) {
         dir->Release();
         return 0;
    }      
    
    int ret = 0;
    for (int i = 0; i < dir->GetNumberOfFiles(); i++) {
        const char* name = dir->GetFile(i);
        assert(name != NULL);

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0){
            continue;
        }

        char fullname[2048];
        sprintf(fullname, "%s/%s", path, name);
        if (dir->FileIsDirectory(fullname)) {
            cpl_CompositePlugin* newPath = cpl_CompositePlugin::New();
            newPath->Allocate(10, 10);
            newPath->SetName(fullname);
            if (this->ParseInPath(newPath, fullname)) {
                plugins->InsertNextItem(newPath);
                newPath->SetParent(plugins);
                ret = 1;
            }
            else {
                newPath->Release();
            }
            continue;
        }       
        if (this->ParsePlugin(plugins, fullname)) {
            ret = 1;
        }
    }
    dir->Release();
    return ret;
}

//-----------------------------------------------------------------------------
static int NameIsPluginFileName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) > 0);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    char* ret = strstr(copy, ".plugin");
    if   (ret != NULL) {
        if (strlen(ret) == strlen(".plugin")) {
            delete [] copy;
            return 1;
        }
    }
    delete [] copy;
    return 0;
}

//-----------------------------------------------------------------------------
static int NameIsXML(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) > 0);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    int ret = !strcmp(&copy[len-3], "xml");
    delete [] copy;
    return (ret != NULL);
}

//-----------------------------------------------------------------------------
int cpl_PluginManager::ParsePlugin(cpl_CompositePlugin* plugins, const char* fname) {
    //@@preconditions
    assert(fname != NULL);
    assert(strlen(fname) > 0);
    assert(plugins != NULL);
    //@@end preconditions

    if (NameIsPluginFileName(fname) == 0) {
        return 0;        
    }
    cpl_Plugin* plugin = new cpl_Plugin;
    assert(plugin != NULL);

    cpl_PluginXmlReader* reader = cpl_PluginXmlReader::New();
    assert(reader != NULL);

    plugin->SetXmlName(fname);
    reader->SetPlugin(plugin);
    reader->SetXmlSource(fname);

    int ret = reader->Parse();    
    if (ret == 1) {
        plugins->InsertNextItem(plugin);
    }
    else {
        plugin->Release();
    }
    reader->Release();
    return ret;
}

//-----------------------------------------------------------------------------
cpl_CompositePlugin* cpl_PluginManager::GetRootPath() {
    return this->rootPluginPath;
}

//-----------------------------------------------------------------------------
cpl_PluginManager::cpl_PluginManager() {
    this->rootPluginPath = 0;
}

//-----------------------------------------------------------------------------
cpl_PluginManager::~cpl_PluginManager() {
    if (this->rootPluginPath != NULL) {
        this->rootPluginPath->Release();
    }
}
