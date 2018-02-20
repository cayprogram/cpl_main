#ifndef CPL_WXMAINNORMALTOOLBAR_H
#define CPL_WXMAINNORMALTOOLBAR_H

class cpl_wxMainNormalToolbar : public cpl_wxMainToolbar {

public:
    // create.
    virtual wxPanel* Create(int w, int h);

private:
    wxToolBar * CreateToolbar();

public:
    cpl_wxMainNormalToolbar(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainNormalToolbar();
};

#endif //CPL_WXMAINNORMALTOOLBAR_H
