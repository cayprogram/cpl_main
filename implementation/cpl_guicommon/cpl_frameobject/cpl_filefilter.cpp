#include "cpl_frameobjectincludes.h"

//-----------------------------------------------------------------------------
// static variables.
//-----------------------------------------------------------------------------
//
cpl_FileFilter::Filt cpl_FileFilter::filter;

//-----------------------------------------------------------------------------
// class cpl_FileFilter
//-----------------------------------------------------------------------------
//
char* cpl_FileFilter::GetFileName() {
    return cpl_FileFilter::filter.pCharName;
}

//-----------------------------------------------------------------------------
char* cpl_FileFilter::GetFilePath() {
    return cpl_FileFilter::filter.pCharPath;
}

//-----------------------------------------------------------------------------
char* cpl_FileFilter::GetFileExt() {
    return cpl_FileFilter::filter.pCharExt;
}

//-----------------------------------------------------------------------------
char* cpl_FileFilter::GetFileFullName() {
    return cpl_FileFilter::filter.pCharFull;
}

//-----------------------------------------------------------------------------
int   cpl_FileFilter::GetFileExist() {
    return cpl_FileFilter::filter.Exists;
}

//-----------------------------------------------------------------------------
void cpl_FileFilter::CleanupFilt() {
    cpl_FileFilter::filter.Exists = 0;
    cpl_FileFilter::filter.Flen = 0;
    cpl_FileFilter::filter.pCharExt[0] = '\0';
    cpl_FileFilter::filter.pCharFull[0] = '\0';
    cpl_FileFilter::filter.pCharName[0] = '\0';
    cpl_FileFilter::filter.pCharPath[0] = '\0';
    cpl_FileFilter::filter.pCharPath_slashed[0] = '\0';
}

//-----------------------------------------------------------------------------
int cpl_FileFilter::IsContainPath(char* pfname) {
#ifdef WIN32
    char path_char = '\\';
#else
    char path_char = '/';
#endif
    int hasPath = 0;
    size_t len = strlen(pfname);
    for (size_t i = 0; i < len; i++) {
        if (pfname[i] == path_char) {
            hasPath = 1;
            break;
        }
    }
    return hasPath;
}

//-----------------------------------------------------------------------------
void cpl_FileFilter::FileFilter(char * pfname) {
    int ICnt;
    char * pChar, * pChar1, * pChar2, * pChar3, CharBuffer[512];
    char * fname = NULL, wd[1000], WindowsPassed[1000];

    cpl_FileFilter::CleanupFilt();

    Filt * pFilt = &cpl_FileFilter::filter;
    
#ifdef WIN32
    struct _stat stfbuf;
    char path_char = '\\';
#else
    char path_char = '/';
#endif
    int hasPath = 0;
    size_t i, j;
    size_t len = strlen(pfname);
    for (i = 0; i < len; i++) {
        if (pfname[i] == '\\' || pfname[i] == '/') {
            hasPath = 1;
            break;
        }
    }

    if (!hasPath) {
        fname = wd;
        _getcwd(wd, 1000);
        strcat(wd, "\\");
        strcat(wd, pfname);
    }
    else fname = pfname;

    memset(WindowsPassed, '\0', 1000);
    len = strlen(fname);

    for (i = 0, j = 0; i < len; i++) {
        if (fname[i] != '"') WindowsPassed[j++] = fname[i];
    }
    fname = WindowsPassed;
    pChar = pChar1 = pChar2 = pChar3 = NULL;

    strcpy(pFilt->pCharFull, fname);
    pFilt->pCharName[0] = '\0';
    pFilt->pCharPath[0] = '\0';
    pFilt->pCharExt[0] = '\0';
    pFilt->Flen = (int)strlen(fname);
#ifdef WIN32
    pFilt->Exists = !_stat(fname, & stfbuf);
#else
    if (access(fname, 0) == 0) {
         pFilt->Exists = 1;
    }
    else {
         pFilt->Exists = 0;
    }
#endif

    //..get path
    ICnt = pFilt->Flen;
    for (pChar1 = pFilt->pCharFull + ICnt; pChar1 >= pFilt->pCharFull && (* pChar1 != '\\' || * pChar1 != '/'); pChar1--) {
        if (* pChar1 == '\\' || * pChar1 == '/') break;
    }
    if (* pChar1 == '\\' || * pChar1 == '/') {
        memset(CharBuffer, '\0', 512);
        for (pChar = pFilt->pCharFull, pChar2 = CharBuffer; pChar != pChar1; pChar++, pChar2++) * pChar2 = * pChar;
        strcpy(pFilt->pCharPath, CharBuffer);
    }
    else pChar1 = NULL;

    //..get the filename
    if (pFilt->pCharPath[0] != '\0') { // if there is a path
        for(pChar=pFilt->pCharFull + pFilt->Flen; pChar>pChar1; pChar--) { 
            if(*pChar == '.') break;
        }
        pChar2 = pChar1 + 1; // one character past the slash
        if(* pChar == '\\' || * pChar == '/') { // if there is no extension
            strcpy(pFilt->pCharName, pChar2);
        }
        else { // if there is an extension
            memset(CharBuffer, '\0', 512);
            strncpy(CharBuffer, pChar1+1, pChar-pChar1-1); 
            strcpy(pFilt->pCharName, CharBuffer);
        }
    }
    else { // if there is no path
        for (pChar = pFilt->pCharFull; * pChar != '\0' && * pChar != '.'; pChar++);
        if (* pChar == '\0') { // no extension
             strcpy(pFilt->pCharName, pFilt->pCharFull);
        }
        else { // there is an extension
             memset(CharBuffer, '\0', 512);
             for (pChar2 = pFilt->pCharFull, pChar3 = CharBuffer; pChar2 != pChar; pChar2++, pChar3++) * pChar3 = * pChar2;
             strcpy(pFilt->pCharName, CharBuffer);
        }
    }

    //..get Extension		
    if (* pChar == '.') { // if there is an extension
         memset(CharBuffer, '\0', 512);
         pChar += 1;
         strcpy(pFilt->pCharExt, pChar);
    }

    //..create long path
    if (pFilt->pCharPath[0] != '\0') {
        memset(pFilt->pCharPath_slashed, '\0', 512);
        for (i = 0, j = 0; i < (int)strlen(pFilt->pCharPath); i++) {
            if (pFilt->pCharPath[i] == '\\' || pFilt->pCharPath[i] == '/') pFilt->pCharPath_slashed[j++] = path_char;
            else pFilt->pCharPath_slashed[j++] = pFilt->pCharPath[i];
        }
    }
    if (strlen(pFilt->pCharName) <1) {
        pFilt->Exists = 0;
    }
}
