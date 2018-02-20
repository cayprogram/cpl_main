#include "cpl_plugintreeframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginTreeMap);

//-----------------------------------------------------------------------------
// class cpl_PluginTreeMap
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
int cpl_PluginTreeMap::DoInitialization() {
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_PluginTreeMap::DoCleanup() {
    return 1;
}

//-----------------------------------------------------------------------------
cpl_PluginTreePath* cpl_PluginTreeMap::CreatePath(const char* path_name) {
    //@@preconditions
    assert(path_name != NULL);
    assert(path_name[0] != '\0');
    //@@end preconditions

    if (this->rootPath == NULL) {
        this->rootPath = cpl_PluginTreePath::New();
        this->rootPath->Allocate(10, 10);
    }
    return this->CreatePath(this->rootPath, path_name);
}

//-----------------------------------------------------------------------------
static char* Join(char** split_str, int num, char separator) {
    static char text[1024];
    for (int i = 0; i < num; i++) {
        (i == 0) ? sprintf(text, "%s",split_str[i]) : sprintf(text, "%s%s", text, split_str[i]);
        sprintf(text, "%s/", text);
    }
    size_t len = strlen(text);
    text[len-1] = '\0';
    return text;
}

//-----------------------------------------------------------------------------
cpl_PluginTreePath* cpl_PluginTreeMap::CreatePath(cpl_PluginTreePath* path, const char* path_name) {
    //@@preconditions
    assert(path_name != NULL);
    assert(path_name[0] != '\0');
    assert(path != NULL);
    //@@end preconditions

    int num = 0;
    char** split_str = NULL, separator = '/'; 
    cpl_SystemTools::Split(path_name, split_str, num, separator);

    int i = 0;
    cpl_PluginTreePath* curPath = path;
	while (i < num) {
        cpl_PluginTreeNode* nextPath = curPath->GetItemA(split_str[i]);
		if (nextPath == NULL) {
            nextPath = cpl_PluginTreePath::New();
            nextPath->SetName(split_str[i]);
            nextPath->SetPath(Join(split_str, i+1, separator));
            curPath->InsertNextItem(nextPath);
		}
		curPath = (cpl_PluginTreePath*)nextPath;
		++i;
	}
            
    for (int j = 0; j < num; j++) {
        delete[] split_str[j];
    }
    delete[] split_str;
    return curPath;
}

//-----------------------------------------------------------------------------
cpl_PluginTreePath* cpl_PluginTreeMap::GetPath(const char* path_name) {
    //@@preconditions
    assert(path_name != NULL);
    assert(path_name[0] != '\0');
    //@@end preconditions

    if (this->rootPath == NULL) {
        return NULL;
    }
    
    int num = 0;
    char** split_str = NULL, separator = '/'; 
    cpl_SystemTools::Split(path_name, split_str, num, separator);

    int i = 0, find = 1;
    cpl_PluginTreePath* curPath = this->rootPath;
	while (i < num) {
        cpl_PluginTreeNode* nextPath = curPath->GetItemA(split_str[i]);
		if (nextPath == NULL) {
            find = 0;
            break;
		}
		curPath = (cpl_PluginTreePath*)nextPath;
		++i;
	}
            
    for (int j = 0; j < num; j++) {
        delete[] split_str[j];
    }
    delete[] split_str;

    return find == 1 ? curPath : NULL;
}

//-----------------------------------------------------------------------------
cpl_PluginTreeMap::cpl_PluginTreeMap() {
    this->rootPath = 0;
}

//-----------------------------------------------------------------------------
cpl_PluginTreeMap::~cpl_PluginTreeMap() {
    if (this->rootPath != NULL) {
        this->rootPath->Release();
    }
}
