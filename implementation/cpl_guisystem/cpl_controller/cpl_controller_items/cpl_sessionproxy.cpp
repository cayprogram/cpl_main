#include <cpl_controller/cpl_controllerframeincludes.h>
#include <time.h>
#include "cpl_sessionproxy.h"

//-----------------------------------------------------------------------------
// class cpl_SessionProxyImp
//-----------------------------------------------------------------------------
//
class cpl_SessionProxyImp : public ISessionProxy {

public:
    /** is valid to record session */
    int  IsValidRecordSession();

    /** is running session */
    int  IsRunningSession();

    /** read function session */
    void WriteFunctionSession(char* funStr);

    /** write command session */
    void WriteCommandSession(char* cmdStr);

    /** is function not need to be recorded */
    int  IsSkipRecordFunction(char* funStr);

protected:
    /** write session head */
    void WriteSessionHead();

    /** write session tail */
    void WriteSessionTail();

public:
    //constructor
    cpl_SessionProxyImp();

    //destructor
    virtual ~cpl_SessionProxyImp();

protected:
    FILE* sessionWriteFP;
};

//-----------------------------------------------------------------------------
int cpl_SessionProxyImp::IsValidRecordSession() {
    if (this->sessionWriteFP == NULL) {
        return 0;
    }
    return 1;
}

//-----------------------------------------------------------------------------
int cpl_SessionProxyImp::IsRunningSession() {
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_SessionProxyImp::WriteCommandSession(char* cmdStr) {
    //@@preconditions
    assert(cmdStr != NULL);
    assert(this->sessionWriteFP != NULL);
    //@@end preconditions

    fprintf(this->sessionWriteFP, "  <COMMAND NAME=\"");
    fprintf(this->sessionWriteFP, cmdStr);
    fprintf(this->sessionWriteFP, "\"/>\n");
    fflush(this->sessionWriteFP);
    return;
}

//-----------------------------------------------------------------------------
void cpl_SessionProxyImp::WriteFunctionSession(char* funStr) {
    //@@preconditions
    assert(funStr != NULL);
    assert(this->sessionWriteFP != NULL);
    //@@end preconditions

    fprintf(this->sessionWriteFP, "  <FUNCTION NAME=\"");
    fprintf(this->sessionWriteFP, funStr);
    fprintf(this->sessionWriteFP, "\"/>");
    fprintf(this->sessionWriteFP, "\n");
    fflush(this->sessionWriteFP);
    return;
}

//-----------------------------------------------------------------------------
int cpl_SessionProxyImp::IsSkipRecordFunction(char* funStr) {
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_SessionProxyImp::WriteSessionHead() {
    //@@preconditions
    assert(this->sessionWriteFP != NULL);
    //@@end preconditions

    //get system time.
    char charTime[512];
    {
        time_t sysTime = time(0);
        sprintf(charTime, "%s", ctime(&sysTime));

        int slen = (int)strlen(charTime);
        assert(slen < 511);
        if (charTime[slen - 1] < 48 || charTime[slen - 1] > 90) {
            charTime[slen - 1] = '\0';
        }
    }

    char* productName = cpl_SystemConfig::Instance()->GetFullProductName();
    assert(productName != NULL);

    fprintf(this->sessionWriteFP, "<!--  %s session (version.1.0) started at %s -->\n", productName, charTime);
    fprintf(this->sessionWriteFP, "<SESSION>\n");
    fflush(this->sessionWriteFP);
}

//-----------------------------------------------------------------------------
void cpl_SessionProxyImp::WriteSessionTail() {
    //@@preconditions
    assert(this->sessionWriteFP != NULL);
    //@@end preconditions

    fprintf(this->sessionWriteFP, "</SESSION>\n\n");
    fflush(this->sessionWriteFP);
}

//-----------------------------------------------------------------------------
cpl_SessionProxyImp::cpl_SessionProxyImp() {
    char sessionFileName[1024];
    SYSTEMTIME sys;   
    GetLocalTime( &sys );   
    sprintf(sessionFileName, "session_%d_%02d_%02d_%02d_%02d_%02d.txt", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute,sys.wSecond);

    const char* sessionWorkDir = NULL;
    cpl_SystemConfig::Instance()->GetWorkDirectory(sessionWorkDir, cpl_SystemConfig::EFileType_HOME);
    assert(sessionWorkDir);

    char* sessionFileFullName = cpl_SystemTools::AppendPath((char*)sessionWorkDir, sessionFileName);
    assert(sessionFileFullName != NULL);

    this->sessionWriteFP = fopen(sessionFileFullName, "a+");
    if (this->sessionWriteFP == NULL) {
        return;
    }
    this->WriteSessionHead();
}

//-----------------------------------------------------------------------------
cpl_SessionProxyImp::~cpl_SessionProxyImp() {
    if (this->sessionWriteFP != NULL) {
        this->WriteSessionTail();

        fclose(this->sessionWriteFP);
        this->sessionWriteFP = NULL;
    }
}

//-----------------------------------------------------------------------------
// class cpl_SessionProxy
//-----------------------------------------------------------------------------
//
cpl_SessionProxy* cpl_SessionProxy::New() {
    return new cpl_SessionProxy;
}

//-----------------------------------------------------------------------------
void cpl_SessionProxy::DoInitialization() {
    //@@preconditions
    assert(this->Implementaion == NULL);
    //@@end preconditions

    this->Implementaion = new cpl_SessionProxyImp();
}

//-----------------------------------------------------------------------------
void cpl_SessionProxy::DoCleanup() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end preconditions

    delete (cpl_SessionProxyImp*)this->Implementaion;
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
ISessionProxy* cpl_SessionProxy::GetImplementation() {
    //@@preconditions
    assert(this->Implementaion != NULL);
    //@@end precondition

    return this->Implementaion;
}

//-----------------------------------------------------------------------------
cpl_SessionProxy::cpl_SessionProxy() {
    this->Implementaion = NULL;
}

//-----------------------------------------------------------------------------
cpl_SessionProxy::~cpl_SessionProxy() {
    assert(this->Implementaion == NULL);
}
