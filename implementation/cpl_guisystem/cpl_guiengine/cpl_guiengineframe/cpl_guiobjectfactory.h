#ifndef CPL_GUIOBJECTFACTORY_H
#define CPL_GUIOBJECTFACTORY_H

class cpl_GUIObjectFactory {

public:
    /** Create GUI engine implementation.*/
    virtual cpl_GUIEngineImp* CreateGUIEngineImp() = 0;

    /** Create main window implementation.*/
    virtual cpl_MainWindowImp* CreateMainWindowImp(cpl_MainWindow* pOwner) = 0;
   
public:
    /** create Instance */
    static cpl_GUIObjectFactory * Instance();

    /** Release */
    static void Delete();

    /** set instance. */
    static void SetFactory(cpl_GUIObjectFactory* factory);

protected:
    //constructor.
    cpl_GUIObjectFactory();

    //destructor
    virtual ~cpl_GUIObjectFactory();

private:
    // private instance
    static cpl_GUIObjectFactory * instance;
};

#endif //CPL_GUIOBJECTFACTORY_H
