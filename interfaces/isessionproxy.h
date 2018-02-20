#ifndef SESSIONPROXYINTERFACE_H
#define SESSIONPROXYINTERFACE_H

class ISessionProxy {

public:
    /** is valid to record session */
    virtual int  IsValidRecordSession() = 0;

    /** is running session */
    virtual int  IsRunningSession() = 0;

    /** write command session */
    virtual void WriteCommandSession(char* cmdStr) = 0;

    /** read function session */
    virtual void WriteFunctionSession(char* funStr) = 0;

    /** is function not need to be recorded */
    virtual int  IsSkipRecordFunction(char* funStr) = 0;
};

#endif //SESSIONPROXYINTERFACE_H
