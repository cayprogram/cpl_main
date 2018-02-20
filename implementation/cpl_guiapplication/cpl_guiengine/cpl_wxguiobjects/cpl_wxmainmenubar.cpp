#include "cpl_wxguiobjectincludes.h"
#include <tinyxml.h>

//local includes.
#include "cpl_wxmainmenubar.h"


//-----------------------------------------------------------------------------
// static variables: main menu path
//-----------------------------------------------------------------------------
//
static char mainMenuPath[] = "/Workbench/MainMenu";

//-----------------------------------------------------------------------------
// class cpl_wxMainMenubar
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxMenuBar* cpl_wxMainMenubar::Create() {
    //@@preconditions
    assert(this->Owner != NULL);
    assert(this->PMenubar == NULL);
    //@@end preconditions
    
    this->PMenubar = new wxMenuBar();

    // default, to avoid screen flicker.
    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ANY, "&About\tF1", "Show about dialog");
    this->PMenubar->Append(helpMenu, " ");

    //bind..
    if (this->Owner->GetMenuBar() != this->PMenubar) {
        this->Owner->SetMenuBar(this->PMenubar);
    }
    return this->PMenubar;
}

//-----------------------------------------------------------------------------
void cpl_wxMainMenubar::Update(const char* hint) {
    //@@preconditions
    assert(this->PMenubar != NULL);
    //@@end preconditions

    if (this->mainMenu != NULL) {
        this->CleanupMenuLinksByNestMenu(this->mainMenu);
        delete this->mainMenu;
        this->mainMenu = NULL;
    }    
    this->mainMenu = new cpl_SubMenu;
    this->mainMenu->Allocate(4, 4);
    this->mainMenu->SetText("mainMenu");
    this->CreateNestMenuItem(hint, mainMenuPath, this->mainMenu);

    //update wxMenu.
    wxMenu* PMenu = new wxMenu();
    this->GetMenuItemFromSubMenu(this->mainMenu, PMenu);

    //bind.
    if (PMenu->GetMenuItemCount()) {
        wxMenuItem** pitems = new wxMenuItem* [PMenu->GetMenuItemCount()];
        wxMenuItemList menuList = PMenu->GetMenuItems();
        int count = 0;
        for (int i = 0; i < menuList.size(); i++) {       
            if (menuList[i]->IsSubMenu()) {
                pitems[count] = menuList[i];
                count++;
            }            
        }

        //avoid flicker.
        this->PMenubar->Freeze();
        while (this->PMenubar->GetMenuCount() > 0) {
            delete this->PMenubar->Remove(0);
        }        
        for (int i = 0; i < count-1; i++) {    
            PMenu->Remove(pitems[i]);        
            this->PMenubar->Append(menuList[i]->GetSubMenu(), menuList[i]->GetItemLabel());
        }
        this->PMenubar->Thaw();
        PMenu->Remove(pitems[count-1]);        
        this->PMenubar->Append(menuList[count-1]->GetSubMenu(), menuList[count-1]->GetItemLabel());
        delete[] pitems;
    }
    delete PMenu;
    PMenu = NULL;

    //bind..
    if (this->Owner->GetMenuBar() != this->PMenubar) {
        this->Owner->SetMenuBar(this->PMenubar);
    }
}

//-----------------------------------------------------------------------------
int cpl_wxMainMenubar::GetMenuItemFromSubMenu(cpl_SubMenu* pAction, wxMenu* xmenu) {
    //@@preconditions
    assert(pAction != NULL);
    assert(xmenu != NULL);
    //@@end preconditions

    int numItem = pAction->GetNumberOfSubActions();
    for (int i = 0; i < numItem ; i++) {
        cpl_Action* subAction = pAction->GetAction(i);      
        subAction->SetUserData(this);
        if (subAction->IsComposite()) {
            wxMenu* _subMenu = new wxMenu();
            this->GetMenuItemFromSubMenu((cpl_SubMenu*)subAction, _subMenu);
            xmenu->AppendSubMenu(_subMenu, subAction->GetText());
        }
        else {     
            wxString label = wxT(subAction->GetText());
            wxString shortcut = (subAction->GetShortCut() == NULL)? wxEmptyString: wxT(subAction->GetShortCut());

            wxMenuItem* _newItem = NULL;                
            if (subAction->GetType() != 0) {
                _newItem = new wxMenuItem(xmenu, wxID_ANY, label+wxT('\t')+shortcut, subAction->GetText(), wxITEM_CHECK);
                 xmenu->Append(_newItem);
                _newItem->Check(subAction->GetChecked());
            }
            else {
                _newItem = new wxMenuItem(xmenu, wxID_ANY, label+wxT('\t')+shortcut, subAction->GetText(), wxITEM_NORMAL);
                xmenu->Append(_newItem);
            }

            if (subAction->GetIconId()) {
                wxBitmap iconBitmap = this->Owner->GetIcon(subAction->GetIconId());
                _newItem->SetBitmap(iconBitmap);
            }

            this->Owner->Bind(wxEVT_UPDATE_UI, &cpl_wxMainMenubar::OnUpdateUICallback, this, _newItem->GetId(), _newItem->GetId());
            this->Owner->Bind(wxEVT_COMMAND_MENU_SELECTED, &cpl_wxMainMenubar::OnCommandCallback, this, _newItem->GetId(), _newItem->GetId());
            subAction->SetCommandId(_newItem->GetId());
            if (subAction->GetDivider()) {
                xmenu->AppendSeparator();
            }
        }        
    }

    return 0;
}

