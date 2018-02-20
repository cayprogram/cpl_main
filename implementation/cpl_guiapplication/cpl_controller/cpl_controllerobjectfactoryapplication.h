#ifndef CPL_APPLICATIONCONTROLLEROBJECTFACTORY_H
#define CPL_APPLICATIONCONTROLLEROBJECTFACTORY_H

class cpl_ApplicationControllerObjectFactory : public cpl_ControllerObjectFactory {
public:    
    /** Create controller manager */
    virtual cpl_ControllerManager* CreateControlManager();

public:
    //constructor.
    cpl_ApplicationControllerObjectFactory();

    //destructor
    virtual ~cpl_ApplicationControllerObjectFactory();
};

#endif //CPL_APPLICATIONCONTROLLEROBJECTFACTORY_H

