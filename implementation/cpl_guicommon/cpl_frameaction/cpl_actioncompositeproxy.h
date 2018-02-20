#ifndef CPL_ACTIONCOMPOSITEPROXY_H
#define CPL_ACTIONCOMPOSITEPROXY_H

class cpl_ActionCompositeProxy {

public:
    /** set composite action as root action (root menu) */
    virtual void SetRoot(cpl_ActionComposite* pAction);

    /** get root composite action */
    virtual cpl_ActionComposite* GetRoot();

    /** get current composite action */
    virtual cpl_ActionComposite* GetCurrent();
    
public:
    //constructor.
    cpl_ActionCompositeProxy();

    //destructor,
    virtual ~cpl_ActionCompositeProxy();

protected:
    //protect function.
    void SetCurrent(cpl_ActionComposite* pAction);

    //protect variables.
    cpl_ActionComposite* current;
    cpl_ActionComposite* root;
};

#endif //CPL_ACTIONCOMPOSITEPROXY_H

