#ifndef CPL_WXSYSTEMMULTIFILEIO_H
#define CPL_WXSYSTEMMULTIFILEIO_H

class cpl_wxSystemMultiFileIO: public cpl_SystemMultiFileIO {

public:
    /** open default file. */
    virtual int OpenFile();

    /** open file. */
    virtual int OpenFile(char* szFilter);  

public:
    friend class cpl_SystemMultiFileIO;

    /** default constructor */
    cpl_wxSystemMultiFileIO() {}

    /** destructor */
    virtual ~cpl_wxSystemMultiFileIO() {}
};

#endif // CPL_WXSYSTEMMULTIFILEIO_H
