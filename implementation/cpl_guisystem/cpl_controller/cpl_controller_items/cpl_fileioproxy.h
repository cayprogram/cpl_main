#ifndef CPL_FILEIOPROXY_H
#define CPL_FILEIOPROXY_H

class cpl_FileIOController : public cpl_Controller {

public:
    /** create instance */
    static cpl_FileIOController* New();

public:
    /** Initialize window.*/
    virtual void DoInitialization();

    /** Do clean up */
    virtual void DoCleanup();

public:
    /** get implementation */
    IFileIOProxy* GetImplementation();

protected:        
    //constructor.
    cpl_FileIOController();

    //destructor
    virtual ~cpl_FileIOController();
    
    //implementation.
    class Impl;
    Impl* Implementaion;
};

#endif //CPL_FILEIOPROXY_H
