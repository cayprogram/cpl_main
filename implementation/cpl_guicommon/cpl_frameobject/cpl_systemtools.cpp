#include "cpl_frameobjectincludes.h"

#ifdef _WIN32
#include <windows.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <direct.h>
#include <shlobj.h>   
#include <Shlwapi.h>
#include <direct.h>
#include <io.h>
#else
#include <sys/time.h>
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#endif

#include <sys/types.h>
#include <time.h>

// The microsoft compiler defines this as a macro, so undefine it here
#undef GetCurrentTime

char cpl_SystemTools::CONST_SEPDIRCHAR = '/';

#define USE_PCRE

//-----------------------------------------------------------------------------
static void getMyDocument(char *dirname) {
    static char homeDir[1024] = "";
    if (strlen(homeDir) <= 0) {
        char *envvalue, *sp, str[1024] = "";
#ifdef WIN32 
        if (!SHGetSpecialFolderPath(NULL,str, CSIDL_MYDOCUMENTS, 0)) {
            envvalue = getenv("userprofile");
            if (envvalue != NULL) {
                sprintf(str,"%s\\My Documents",envvalue);
            }
            else {
                envvalue = getenv("windir");
                if (envvalue != NULL) {
                    strcpy( dirname, envvalue );
                    sp = strchr( dirname, ':' );
                    if (sp != NULL) {
                        *(sp+1) = '\0';
                        sprintf( str,"%s\\My Documents",dirname);
                    }
                    else strcpy( str, "C:\\My Documents" );
                }
                else {
                    strcpy( str, "C:\\My Documents" );
                }
            }
            if (PathIsDirectory(str) == false) {
                _mkdir( str );
            }
        }
        strcat(str, "\\Demo");
        if (PathIsDirectory(str) == false) {
            _mkdir( str );
        }
        sprintf( homeDir,"%s",str);
#else
        envvalue = getenv("HOME");
        if (envvalue != NULL) {
            sprintf( str,"%s/", envvalue );
        }
        else {
            envvalue = getenv("~");
            if (envvalue != NULL) {
                sprintf( str,"%s/", envvalue );
            }
            else {
                getcwd(str,1024);
                sprintf( str,"%s/", str );
            }
        }
        strcat( str, "Demo/");
        if (!PathIsDirectory(str)) {
            mkdir(str,0755 );
        }
        sprintf( homeDir,"%s/",str);
#endif		
    }
    strcpy(dirname, homeDir);	
}

//-----------------------------------------------------------------------------
// class cpl_SystemTools
//-----------------------------------------------------------------------------
//
void cpl_SystemTools::ConvertWindowsCommandLineToUnixArguments(const char * cmd_line, int * argc, char * * * argv) {
    if (!cmd_line || !argc || !argv) {
        return;
    }

    (* argc) = 1;
    size_t cmd_line_len = strlen(cmd_line);
    size_t i;
    for (i = 0; i < cmd_line_len; i++) {
        while (isspace(cmd_line[i]) && i < cmd_line_len) {
            i++;
        }
        if (i < cmd_line_len) {
            if (cmd_line[i] == '\"') {
                i++;
                while (cmd_line[i] != '\"' && i < cmd_line_len) {
                    i++;
                }
                (* argc) ++;
            }
            else {
                while (!isspace(cmd_line[i]) && i < cmd_line_len) {
                    i++;
                }
                (* argc) ++;
            }
        }
    }

    (* argv) = new char * [(* argc) + 1];
    (* argv) [(* argc)] = NULL;
    (* argv) [0] = new char[1024];
#ifdef _WIN32
    ::GetModuleFileName(0, (* argv) [0], 1024);
#else
    (* argv) [0] [0] = '\0';
#endif
    int  j;
    for (j = 1; j < (* argc); j++) {
        (* argv) [j] = new char[cmd_line_len + 10];
    }

    size_t pos;
    int argc_idx = 1;

    for (i = 0; i < cmd_line_len; i++) {
        while (isspace(cmd_line[i]) && i < cmd_line_len) {
            i++;
        }
        if (i < cmd_line_len) {
            if (cmd_line[i] == '\"') {
                i++;
                pos = i;
                while (cmd_line[i] != '\"' && i < cmd_line_len) {
                    i++;
                }
                memcpy((* argv) [argc_idx], & cmd_line[pos], i - pos);
                (* argv) [argc_idx] [i - pos] = '\0';
                argc_idx++;
            }
            else {
                pos = i;
                while (!isspace(cmd_line[i]) && i < cmd_line_len) {
                    i++;
                }
                memcpy((* argv) [argc_idx], & cmd_line[pos], i - pos);
                (* argv) [argc_idx] [i - pos] = '\0';
                argc_idx++;
            }
        }
    }
}

