#include "cpl_frameobjectincludes.h"

//-----------------------------------------------------------------------------
// static variables.
//-----------------------------------------------------------------------------
//
int cpl_MultiFileFilter::number = 0;
cpl_MultiFileFilter::MultiFilt cpl_MultiFileFilter::filters[MAX_FILT_NUMBER];

//-----------------------------------------------------------------------------
// class cpl_MultiFileFilter
//-----------------------------------------------------------------------------
//
int cpl_MultiFileFilter::Getnumber() {
    return cpl_MultiFileFilter::number;
}

//-----------------------------------------------------------------------------
char* cpl_MultiFileFilter::GetFileName(int index) {
    return cpl_MultiFileFilter::filters[index].pCharName;
}

//-----------------------------------------------------------------------------
char* cpl_MultiFileFilter::GetFilePath(int index) {
    return cpl_MultiFileFilter::filters[index].pCharPath;
}

//-----------------------------------------------------------------------------
char* cpl_MultiFileFilter::GetFileExt(int index) {
    return cpl_MultiFileFilter::filters[index].pCharExt;
}

char* cpl_MultiFileFilter::GetFileFullName(int index) {
    return cpl_MultiFileFilter::filters[index].pCharFull;
}

//-----------------------------------------------------------------------------
int   cpl_MultiFileFilter::GetFileExist(int index) {
    return cpl_MultiFileFilter::filters[index].Exists;
}

//-----------------------------------------------------------------------------
void cpl_MultiFileFilter::CleanupFilt() {
    cpl_MultiFileFilter::number = 0;
    memset(cpl_MultiFileFilter::filters, 0, MAX_FILT_NUMBER*sizeof(MultiFilt));
}

//-----------------------------------------------------------------------------
void cpl_MultiFileFilter::CleanupFilt(int index) {
    cpl_MultiFileFilter::filters[index].Exists = 0;
    cpl_MultiFileFilter::filters[index].Flen = 0;
    cpl_MultiFileFilter::filters[index].pCharExt[0] = '\0';
    cpl_MultiFileFilter::filters[index].pCharFull[0] = '\0';
    cpl_MultiFileFilter::filters[index].pCharName[0] = '\0';
    cpl_MultiFileFilter::filters[index].pCharPath[0] = '\0';
    cpl_MultiFileFilter::filters[index].pCharPath_slashed[0] = '\0';
}

//-----------------------------------------------------------------------------
int cpl_MultiFileFilter::IsContainPath(char* pfname) {
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
void cpl_MultiFileFilter::FileFilter(char * pfname) {
    int ICnt;
    char * pChar, * pChar1, * pChar2, * pChar3, CharBuffer[512];
    char * fname = NULL, wd[1000], WindowsPassed[1000];

    int index = cpl_MultiFileFilter::Getnumber();
    if(index >= MAX_FILT_NUMBER) return;

    MultiFilt * pFilt = &cpl_MultiFileFilter::filters[index];
    
#ifdef WIN32
    struct _stat stfbuf;
    char path_char = '\\';
#else
    char path_char = '/';
#endif
    int hasPath = 0;
    int i, j;
    int len;

    len = (int)strlen(pfname);
    for (i = 0; i < len; i++) {
        if (pfname[i] == path_char) {
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
    len = (int)strlen(fname);

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
    for (pChar1 = pFilt->pCharFull + ICnt; pChar1 >= pFilt->pCharFull && * pChar1 != path_char; pChar1--) {
        if (* pChar1 == path_char) break;
    }
    if (* pChar1 == path_char) {
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
        if(* pChar == path_char) { // if there is no extension
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
            if (pFilt->pCharPath[i] == path_char) pFilt->pCharPath_slashed[j++] = path_char;
            else pFilt->pCharPath_slashed[j++] = pFilt->pCharPath[i];
        }
    }
    if (strlen(pFilt->pCharName) <1) {
        pFilt->Exists = 0;
    }

    cpl_MultiFileFilter::number++;
    assert(cpl_MultiFileFilter::number <= MAX_FILT_NUMBER);
}
