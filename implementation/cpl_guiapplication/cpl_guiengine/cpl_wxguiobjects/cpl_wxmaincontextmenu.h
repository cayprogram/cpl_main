#ifndef CPL_WXMAINCONTEXTMENU_H
#define CPL_WXMAINCONTEXTMENU_H

//-----------------------------------------------------------------------------
//class cpl_wxMainContextMenu
//-----------------------------------------------------------------------------
//
class cpl_wxMainContextMenu {

public:
    // create.
    void Create();

    // update menu according to hint.
    void Update(const char* hint);

    // get update menu
    wxMenu* GetMenu();

public:
    cpl_wxMainContextMenu(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainContextMenu();

private:
    //owner.
    cpl_wxMainFrame* Owner;

    //wxwidgets.
    wxMenu* PMenu;

    //menu
    cpl_SubMenu* mainMenu;

    //command callback
    void OnCommandCallback(wxCommandEvent & evt);
    void OnUpdateUICallback(wxUpdateUIEvent& evt);

    //get check button state.
    int GetCheckButtonState(cpl_MenuItem* item);

    //create nest menu item.
    int GetMenuItemFromSubMenu(cpl_SubMenu* menu, wxMenu* rootMenu, wxMenu* xMenu);
    int CreateNestMenuItem(const char* hint, char* path, cpl_SubMenu* menu);

    //..
    void ConvertCodonIntoMenu(IPluginCodon* codon, cpl_MenuItem* menuItem);    

    //cleanup menu link
    void CleanupMenuLinksByNestMenu(cpl_SubMenu* menu);
};

#endif //CPL_WXMAINCONTEXTMENU_H
