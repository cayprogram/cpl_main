#ifndef CPL_MULTIFILEIOPROXY_H
#define CPL_MULTIFILEIOPROXY_H

class cpl_MultiFileIOController : public cpl_Controller {

public:
    /** create instance */
    static cpl_MultiFileIOController* New();

public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

public:
    /** get implementation */
    IMultiFileIOProxy* GetImplementation();

protected:        
    //constructor.
    cpl_MultiFileIOController();

    //destructor
    virtual ~cpl_MultiFileIOController();
    
    //implementation.
    class Impl;
    Impl* Implementaion;
};

#endif //CPL_MULTIFILEIOPROXY_H
