#ifndef CPL_CONTROLLEROBJECTFACTORY_H
#define CPL_CONTROLLEROBJECTFACTORY_H

class cpl_ControllerObjectFactory {

public:
    /** Create controller manager */
    virtual cpl_ControllerManager* CreateControlManager() = 0;

public:
    /** create Instance */
    static cpl_ControllerObjectFactory * Instance();

    /** Release */
    static void Delete();

    /** set instance. */
    static void SetFactory(cpl_ControllerObjectFactory* factory);

protected:
    //constructor.
    cpl_ControllerObjectFactory();

    //destructor
    virtual ~cpl_ControllerObjectFactory();

private:
    // private instance
    static cpl_ControllerObjectFactory * instance;
};

#endif //CPL_CONTROLLEROBJECTFACTORY_H

