#include "cpl_plugintreeframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_PluginTreeNode);

//-----------------------------------------------------------------------------
// class cpl_PluginTreeNode
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
void cpl_PluginTreeNode::SetName(const char* name) {
    //@@preconditions
    assert(name != NULL);
    assert(strlen(name) >= 0);
    //@@end preconditions

    if (this->nodeData.name != NULL) {
        delete[] this->nodeData.name;
        this->nodeData.name = NULL;
    }
    int slen = (int)strlen(name);
    this->nodeData.name = new char[slen+1];
    strcpy(this->nodeData.name, name);
}

//-----------------------------------------------------------------------------
const char* cpl_PluginTreeNode::GetName() {
    return this->nodeData.name;
}

//-----------------------------------------------------------------------------
void cpl_PluginTreeNode::SetPath(const char* path) {
    //@@preconditions
    assert(path != NULL);
    assert(strlen(path) >= 0);
    //@@end preconditions

    if (this->nodeData.path != NULL) {
        delete[] this->nodeData.path;
        this->nodeData.path = NULL;
    }
    int slen = (int)strlen(path);
    this->nodeData.path = new char[slen+1];
    strcpy(this->nodeData.path, path);
}

//-----------------------------------------------------------------------------
const char* cpl_PluginTreeNode::GetPath() {
    return this->nodeData.path;
}

//-----------------------------------------------------------------------------
void cpl_PluginTreeNode::SetUserData(const void* usrData) {
    this->nodeData.data = (void*)usrData;
}

//-----------------------------------------------------------------------------
const void* cpl_PluginTreeNode::GetUserData() {
    return this->nodeData.data;
}

//-----------------------------------------------------------------------------
void cpl_PluginTreeNode::SetCodon(IPluginCodon* codon) {
    //@@preconditions
    assert(codon != NULL);
    //@@end preconditions

    this->nodeData.codon = (cpl_PluginCodon*)codon;
}

//-----------------------------------------------------------------------------
IPluginCodon* cpl_PluginTreeNode::GetCodon() {
    return this->nodeData.codon;
}

//-----------------------------------------------------------------------------
void cpl_PluginTreeNode::SetParent(IPluginTreePath* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    this->nodeData.parent = (cpl_PluginTreePath*)parent;
}
   
//-----------------------------------------------------------------------------
 IPluginTreePath* cpl_PluginTreeNode::GetParent() {
    return this->nodeData.parent;
}

 //-----------------------------------------------------------------------------
cpl_PluginTreeNode::cpl_PluginTreeNode() {
    memset(&this->nodeData, 0, sizeof(_fbNode_s));
    this->SetName("");
    this->SetPath("");
}

//-----------------------------------------------------------------------------
cpl_PluginTreeNode::cpl_PluginTreeNode(cpl_PluginTreePath* parent) {
    memset(&this->nodeData, 0, sizeof(_fbNode_s));
    this->nodeData.parent = parent;
    this->SetName("");
    this->SetPath("");
}

//-----------------------------------------------------------------------------
cpl_PluginTreeNode::~cpl_PluginTreeNode() {
    if (this->nodeData.name != NULL) {
        delete[] this->nodeData.name;
        this->nodeData.name = NULL;
    }
    if (this->nodeData.path != NULL) {
        delete[] this->nodeData.path;
        this->nodeData.path = NULL;
    }
}
