#ifndef CPL_WXMAINMENUBAR_H
#define CPL_WXMAINMENUBAR_H

//-----------------------------------------------------------------------------
//class cpl_wxMainMenubar
//-----------------------------------------------------------------------------
//
class cpl_wxMainMenubar {

public:
    // create.
    wxMenuBar* Create();

    // update menu according to hint.
    void Update(const char* hint);

    //command callback
    void OnCommandCallback(wxCommandEvent & evt);
    void OnUpdateUICallback(wxUpdateUIEvent& evt);

public:
    cpl_wxMainMenubar(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainMenubar();

private:
    //owner.
    cpl_wxMainFrame* Owner;

    //raw pointer.
    wxPanel* PPanel;
    wxMenuBar* PMenubar;

    //menu
    cpl_SubMenu* mainMenu;

    //create nest menu item.
    int GetMenuItemFromSubMenu(cpl_SubMenu* menu, wxMenu* xMenu);
    int CreateNestMenuItem(const char* hint, char* path, cpl_SubMenu* menu);

    //get check button state.
    int GetCheckButtonState(cpl_MenuItem* item);

    //...
    void ConvertCodonIntoMenu(IPluginCodon* codon, cpl_MenuItem* menuItem);    

    //cleanup menu link
    void CleanupMenuLinksByNestMenu(cpl_SubMenu* menu);
};

#endif //CPL_WXMAINMENUBAR_H
