#ifndef OUTPUTSTATUSINTERFACE_H
#define OUTPUTSTATUSINTERFACE_H

class IOutputStatusInfo {

public:
    /** status text A */
    virtual void StatusTextA(const char* text) = 0;

    /** status text B */
    virtual void StatusTextB(const char* text) = 0;

    /** status text C */
    virtual void StatusTextC(const char* text) = 0;

    /** status progress */
    virtual void SetProgressStatus(int state) = 0;

    /** status progress */
    virtual void SetProgressValue(float value) = 0;
};

#endif //OUTPUTSTATUSINTERFACE_H