//-----------------------------------------------------------------------------
void cpl_SystemTools::ConvertWindowsPathToUnix(char* path) {
    if (NULL == path)
        return;

    int i = 0 ;
    while (path[i] != 0){
        if ('\\' == path[i]) path[i] = '/' ;
        i++ ;
    }
    return;
}

//----------------------------------------------------------------------------
bool cpl_SystemTools::Split(const char * str, char**& buffer, int& num, char separator) {
    //@@preconditions
    assert(buffer == NULL);
    //@@end preconditions

    cpl_String data = cpl_String(str);

    int count = 0;
    {
        int lpos = 0;
        while (lpos < data.size()) {
            int rpos = data.find(separator, lpos);
            if (rpos == -1) {
                count++;
                break;
            }
            else {
                count++;
            }
            lpos = rpos + 1;
        }
    }

    buffer = new char* [count];
    {
        count = 0;
        int lpos = 0;
        while (lpos < data.size()) {
            int rpos = data.find(separator, lpos);
            if (rpos == -1) {
                cpl_String tmpStr = data.substr(lpos, data.size()-lpos);
                int len = data.size()-lpos;
                buffer[count] = new char[len+1];
                strncpy(buffer[count], &str[lpos], len);
                buffer[count][len] = '\0';
                count++;
                break;
            }
            else {                
                cpl_String tmpStr = data.substr(lpos, rpos-lpos);
                int len = rpos-lpos;
                buffer[count] = new char[len+1];
                strncpy(buffer[count], &str[lpos], len);
                buffer[count][len] = '\0';
                count++;
            }
            lpos = rpos + 1;
        }
    }
    num = count;
    return true;
}

//-----------------------------------------------------------------------------
static unsigned long GetCurrentTime() {
    double currentTimeInSeconds;
#ifdef _WIN32
    timeb CurrentTime;
    static double scale = 1.0 / 1000.0;
    ::ftime(& CurrentTime);
    currentTimeInSeconds = CurrentTime.time + scale * CurrentTime.millitm;
#else
    static timeval CurrentTimeA;
    static double scale = 1.0 / 1000000.0;
    gettimeofday(& (CurrentTimeA), NULL);
    currentTimeInSeconds = CurrentTimeA.tv_sec + scale * CurrentTimeA.tv_usec;
#endif
    return (unsigned long)(1000.0*currentTimeInSeconds);
}

//-----------------------------------------------------------------------------
void cpl_SystemTools::Sleep(unsigned long elasped) {
    unsigned long initTime = GetCurrentTime();
    for (;;) {
        unsigned long currentTime = GetCurrentTime();
        if ((currentTime-initTime) > elasped) {
            break;
        }
    }
}

//-----------------------------------------------------------------------------
void cpl_SystemTools::CreateDirectory(const char* str) {
#ifdef WIN32
   _mkdir(str);
#else
   _mkdir(str);
#endif
}

//-----------------------------------------------------------------------------
bool cpl_SystemTools::IsDirectoryExist(const char * name) {
    struct stat fs;
    if (stat(name, & fs) == 0) {
#ifdef WIN32
        return ((fs.st_mode & _S_IFDIR) != 0);
#else
        return S_ISDIR(fs.st_mode);
#endif
    }
    else {
        return false;
    }
}

