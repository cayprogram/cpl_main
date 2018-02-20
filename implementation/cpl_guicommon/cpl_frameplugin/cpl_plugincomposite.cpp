#include "cpl_pluginframeincludes.h"

//@@standard macro.
CPL_StandardNewCommandMacro(cpl_CompositePlugin);

//-------------------------------------------------------------------------
// class cpl_CompositePlugin
//-------------------------------------------------------------------------
//

//-------------------------------------------------------------------------
cpl_CompositePlugin::cpl_CompositePlugin() : cpl_Plugin(NULL) {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-------------------------------------------------------------------------
cpl_CompositePlugin::cpl_CompositePlugin(cpl_CompositePlugin * pWidget) : cpl_Plugin(pWidget)  {
    this->Array = NULL;
    this->MaxId =-1;
    this->Size  = 0;
    this->Extend= 10;
}

//-------------------------------------------------------------------------
cpl_CompositePlugin::~cpl_CompositePlugin() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].PluginItem != NULL) {
                this->Array[i].PluginItem->Release();
                this->Array[i].PluginItem = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::Allocate(int sz, int ext) {
    //@@preconditions
    assert(sz > 0);
    assert(ext> 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].PluginItem != NULL) {
                    this->Array[i].PluginItem->Release();
                    this->Array[i].PluginItem = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new _fbPluginItem_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].PluginItem = NULL;
             this->Array[i].resourceId = 0;
        }
    }
    this->Extend = (ext > 0 ? ext : 1);
    this->MaxId = -1;

    return 1;
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::InsertNextItem(cpl_Plugin* plugin) {    
    //@@preconditons
    assert(plugin != NULL);
    //@@end preconditions

    this->InsertItem(++this->MaxId, plugin);
    return this->MaxId;
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::RemoveItem(cpl_Plugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int PluginId = -1;
    for (int i = 0; i < this->MaxId; i++) {
        if (this->Array[i].PluginItem == plugin) {
            PluginId = i;
            break;
        }
    }
    assert(PluginId != -1);

    //exchange position between lnId and MaxId, note: widget is not delete.
    if (PluginId != this->MaxId) {
        this->Array[PluginId] = this->Array[this->MaxId];
    }
    this->MaxId--;

    return this->MaxId;
}
    
//-------------------------------------------------------------------------
int cpl_CompositePlugin::RemoveAllItems(){
    for (int i = 0; i < this->MaxId; i++) {
        if (this->Array[i].PluginItem != NULL) {
            this->Array[i].PluginItem->Release();
            this->Array[i].PluginItem = NULL;
        }
    }
    this->MaxId = -1;
    return 1;
}

//-------------------------------------------------------------------------
void cpl_CompositePlugin::InsertItem(int pos, cpl_Plugin* plugin) {
    //@@preconditions
    assert(pos >= 0);
    assert(plugin != NULL);
    //@@end preconditions

    _fbPluginItem_s * plugins;
    if (pos >= this->Size) {
        this->Reallocate(pos + 1);
    }
    if (pos > this->MaxId) {
        this->MaxId = pos;
    }

    plugins = this->Array + pos;
    assert(plugins != NULL);

    plugins->PluginItem = plugin;
    plugins->resourceId = 0;

    //set as parent.
    plugins->PluginItem->SetParent(this);

    return;
}
 
//-------------------------------------------------------------------------
cpl_CompositePlugin::_fbPluginItem_s* cpl_CompositePlugin::Reallocate(int sz) {
    //@@preconditions
    assert(sz > 0);
    //@@end preconditions

    int newSize = 0;
    if (sz >= this->Size) {
        newSize = this->Size + sz;
    }
    else {
        assert(0);
        newSize = sz;
    }

    cpl_CompositePlugin::_fbPluginItem_s * newArray = new cpl_CompositePlugin::_fbPluginItem_s[newSize];
    for (int j = 0; j < newSize; j++) {
        newArray[j].PluginItem = NULL;
        newArray[j].resourceId = 0;
    }

    for (int i = 0; i < sz && i < this->Size; i++) {
        newArray[i].PluginItem = this->Array[i].PluginItem;
        newArray[i].resourceId = this->Array[i].resourceId;
    }
    this->Size = newSize;
    delete[] this->Array;
    this->Array = newArray;
    return this->Array;
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNumberOfNestPlugins() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItem(this);
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNumberOfNestPluginsRequireLib() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItemRequireLib(this);
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNumberOfNestPluginsDLL() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItemDLL(this);
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNumberOfNestPluginsZScript() {
    //@@preconditions
    //@@end preconditions

    return this->GetNestSubItemZScript(this);
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNestSubItem(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);

        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItem((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            count++;
        }        
    }
    return count;
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNestSubItemRequireLib(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);

        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItemRequireLib((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            cpl_StringCollection* collection = sub_plugin->GetRequireLibs();
            if (collection != NULL) {                
                count += collection->GetNumberOfItem();
            }
        }        
    }
    return count;
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNestSubItemDLL(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);
        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItemDLL((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            cpl_StringCollection* collection = sub_plugin->GetDynamicFactories();
            if (collection != NULL) {                
                count += collection->GetNumberOfItem();
            }
        }        
    }
    return count;
}

//-------------------------------------------------------------------------
int cpl_CompositePlugin::GetNestSubItemZScript(cpl_CompositePlugin* plugin) {
    //@@preconditions
    assert(plugin != NULL);
    //@@end preconditions

    int count = 0;
    int numItem = plugin->GetNumberOfPlugins();
    for (int i = 0; i < numItem ; i++) {
        cpl_Plugin* sub_plugin = plugin->GetPlugin(i);
        assert(sub_plugin != NULL);

        if (sub_plugin->IsComposite() == 1) {
            count += this->GetNestSubItemZScript((cpl_CompositePlugin*)sub_plugin);
        }
        else {
            cpl_StringCollection* collection = sub_plugin->GetZScriptLibs();
            if (collection != NULL) {                
                count += collection->GetNumberOfItem();
            }
        }        
    }
    return count;
}
