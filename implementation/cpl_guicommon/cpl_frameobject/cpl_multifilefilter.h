#ifndef CPL_MULTIFILEFILT_H
#define CPL_MULTIFILEFILT_H

//predefinitions.
#define MAX_FILT_NUMBER 100

class cpl_MultiFileFilter {

public:
    /** convert filename into MultiFilt */    
    static void FileFilter(char* pfname);

    /** get filename. */
    static char* GetFileName(int index);

    /** get filepath. */
    static char* GetFilePath(int index);

    /** get fileext */
    static char* GetFileExt(int index);

    /** get file fullname */
    static char* GetFileFullName(int index);

    /** get the file exist.*/
    static int   GetFileExist(int index);

    /** contain path */
    static int IsContainPath(char* pfname);

    /** get the number of filter */
    static int Getnumber();

    /** rest multifilter */
    static void CleanupFilt();

private:
    static int number;

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
    }MultiFilt;

    //constructor.
    cpl_MultiFileFilter() {}

    //destructor.
    virtual ~cpl_MultiFileFilter() {}

    //cleanup filters
    static void CleanupFilt(int index);

    //protected variables
    static MultiFilt filters[MAX_FILT_NUMBER];
};

#endif // CPL_MULTIFILEFILT_H
