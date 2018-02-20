#ifndef CPL_WXWORKER_H
#define CPL_WXWORKER_H

#define WORKER_START     2000
#define WORKER_INPROCESS 2001
#define WORKER_DONE      2002

class cpl_wxWorker : public IThreadFunc,  public wxThread {

public:
    // Override thread entry point
    virtual ExitCode Entry();

    // set break 
    void SetBreakOn();

public:
    // exec func.
    virtual void Exec(void* arg, THREAD_TASK process, THREAD_TASK pre, THREAD_TASK post);

    // update gui state 
    virtual void UpdateGUIState(int data);

public:
    // send event.
    void SendEvent(int type, int data);

    // exec pre
    void ExecPre();

    // exec post
    void ExecPost();

public:
    //constructor.
    cpl_wxWorker(cpl_wxMainFrame* pOwner);

    //destructor.
    virtual ~cpl_wxWorker();

public:
    //inner structure.
    struct _fbIdle_cb {
        THREAD_TASK process;
        THREAD_TASK pre;
        THREAD_TASK post;
        void* callData;
        void* clientData;
    };

    //
    cpl_wxMainFrame* Owner;

    // timers
    unsigned char m_bLife;
    unsigned char m_isExecuting;

    //idle callback.
    _fbIdle_cb  cb;

    // get time
    double GetTime(); 

    // executing flag
    int SetExecutingFlag(int state);
    int GetExecutingFlag();

    // set func
    void SetFunc(void* arg, THREAD_TASK process, THREAD_TASK pre, THREAD_TASK post);
};

#endif //CPL_WXWORKER_H
