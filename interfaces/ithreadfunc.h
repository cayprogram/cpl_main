#ifndef ITHREADFUNCINTERFACE_H
#define ITHREADFUNCINTERFACE_H

typedef void (*THREAD_TASK)(void *, void *);  

//-----------------------------------------------------------------------------
// class IThreadFunc
//-----------------------------------------------------------------------------
//
class IThreadFunc {

public:
    // exec function
    virtual void Exec(void* arg, THREAD_TASK process, THREAD_TASK pre = NULL, THREAD_TASK post = NULL) = 0;

    // update gui state [0-1000]
    virtual void UpdateGUIState(int data) = 0;
};

#endif //ITHREADFUNCINTERFACE_H
