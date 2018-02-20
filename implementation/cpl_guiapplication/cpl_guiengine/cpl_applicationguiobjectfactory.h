#ifndef CPL_APPLICATIONGUIOBJECTFACTORY_H
#define CPL_APPLICATIONGUIOBJECTFACTORY_H

class cpl_ApplicationGUIObjectFactory: public cpl_GUIObjectFactory {

public:
    /** Create GUI Engine Imp.*/
    virtual cpl_GUIEngineImp* CreateGUIEngineImp();

    /** Create Main Window Imp.*/
    virtual cpl_MainWindowImp* CreateMainWindowImp(cpl_MainWindow* pOwner);

public:
    //constructor.
    cpl_ApplicationGUIObjectFactory();

    //destructor
    virtual ~cpl_ApplicationGUIObjectFactory();
};

#endif //CPL_APPLICATIONGUIOBJECTFACTORY_H