//-----------------------------------------------------------------------------
void cpl_wxMainMenubar::ConvertCodonIntoMenu(IPluginCodon* codon, cpl_MenuItem* menuItem) {
    //@@preconditions
    assert(codon != NULL);
    assert(menuItem != NULL);
    //@@end preconditions

    const char* value = codon->GetName();
    if (value != NULL) {
        if (strcmp(value, "SubMenu") == 0) {
            menuItem->SetCommandId(-1);
        }
    }
    const char* type = codon->GetAttribute("type");
    if (type != NULL) {
        if (strcmp(type, "toggle") == 0) {
            menuItem->SetType(1);
        }
        else {
            menuItem->SetType(0);
        }
    }    

    const char* divider = codon->GetAttribute("divider");
    if (divider != NULL) {
        menuItem->SetDivider(1);        
    }   
    else {
        menuItem->SetDivider(0);  
    }  

    const char* domainInfo = codon->GetAttribute("domain");
    if (domainInfo != NULL) {
        menuItem->SetDomain(domainInfo);
    }

    const char* shortInfo = codon->GetAttribute("shortcut");
    if (shortInfo != NULL) {
        menuItem->SetShortCut(shortInfo);
    }

    //set icon
    const char * iconId = codon->GetAttribute("icon");
    if (iconId != NULL && iconId[0] != 0) {
        menuItem->SetIconId(iconId);
    }
}

//-----------------------------------------------------------------------------
int cpl_wxMainMenubar::CreateNestMenuItem(const char* hint, char* path, cpl_SubMenu* menu) {
    //@@preconditions
    assert(menu != NULL);
    assert(path != NULL);
    assert(this->Owner != NULL);
    //@@end preconditions

    IPluginTree* pluginTreeHandler = this->Owner->GetPluginTree();
    assert(pluginTreeHandler);

    IPluginTreePath* treepath = pluginTreeHandler->GetTreePath(path);
    if (treepath == NULL) {
        return 0;
    }

    int count = 0;
    int numItem = treepath->GetNumberOfItems();
    for (int i = 0; i < numItem; i++) {
        IPluginTreeNode* node = treepath->GetItem(i);
        if (node->IsComposite()) {
#ifdef _DEBUGA
            printf("node %s %s\n", node->GetName(), node->GetPath());
#endif
            continue;
        }
        IPluginCodon* codon = node->GetCodon();
        assert(codon != NULL);

        const char* label = codon->GetAttribute("label");
        const char* id    = codon->GetId();
        assert(id != NULL);
        
        char text[1024];
        sprintf(text, "%s/%s", path, id);

        cpl_SubMenu* subMenu = new cpl_SubMenu;
        subMenu->Allocate(4, 4);
        subMenu->SetText(label);
        subMenu->SetStringId(id);
        count++;

        int nextcount = this->CreateNestMenuItem(hint,text, subMenu);
        if (nextcount == 0) {
            delete subMenu;
            cpl_MenuItem * menuItem = new cpl_MenuItem();
            menuItem->SetText(label);
            menuItem->SetStringId(id);
            menuItem->SetComposite(menu);
            this->ConvertCodonIntoMenu(codon, menuItem);
            if (menuItem->GetDomain() == NULL) {
                menu->InsertNextItem(menuItem);
                continue;
            }
            if (hint != NULL && cpl_SystemTools::RegExpressMatch(hint, menuItem->GetDomain()) ) {
                menu->InsertNextItem(menuItem);
                if (menuItem->GetType() != 0) {
                    this->GetCheckButtonState(menuItem);
                }
                continue;
            }
            count--;
            delete menuItem;
        }
        else {
            this->ConvertCodonIntoMenu(codon, subMenu);
            if (subMenu->GetNumberOfNestSubActions() > 0) {
                if (subMenu->GetDomain() == NULL) {
                    menu->InsertNextItem(subMenu);
                    subMenu->SetComposite(menu);
                    count++;
                    continue;
                }
                if (hint != NULL && cpl_SystemTools::RegExpressMatch(hint, subMenu->GetDomain()) ) {
                    menu->InsertNextItem(subMenu);
                    subMenu->SetComposite(menu);
                    count++;
                    continue;
                }
            }
            count--;
            delete subMenu;
        }
    }
    return count;
}

