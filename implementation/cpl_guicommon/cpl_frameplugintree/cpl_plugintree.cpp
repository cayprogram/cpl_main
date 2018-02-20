#include "cpl_plugintreeframeincludes.h"

//local includes.
#include <lua.hpp>
#include <tinyxml.h>
#include <cpl_guicommonincludes.h>

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginTree);

//-----------------------------------------------------------------------------
// class cpl_PluginTree
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int cpl_PluginTree::SetLuaState(void* luaState) {
    //@@preconditions
    assert(luaState != NULL);
    //@@end preconditions

    this->pLuaState = luaState;
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_PluginTree::Parse(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) > 0);
    assert(this->PluginManager != NULL);
    assert(this->PathManager != NULL);
    //@@end preconditions

    //parse plugin in the specific path.
    this->PluginManager->Parse(path);

    //load resources accordingly.
    this->LoadLibRequired();
    this->LoadDllRuntimes();
    this->LoadZScriptPackage();

    //assembly everyting together.
    this->AssemblyExtensions();
    return 1;
}

//-----------------------------------------------------------------------------
static int RegisterLib(void* lua_state, const char* lua_fname) {
    //@@preconditions
    assert(lua_fname != NULL);
    assert(strlen(lua_fname) > 0);
    assert(lua_state != NULL);
    //@@end preconditions

    lua_State* state = (lua_State*)lua_state;
    assert(state != NULL);
    if (luaL_loadfile(state, lua_fname) || lua_pcall(state, 0, 0, 0)) {
        printf("error: %s", lua_tostring(state, -1));
    }
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_PluginTree::LoadLuaScriptPackage() {
    //@@preconditions
    assert(this->pLuaState != NULL);
    //@@end preconditions

    for (int j = 0; j < this->ZScriptResource.libCount; j++) {
        RegisterLib(this->pLuaState, this->ZScriptResource.libHandlers[j]);
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_PluginTree::LoadLuaRuntimePackage() {
    //@@preconditions
    assert(this->pLuaState != NULL);
    //@@end preconditions

    typedef int (* CreatFuncPtr) (lua_State* L);    
    for (int j = 0; j < this->DLLResource.libCount; j++) {
        void* lib = this->DLLResource.libHandlers[j];
        if (lib) {
            CreatFuncPtr loadfunction = (CreatFuncPtr) cpl_DynamicLoader::GetSymbolAddress(lib, "luaopen_plugin");
            if (loadfunction) {
                loadfunction((lua_State *)this->pLuaState);
            }
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_PluginTree::LoadClassCreatorRuntimePackage(cpl_Creator* pCreator) {
    //@@preconditions
    assert(pCreator != NULL);
    //@@end preconditions

    typedef cpl_ImplementationProxy* (* CreatFuncPtr) (int&);
    int sum = 0;
    for (int j = 0; j < this->DLLResource.libCount; j++) {
        void* lib = this->DLLResource.libHandlers[j];
        if (lib) {
            CreatFuncPtr loadfunction = (CreatFuncPtr) cpl_DynamicLoader::GetSymbolAddress(lib, "CoGetImplementationProxy");
            if (loadfunction) {
                int count = 0;
                cpl_ImplementationProxy* proxies = loadfunction(count);
                for (int i = 0; i < count; i++) {
                    pCreator->InsertImplementationProxy(proxies[i]);
                    sum++;
                }
            }
        }
    }
    return sum;
}

//-----------------------------------------------------------------------------
IPluginTreePath* cpl_PluginTree::GetTreePath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(path[0] != '\0');
    assert(this->PathManager != NULL);
    //@@end preconditons

    return this->PathManager->GetPath(path);
}

//-----------------------------------------------------------------------------
IPluginTreePath* cpl_PluginTree::CreateTreePath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(path[0] != '\0');
    assert(this->PathManager != NULL);
    //@@end preconditons

    return this->PathManager->CreatePath(path);
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::AssemblyExtensions() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    //@@end preconditions

    cpl_CompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPlugins();
    if (count == 0) {
        return;
    }
    this->GetNestSubItemExtensions(root);
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::LoadLibRequired() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    assert(this->DLLResource.libHandlers == NULL);
    //@@end preconditions

    cpl_CompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPluginsRequireLib();
    if (count == 0) {
        return;
    }

    this->DLLRequired.libCount = 0;
    this->DLLRequired.libSize  = count;
    this->DLLRequired.libHandlers = new void* [count];
    assert(this->DLLRequired.libHandlers != NULL);

    this->GetNestSubItemLibRequired(root);
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::LoadDllRuntimes() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    assert(this->DLLResource.libHandlers == NULL);
    //@@end preconditions

    cpl_CompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPluginsDLL();
    if (count == 0) {
        return;
    }

    this->DLLResource.libCount = 0;
    this->DLLResource.libSize = count;
    this->DLLResource.libHandlers = new void* [count];
    assert(this->DLLResource.libHandlers != NULL);

    this->GetNestSubItemDllRuntimes(root);
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::LoadZScriptPackage() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    assert(this->ZScriptResource.libHandlers == NULL);
    //@@end preconditions

    cpl_CompositePlugin* root = this->PluginManager->GetRootPath();
    assert(root != NULL);

    int count = root->GetNumberOfNestPluginsZScript();
    if (count == 0) {
        return;
    }

    this->ZScriptResource.libCount = 0;
    this->ZScriptResource.libSize  = count;
    this->ZScriptResource.libHandlers = new char* [count];
    assert(this->ZScriptResource.libHandlers != NULL);

    this->GetNestSubItemScriptName(root);
}

//-----------------------------------------------------------------------------
static int vtkNameIsSharedLibrary(const char* name) {
    //@@preconditions
    assert(name != NULL);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    char* ret = strstr(copy, cpl_DynamicLoader::LibExtension());
    if   (ret != NULL) {
        if (strlen(ret) == strlen(cpl_DynamicLoader::LibExtension())) {
            delete [] copy;
            return 1;
        }
    }
    delete [] copy;
    return 0;
}

//-----------------------------------------------------------------------------
static int vtkNameIsScriptLibrary(const char* name) {
    //@@preconditions
    assert(name != NULL);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    char* ret = strstr(copy, ".lua");
    if   (ret != NULL) {
        if (strlen(ret) == strlen(".lua")) {
            delete [] copy;
            return 1;
        }
    }
    delete [] copy;
    return 0;
}

//-----------------------------------------------------------------------------
static int vtkNameIsLanguageLibrary(const char* name) {
    //@@preconditions
    assert(name != NULL);
    //@@end preconditions

    int len = static_cast<int>(strlen(name));
    char* copy = new char[len+1];
    for(int i = 0; i < len; i++) {
        copy[i] = (char)tolower(name[i]);
    }
    copy[len] = 0;
    int ret = !strcmp(&copy[len-4], "lang");
    delete [] copy;
    return (ret != NULL);
}

//-----------------------------------------------------------------------------
static char* CreateFullPath(const char* path, const char* file) {
    //@@preconditions
    assert(path != NULL);
    assert(file != NULL);
    //@@end preconditions

    int lenpath = static_cast<int>(strlen(path));
    char* ret = new char[lenpath + strlen(file)+2];
    const char sep = '/';
    // make sure the end of path is a separator
    strcpy(ret, path);
    if (ret[lenpath-1] != sep) {
        ret[lenpath] = sep;
        ret[lenpath+1] = 0;
    }
    strcat(ret, file);
    return ret;
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::GetNestSubItemLibRequired(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemLibRequired((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            cpl_StringCollection* collection = sub_plugin->GetRequireLibs();
            if (collection == NULL) {
                continue;
            }
            const char* path = sub_plugin->GetParent()->GetName();
            if (path == NULL) {
                continue;
            }
            const char* name = NULL;
            for (collection->InitTraversal(); collection->GetNextItem(name);) {
                if (vtkNameIsSharedLibrary(name)) {
                    char* fullpath = CreateFullPath(path, name);
                    cpl_LibHandle lib = cpl_DynamicLoader::OpenLibrary(fullpath);
                    if(lib) {
                        assert(this->DLLRequired.libCount < this->DLLRequired.libSize); 
                        this->DLLRequired.libHandlers[this->DLLRequired.libCount++] = lib;
                    }
                    delete [] fullpath;
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::GetNestSubItemDllRuntimes(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemDllRuntimes((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            cpl_StringCollection* collection = sub_plugin->GetDynamicFactories();
            if (collection == NULL) {
                continue;
            }
            const char* path = sub_plugin->GetParent()->GetName();
            if (path == NULL) {
                continue;
            }            
            const char* name = NULL;
            for (collection->InitTraversal(); collection->GetNextItem(name);) {
                if (vtkNameIsSharedLibrary(name)) {
                    char* fullpath = CreateFullPath(path, name);
                    cpl_LibHandle lib = cpl_DynamicLoader::OpenLibrary(fullpath);
                    if(lib) {
                        //coclass.
                        {
                            typedef cpl_ImplementationProxy* (* CreatFuncPtr) (int&);
                            CreatFuncPtr loadfunction = (CreatFuncPtr) cpl_DynamicLoader::GetSymbolAddress(lib, "CoGetImplementationProxy");
                            if (loadfunction) {
                                assert(this->DLLResource.libCount < this->DLLResource.libSize); 
                                this->DLLResource.libHandlers[this->DLLResource.libCount++] = lib;
                            }
                        }
                        //lua components.
                        {
                            typedef int (* CreatFuncPtr) (lua_State* L);
                            CreatFuncPtr loadfunction = (CreatFuncPtr) cpl_DynamicLoader::GetSymbolAddress(lib, "luaopen_plugin");
                            if (loadfunction) {
                                assert(this->DLLResource.libCount < this->DLLResource.libSize); 
                                this->DLLResource.libHandlers[this->DLLResource.libCount++] = lib;
                            }
                        }
                    }
                    delete [] fullpath;
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::GetNestSubItemScriptName(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemScriptName((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            cpl_StringCollection* collection = sub_plugin->GetZScriptLibs();
            if (collection == NULL) {
                continue;
            }
            const char* path = sub_plugin->GetParent()->GetName();
            if (path == NULL) {
                continue;
            }
            const char* name = NULL;
            for (collection->InitTraversal(); collection->GetNextItem(name);) {
                if (vtkNameIsScriptLibrary(name)) {
                    char* fullpath = CreateFullPath(path, name);
                    FILE* fp = fopen(fullpath, "r");
                    if (fp != NULL) {
                        assert(this->ZScriptResource.libCount < this->ZScriptResource.libSize); 
                        this->ZScriptResource.libHandlers[this->ZScriptResource.libCount++] = fullpath;
                        fclose(fp);
                        continue;
                    }
                    delete[] fullpath;
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::GetNestSubItemExtensions(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            this->GetNestSubItemExtensions((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            cpl_PluginExtensionCollection* extensions = sub_plugin->GetExtensions();
            if (extensions != NULL) {
                cpl_PluginExtension* extension = 0;
                for (extensions->InitTraversal(); extensions->GetNextItem(extension); ) {
                    if (extension) {
                        const char* path = extension->GetPath();
                        if (path != NULL) {
                            cpl_PluginTreePath* pluginPath = this->PathManager->CreatePath(path);
                            this->AddExtensionIntoPath(extension, pluginPath, sub_plugin);
                        }                        
                    }
                }
            }
        }        
    }
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::AddExtensionIntoPath(cpl_PluginExtension* extension, cpl_PluginTreePath* path, cpl_Plugin* plugin) {
    //@@preconditions
    assert(extension != NULL);
    assert(plugin != NULL);
    assert(path != NULL);    
    //@@end preconditions

    cpl_PluginCodonCollection* codons = extension->GetCodons();
    if (codons == NULL) {
        return;
    }

    cpl_PluginCodon* codon = 0;
    for (codons->InitTraversal(); codons->GetNextItem(codon); ) {
        if (codon == NULL) {
            continue;
        }
        codon->SetPlugin(plugin);
        IPluginTreeNode* node = path->GetItem(codon);
        if (node == NULL) {
            node = new cpl_PluginTreeNode(path);
            node->SetCodon(codon);
            path->InsertNextItem(node);
        }        
    }   
}

//-----------------------------------------------------------------------------
void cpl_PluginTree::UnLoadDynamicFactories() {
    //@@preconditions
    assert(this->PluginManager != NULL);
    //@@end preconditions

    //dll resources.
    {
        for (int i = 0; i < this->DLLResource.libCount; i++) {
            void* lib = this->DLLResource.libHandlers[i];
            if (lib == 0) {
                continue;
            }
            cpl_DynamicLoader::CloseLibrary(reinterpret_cast<cpl_LibHandle>(lib));
        }
    }
    //required dll..
    {
        for (int i = 0; i < this->DLLRequired.libCount; i++) {
            void* lib = this->DLLRequired.libHandlers[i];
            if (lib == 0) {
                continue;
            }
            cpl_DynamicLoader::CloseLibrary(reinterpret_cast<cpl_LibHandle>(lib));
        }
    }
}

//-----------------------------------------------------------------------------
cpl_PluginTree::cpl_PluginTree() {
    this->PluginManager = cpl_PluginManager::New();
    this->PathManager = cpl_PluginTreeMap::New();
    this->pLuaState = NULL;
    this->DLLRequired.libCount = 0;
    this->DLLRequired.libHandlers = NULL;
    this->DLLResource.libCount = 0;
    this->DLLResource.libHandlers = NULL;
    this->ZScriptResource.libCount = 0;
    this->ZScriptResource.libHandlers = NULL;
}

//-----------------------------------------------------------------------------
cpl_PluginTree::~cpl_PluginTree() {
    if (this->PathManager != NULL) {
        this->PathManager->Release();
    }
    if (this->PluginManager != NULL) {
        this->PluginManager->Release();
    }
    if (this->DLLResource.libHandlers) {
        delete[] this->DLLResource.libHandlers;
        this->DLLResource.libHandlers = NULL;
    }
    if (this->ZScriptResource.libHandlers) {
        for (int i = 0; i < this->ZScriptResource.libCount; i++) {
            if (this->ZScriptResource.libHandlers[i]) {
                delete[] this->ZScriptResource.libHandlers[i];
            }            
        }
        delete[] this->ZScriptResource.libHandlers;
        this->ZScriptResource.libHandlers = NULL;
    }
}
