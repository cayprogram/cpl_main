#ifndef FILEIOPROXYINTERFACE_H
#define FILEIOPROXYINTERFACE_H

class IFileIOProxy {

public:
    /** open file. */
    virtual int OpenFile() = 0;  
    
    /** open file . */
    virtual int OpenFile(char* szFilter) = 0;  

    /** open file with selected type returned. */
    virtual int OpenFile(char* szFilter, int & iFileType) = 0;  
    
    /** open directory*/
    virtual int OpenDirectory() = 0;

    /** save file. */
    virtual int SaveFile(char* szFilter) = 0;

    /** save file. */
    virtual int SaveFile(char* szFilter, int & iFileType) = 0;

    /** save directory*/
    virtual int SaveDirectory() = 0;

    /** set work directory */
    virtual int SetWorkDirectory(char dir[]) = 0;
    
    /** get work directory */
    virtual int GetWorkDirectory(char dir[]) = 0;

    /** Filt file name */
    virtual int FiltFileName(char* fname) = 0;
    
    /** get file name */
    virtual const char* GetFileName() = 0;

    /** get file full name */
    virtual const char* GetFileFullName() = 0;

    /** get file extend name */
    virtual const char* GetFileExt() = 0;
};

#endif //FILEIOPROXYINTERFACE_H