//-----------------------------------------------------------------------------
void cpl_wxMainMenubar::OnCommandCallback(wxCommandEvent & evt) {
    //@@preconditions
    assert(this->mainMenu != NULL);
    //@@end preconditions

    cpl_Action* action = this->mainMenu->FindSpecificItem(evt.GetId());
    assert(action != NULL);

    cpl_Action* handler = NULL;
    this->Owner->GetMainScriptHandler(handler);
    assert(handler != NULL);

    char text[256];
    sprintf(text, "@%s",action->GetStringId()); 
    handler->SetText(text);
    handler->Execute();
}

//-----------------------------------------------------------------------------
void cpl_wxMainMenubar::OnUpdateUICallback(wxUpdateUIEvent & evt) {
    //@@preconditions
    assert(this->mainMenu != NULL);
    //@@end preconditions

    cpl_Action* action = this->mainMenu->FindSpecificItem(evt.GetId());
    assert(action != NULL);

    if (action->GetType() != 0) {
       int state = this->GetCheckButtonState(action);
       if (state == -1) {
           evt.Check(false);
       }
       if (state == 1) {
           evt.Check(true);
       }
    }
}

//-----------------------------------------------------------------------------
int cpl_wxMainMenubar::GetCheckButtonState(cpl_MenuItem* item) {
    //@@preconditions
    assert(item != NULL);
    assert(item->GetType() != 0);
    //@@end preconditions

    cpl_Action* handler = NULL;
    this->Owner->GetMainScriptHandler(handler);
    assert(handler != NULL);

    char text[256];
    sprintf(text, "*%s_check",item->GetStringId()); 
    handler->SetText(text);
    int state = handler->Execute();
    if (state == -999) { //error.
        assert(0);
    }
    else {
        assert(state == -1 || state == 1);
        item->SetChecked((state==-1)?(0):(1));
    }
    return state;
}

//-----------------------------------------------------------------------------
void cpl_wxMainMenubar::CleanupMenuLinksByNestMenu(cpl_SubMenu* pAction) {
    //@@preconditions
    assert(pAction != NULL);
    //@@end preconditions

    int numItem = pAction->GetNumberOfSubActions();
    for (int i = 0; i < numItem ; i++) {
        cpl_Action* subAction = pAction->GetAction(i);
        assert(subAction != NULL);

        int id = subAction->GetCommandId();
        if (id > 0) {
            this->Owner->Unbind(wxEVT_UPDATE_UI, &cpl_wxMainMenubar::OnUpdateUICallback, this, id, id);
            this->Owner->Unbind(wxEVT_COMMAND_MENU_SELECTED, &cpl_wxMainMenubar::OnCommandCallback, this, id, id);
        }
        if (subAction->IsComposite() == 1) {
            this->CleanupMenuLinksByNestMenu((cpl_SubMenu*)subAction);
        }
    }
}

//-----------------------------------------------------------------------------
cpl_wxMainMenubar::cpl_wxMainMenubar(cpl_wxMainFrame* pOwner) : Owner(pOwner), PMenubar(0), mainMenu(0) {
}

//-----------------------------------------------------------------------------
cpl_wxMainMenubar::~cpl_wxMainMenubar() {
    if (this->mainMenu != NULL) {
        this->CleanupMenuLinksByNestMenu(this->mainMenu);
        delete this->mainMenu;
        this->mainMenu = NULL;
    }
}
