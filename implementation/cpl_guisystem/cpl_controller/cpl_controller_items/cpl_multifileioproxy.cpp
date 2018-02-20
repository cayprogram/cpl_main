#include <cpl_controller/cpl_controllerframeincludes.h>

//local includes.
#include "cpl_multifileioproxy.h"

//-----------------------------------------------------------------------------
// class cpl_MultiFileIOController
//-----------------------------------------------------------------------------
//
class cpl_MultiFileIOController::Impl : public IMultiFileIOProxy {

public:    
    /** open file. */
    virtual int OpenFile();  

    /** open file. */
    virtual int OpenFile(char* szFilter);  
    
    /** Filt file name */
    virtual int FiltFileName(char* fname);
    
    /** get file name num*/
    virtual int GetFileNum();

    /** get file name */
    virtual const char* GetFileName(int num) ;

    /** get file full name */
    virtual const char* GetFileFullName(int num);
    
public:
    //constructor.
    Impl() {}
    
    //destructor
    virtual ~Impl();
};

//-----------------------------------------------------------------------------
int cpl_MultiFileIOController::Impl::OpenFile() {
    return cpl_SystemMultiFileIO::Instance()->OpenFile();        
}

//-----------------------------------------------------------------------------
int cpl_MultiFileIOController::Impl::OpenFile(char* szFilter) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions

    return cpl_SystemMultiFileIO::Instance()->OpenFile(szFilter);        
}

//-----------------------------------------------------------------------------
int cpl_MultiFileIOController::Impl::FiltFileName(char* fname) {
    //@@preconditions
    assert(fname != NULL);
    //@@end preconditions

    cpl_MultiFileFilter::FileFilter(fname);
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_MultiFileIOController::Impl::GetFileNum() {
    return cpl_MultiFileFilter::Getnumber();
}

//-----------------------------------------------------------------------------
const char* cpl_MultiFileIOController::Impl::GetFileName(int num) {
    return cpl_MultiFileFilter::GetFileName(num);
}

//-----------------------------------------------------------------------------
const char* cpl_MultiFileIOController::Impl::GetFileFullName(int num) {
    return cpl_MultiFileFilter::GetFileFullName(num);
}

//-----------------------------------------------------------------------------
cpl_MultiFileIOController::Impl::~Impl() {
}

//-----------------------------------------------------------------------------
// class cpl_MultiFileIOController
//-----------------------------------------------------------------------------
//
cpl_MultiFileIOController* cpl_MultiFileIOController::New() {
    return new cpl_MultiFileIOController;
}

//-----------------------------------------------------------------------------
void cpl_MultiFileIOController::DoInitialization() {
    //@@preconditions
    assert(this->Implementaion == NULL);
    //@@end preconditions

    this->Implementaion = new Impl;   
}

//-----------------------------------------------------------------------------
void cpl_MultiFileIOController::DoCleanup() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    delete this->Implementaion;
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
IMultiFileIOProxy* cpl_MultiFileIOController::GetImplementation() {
    return this->Implementaion;
}

//-----------------------------------------------------------------------------
cpl_MultiFileIOController::cpl_MultiFileIOController() {
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
cpl_MultiFileIOController::~cpl_MultiFileIOController() {
    assert(this->Implementaion == NULL);
}
