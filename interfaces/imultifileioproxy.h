#ifndef MULTIFILEIOPROXYINTERFACE_H
#define MULTIFILEIOPROXYINTERFACE_H

class IMultiFileIOProxy {

public:
    /** open file. */
    virtual int OpenFile() = 0;  

    /** open file. */
    virtual int OpenFile(char* szFilter) = 0;  
    
    /** Filt file name */
    virtual int FiltFileName(char* fname) = 0;
    
    /** get file name num*/
    virtual int GetFileNum() = 0;

    /** get file name */
    virtual const char* GetFileName(int num) = 0;

    /** get file full name */
    virtual const char* GetFileFullName(int num) = 0;
};

#endif //MULTIFILEIOPROXYINTERFACE_H

