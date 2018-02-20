#ifndef CPL_CONTROLLER_H
#define CPL_CONTROLLER_H

class cpl_Controller : public cpl_Object {

public:
    /** create function */
    static cpl_Controller * New();

public:
    /** Set ControllerManager */
    virtual void SetControllerManager(cpl_ControllerManager* manager);

    /** Initialize window.*/
    virtual void DoInitialization() {}

    /** Do clean up */
    virtual void DoCleanup() {}

protected:        
    //constructor.
    cpl_Controller();

    //destructor
    virtual ~cpl_Controller();

    cpl_ControllerManager* pOwner;
};

#endif //CPL_CONTROLLER_H
