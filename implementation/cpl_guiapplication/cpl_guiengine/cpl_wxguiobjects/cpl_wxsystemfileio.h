#ifndef CPL_WXSYSTEMFILEIO_H
#define CPL_WXSYSTEMFILEIO_H

class cpl_wxSystemFileIO: public cpl_SystemFileIO {

public:
    /** open default file. */
    virtual int OpenFile();

    /** open file with selected type returned . */
    virtual int OpenFile(char* szFilter, int &iFileType); 

    /** save file. */
    virtual int SaveFile(char* szFilter, int& iFileType);

    /** open directory*/
    virtual int OpenDirectory();

    /** save directory*/
    virtual int SaveDirectory();

public:
    friend class cpl_SystemFileIO;

    /** default constructor */
    cpl_wxSystemFileIO() {}

    /** destructor */
    virtual ~cpl_wxSystemFileIO() {}
};

#endif // CPL_WXSYSTEMFILEIO_H