//-----------------------------------------------------------------------------
char* cpl_SystemTools::AppendPath(char* path1, char* path2) {
    assert(path1);
    assert(path2);

    static char szpath[2048];

    size_t len1 = strlen(path1); assert(len1 > 0);
    size_t len2 = strlen(path2); assert(len2 > 0);

    int endpath1 = 0, begpath2 = 0;
    if (path1[len1-1] == '\\' || path1[len1-1] == '/') endpath1 = 1;
    if (path2[0] == '\\'     || path2[0] == '/') begpath2 = 1;

    size_t sl = len1;
    strncpy(szpath, path1, sl);
    if( endpath1 == 0 ) {
        szpath[sl] = cpl_SystemTools::CONST_SEPDIRCHAR;
        sl++;
    }
    if( begpath2 == 1 ) {
        strncpy(szpath+sl, path2+1, len2-1);
        sl += len2-1;
    }else {
        strncpy(szpath+sl, path2, len2);
        sl += len2;
    }
    szpath[sl] = 0;
    cpl_SystemTools::ConvertWindowsPathToUnix(szpath);
    return szpath;
}

//-----------------------------------------------------------------------------
char* cpl_SystemTools::GetApplicationPath() {
    static char szpath[2048];       
#ifdef WIN32    
    char buffer[_MAX_PATH] = {0}, *application_path = NULL;
    ::GetModuleFileName(0, buffer, 1024);
    cpl_FileFilter::FileFilter(buffer);
    application_path = cpl_FileFilter::GetFilePath();
    if (cpl_SystemTools::IsDirectoryExist(application_path)) {
        strcpy(szpath,application_path);
        cpl_SystemTools::ConvertWindowsPathToUnix(szpath);
        return szpath;
    }

    application_path = getenv("DEMO_BIN");
    if (cpl_SystemTools::IsDirectoryExist(application_path)) {        
        strcpy(szpath,application_path);
        cpl_SystemTools::ConvertWindowsPathToUnix(szpath);
        return szpath;
    }      
    assert(0);
    return szpath;
#else
    const char* application_path = getenv("DEMO_BIN");
    if (cpl_SystemTools::IsDirectoryExist(application_path)) {        
        strcpy(szpath,application_path);
        return szpath;
    } 
    assert(0);
    return szpath;
#endif
}

//-----------------------------------------------------------------------------
char* cpl_SystemTools::GetDocumentPath() {
    static char szpath[1024];
    getMyDocument(szpath);
    cpl_SystemTools::ConvertWindowsPathToUnix(szpath);
    return szpath;
}

//-----------------------------------------------------------------------------
void cpl_SystemTools::GetFilePath(const char* fname, char path[]) {
    char drive[10];  
    char filename[1024];  
    char dir[1024];
    char fileext[100];      
    _splitpath(fname,drive,dir,filename,fileext);
    sprintf(path, "%s%s", drive, dir);
}

//-----------------------------------------------------------------------------
static int s_isExistent(const char *path)
{
#ifdef WIN32
#ifdef GCC
    if(!access(path, 0)) return 1;
#else
    if(!_access(path, 0)) return 1;
#endif

    return 0;
#else
    if(!access(path, F_OK)) return 1;
    return 0;
#endif
}

static int s_canAccess(const char *path)
{
#ifdef WIN32
    DWORD attr = GetFileAttributes(path);
    if(attr == (DWORD)~0l) return 0;

    if(attr & FILE_ATTRIBUTE_SYSTEM) return 0;

    if(attr & FILE_ATTRIBUTE_HIDDEN) return 0;

    return 1;
#else
    if(!access(path, R_OK)) return 1;
    return 0;
#endif
}

int cpl_SystemTools::CanAccessFile(const char * fname) {
    assert(fname);
    if( s_isExistent(fname) && s_canAccess(fname) ) return 1;
    return 0;
}

//-----------------------------------------------------------------------------
#ifdef USE_PCRE

#include <pcre.h>

#define OVECCOUNT   30    
//-----------------------------------------------------------------------------
bool cpl_SystemTools::RegExpressMatch(const char* src, const char* pattern) {   
    const char * error = NULL; int erroffset;
    pcre* re = pcre_compile(pattern, PCRE_CASELESS, &error, &erroffset, NULL);
    if (re == NULL) {
        return FALSE;
    }
    
    int ovector[OVECCOUNT];
    int rc = pcre_exec(re, NULL, src, (int)strlen(src), 0, 0, ovector, OVECCOUNT);
    if (rc < 0) {
        return FALSE;
    }        
    pcre_free(re);
    return TRUE;
}

#else
//-----------------------------------------------------------------------------
bool cpl_SystemTools::RegExpressMatch(const char* src, const char* pattern) {   
    return FALSE;
}

#endif //USE_PCRE
