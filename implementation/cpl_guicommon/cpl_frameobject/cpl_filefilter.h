#ifndef CPL_FILEFILTER_H
#define CPL_FILEFILTER_H

class cpl_FileFilter {

public:
    /** convert filename into Filt */    
    static void FileFilter(char* pfname);

    /** get filename. */
    static char* GetFileName();

    /** get filepath. */
    static char* GetFilePath();

    /** get fileext */
    static char* GetFileExt();

    /** get file fullname */
    static char* GetFileFullName();

    /** get the file exist.*/
    static int   GetFileExist();

    /** contain path */
    static int   IsContainPath(char* pfname);

protected:
    enum { MAX_STRING_LEN = 1024 };

    typedef struct {
        char pCharName[MAX_STRING_LEN];
        char pCharPath[MAX_STRING_LEN];
        char pCharPath_slashed[MAX_STRING_LEN];
        char pCharExt[MAX_STRING_LEN];
        char pCharFull[MAX_STRING_LEN];
        int Exists;
        int Flen;
    } Filt;

    //constructor.
    cpl_FileFilter() {}

    //destructor.
    virtual ~cpl_FileFilter() {}

    //cleanup filt
    static void CleanupFilt();

    //protected variables
    static Filt filter;
};

#endif // CPL_FILEFILTER_H
