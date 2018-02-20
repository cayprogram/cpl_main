#ifndef CPL_MULTISYSTEMFILEIO_H
#define CPL_MULTISYSTEMFILEIO_H

class cpl_SystemMultiFileIO {
public:
    /** create functions*/
    static cpl_SystemMultiFileIO * Instance();

    /** Release */
    static void Delete();

    /** set instance. */
    static void SetInstance(cpl_SystemMultiFileIO* instance);

    /** open default file. */
    virtual int OpenFile() { return 0; }
    
    /** open file. */
    virtual int OpenFile(char* szFilter) {return 0; }

protected:
    /** default constructor */
    cpl_SystemMultiFileIO() {}

    /** destructor */
    virtual ~cpl_SystemMultiFileIO();

    /* private instance */
    static cpl_SystemMultiFileIO * instance;
};

#endif // CPL_MULTISYSTEMFILEIO_H
