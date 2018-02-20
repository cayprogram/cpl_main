#include <cpl_controller/cpl_controllerframeincludes.h>

//local includes.
#include "cpl_fileioproxy.h"

//-----------------------------------------------------------------------------
// class cpl_FileIOController::Impl
//-----------------------------------------------------------------------------
//
class cpl_FileIOController::Impl : public IFileIOProxy {

public:    
    /** Open file. */
    virtual int OpenFile();  
   
    /** open file . */
    virtual int OpenFile(char* szFilter);

    /** open file with selected type returned. */
    virtual int OpenFile(char* szFilter, int & iFileType);

    /** open directory*/
    virtual int OpenDirectory();

    /** save file. */
    virtual int SaveFile(char* szFilter);

    /** save file. */
    virtual int SaveFile(char* szFilter, int & iFileType);

    /** save directory*/
    virtual int SaveDirectory();

    /** set work directory */
    virtual int SetWorkDirectory(char dir[]) { return 0; }
    
    /** get work directory */
    virtual int GetWorkDirectory(char dir[]);

public:    
    /** Filt file name */
    virtual int FiltFileName(char* fname);
        
    /** get file name */
    virtual const char* GetFileName();
    
    /** get file full name */
    virtual const char* GetFileFullName();

    /** get file extend name */
    virtual const char* GetFileExt();
    
public:
    //constructor.
    Impl() {}
    
    //destructor
    virtual ~Impl();
};

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::OpenFile() {
    return cpl_SystemFileIO::Instance()->OpenFile();        
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::OpenFile(char* szFilter) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions

    int iFileType = cpl_SystemConfig::Instance()->GetFileOpenType();
    return cpl_SystemFileIO::Instance()->OpenFile(szFilter, iFileType);        
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::OpenFile(char* szFilter, int & iFileType) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions

    return cpl_SystemFileIO::Instance()->OpenFile(szFilter, iFileType);        
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::OpenDirectory() {
    return cpl_SystemFileIO::Instance()->OpenDirectory();
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::SaveFile(char* szFilter) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions

    int iFileType = 0;
    return cpl_SystemFileIO::Instance()->SaveFile(szFilter, iFileType);  
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::SaveFile(char* szFilter, int & iFileType) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions
    
    return cpl_SystemFileIO::Instance()->SaveFile(szFilter, iFileType);  
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::SaveDirectory() {
    return cpl_SystemFileIO::Instance()->SaveDirectory();
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::GetWorkDirectory(char dir[]) {    
    const char* path = NULL;
    cpl_SystemConfig::Instance()->GetWorkDirectory(path);
    if (path != NULL&& cpl_SystemTools::IsDirectoryExist(path)) {
        strcpy(dir, path);
        cpl_SystemTools::ConvertWindowsPathToUnix(dir);
        return 1;
    }
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_FileIOController::Impl::FiltFileName(char* fname) {
    //@@preconditions
    assert(fname != NULL);
    //@@end preconditions

    cpl_FileFilter::FileFilter(fname);
    return 1;
}

//-----------------------------------------------------------------------------
const char* cpl_FileIOController::Impl::GetFileName() {
    return cpl_FileFilter::GetFileName();
}

//-----------------------------------------------------------------------------
const char* cpl_FileIOController::Impl::GetFileFullName() {
    return cpl_FileFilter::GetFileFullName();
}

//-----------------------------------------------------------------------------
const char* cpl_FileIOController::Impl::GetFileExt() {
    return cpl_FileFilter::GetFileExt();
}

//-----------------------------------------------------------------------------
cpl_FileIOController::Impl::~Impl() {
}

//-----------------------------------------------------------------------------
// class cpl_FileIOController
//-----------------------------------------------------------------------------
//
cpl_FileIOController* cpl_FileIOController::New() {
    return new cpl_FileIOController;
}

//-----------------------------------------------------------------------------
void cpl_FileIOController::DoInitialization() {
    //@@preconditions
    assert(this->Implementaion == NULL);
    //@@end preconditions

    this->Implementaion = new Impl;   
}

//-----------------------------------------------------------------------------
void cpl_FileIOController::DoCleanup() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    delete this->Implementaion;
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
IFileIOProxy* cpl_FileIOController::GetImplementation() {
    return this->Implementaion;
}

//-----------------------------------------------------------------------------
cpl_FileIOController::cpl_FileIOController() {
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
cpl_FileIOController::~cpl_FileIOController() {
    assert(this->Implementaion == NULL);
}
