#ifndef CPL_SYSTEMFILEIO_H
#define CPL_SYSTEMFILEIO_H

class cpl_SystemFileIO {
public:
    /** create functions*/
    static cpl_SystemFileIO * Instance();

    /** Release */
    static void Delete();

    /** set instance. */
    static void SetInstance(cpl_SystemFileIO* instance);

    /** open default file. */
    virtual int OpenFile(){ return 0; }
    
    /** open file with selected file type returned. */
    virtual int OpenFile(char* szFilter, int& iFileType) {return 0; } 

    /** save file. */
    virtual int SaveFile(char* szFilter, int& iFileType) {return 0; }
    
    /** open directory*/
    virtual int OpenDirectory() { return 0; }

    /** save directory*/
    virtual int SaveDirectory() { return 0; }

protected:
    /** default constructor */
    cpl_SystemFileIO() {}

    /** destructor */
    virtual ~cpl_SystemFileIO();

    /* private instance */
    static cpl_SystemFileIO * instance;
};

#endif // CPL_SYSTEMFILEIO_H
