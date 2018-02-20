#ifndef CPL_WXMAINTOOLBAR_H
#define CPL_WXMAINTOOLBAR_H

class cpl_wxMainToolbar {

public:
    // create.
    virtual wxPanel* Create(int w, int h) = 0;

public:
    // Constructor.
    cpl_wxMainToolbar(cpl_wxMainFrame* pOwner);

    // Destructor
    virtual ~cpl_wxMainToolbar();

protected:
    //owner.
    cpl_wxMainFrame* Owner;

    //raw pointer.
    wxPanel* PPanel;        //parent container

    int  tbBOXw;
    int  tbBOXh;
};

#endif //CPL_WXMAINTOOLBAR_H
