#ifndef CPL_SESSIONPROXY_H
#define CPL_SESSIONPROXY_H

class cpl_SessionProxy : public cpl_Controller {

public:
    /** create instance */
    static cpl_SessionProxy* New();

public:
    /** Initialize */
    virtual void DoInitialization();

    /** do clean up*/
    virtual void DoCleanup();

public:
    /** get implementation */
    ISessionProxy* GetImplementation();

protected:
    //constructor
    cpl_SessionProxy();

    //destructor
    virtual ~cpl_SessionProxy();

    //implementation.
    ISessionProxy* Implementaion;
};

#endif //CPL_SESSIONPROXY_H