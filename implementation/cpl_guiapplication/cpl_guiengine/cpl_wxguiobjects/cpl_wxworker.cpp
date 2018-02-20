#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxworker.h"

//-----------------------------------------------------------------------------
// class cpl_wxWorker
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
wxThread::ExitCode cpl_wxWorker::Entry() {
    this->m_bLife = 1;

    //loop as long as flag m_bLife = 1
    while (this->m_bLife) {
        if (TestDestroy() == 1) {
            break;
        }

        //exec
        if (this->cb.process && this->GetExecutingFlag() == 0) {
            //notify main thread to start.
            this->SendEvent(WORKER_START, 0);

            //sleep cpu.
            wxThread::Sleep(5);

            this->cb.process(this->cb.callData, this->cb.clientData); // this may call add_idle() or remove_idle()!

            //sleep cpu.
            wxThread::Sleep(5);

            //notify main thread done.
            this->SendEvent(WORKER_DONE, 0);
        }

        //sleep cpu.
        wxThread::Sleep(5);
    }
    return (wxThread::ExitCode)0; 
}

//-----------------------------------------------------------------------------
void cpl_wxWorker::Exec(void* arg, THREAD_TASK process, THREAD_TASK pre, THREAD_TASK post) {
    this->SetFunc(arg, process, pre, post);
}

//-----------------------------------------------------------------------------
void cpl_wxWorker::UpdateGUIState(int data) {
    this->SendEvent(WORKER_INPROCESS, data);
}

//-----------------------------------------------------------------------------
int cpl_wxWorker::SetExecutingFlag(int state) {
    wxCriticalSectionLocker enter(this->Owner->PThreadCS);   
    int old = this->m_isExecuting;
    this->m_isExecuting = state;
    return old;
}

//-----------------------------------------------------------------------------
int cpl_wxWorker::GetExecutingFlag() {
    wxCriticalSectionLocker enter(this->Owner->PThreadCS);   
    return this->m_isExecuting;
}

//-----------------------------------------------------------------------------
void cpl_wxWorker::ExecPre() {
    wxCriticalSectionLocker enter(this->Owner->PThreadCS);   
    if (this->cb.pre) {
        this->cb.pre(this->cb.callData, this->cb.clientData); // this may call add_idle() or remove_idle()!
    }
}

//-----------------------------------------------------------------------------
void cpl_wxWorker::ExecPost() {
    wxCriticalSectionLocker enter(this->Owner->PThreadCS);   
    if (this->cb.post) {
        this->cb.post(this->cb.callData, this->cb.clientData); // this may call add_idle() or remove_idle()!
    }
}

//-----------------------------------------------------------------------------
void cpl_wxWorker::SetFunc(void* arg, THREAD_TASK process, THREAD_TASK pre, THREAD_TASK post) {
    //@@preconditions
    assert(this->m_isExecuting == 0);
    //@@end preconditions

    wxCriticalSectionLocker enter(this->Owner->PThreadCS);    
    this->cb.process = process;
    this->cb.pre = pre;
    this->cb.post = post;
    this->cb.callData = this;
    this->cb.clientData = arg;
}

//-----------------------------------------------------------------------------
void cpl_wxWorker::SetBreakOn() {
    this->m_bLife = 0;
}

//-----------------------------------------------------------------------------
void cpl_wxWorker::SendEvent(int type, int data) {
    //1.asynchronous update,communicate with main thread.  
    wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, type);  
    event->SetInt(data);  
    wxQueueEvent(this->Owner, event);  
}

//-----------------------------------------------------------------------------
double cpl_wxWorker::GetTime() {
    struct timeb timeStamp;
    // get a time stamp
    ftime( &timeStamp );
    double nTime = (double) timeStamp.time*1000 + timeStamp.millitm;
    return( nTime );
}

//-----------------------------------------------------------------------------
cpl_wxWorker::cpl_wxWorker(cpl_wxMainFrame* pOwner) : wxThread(wxTHREAD_DETACHED), Owner(pOwner) {
    this->m_bLife = 1;
    this->m_isExecuting = 0;

    this->cb.process = 0;
    this->cb.pre = 0;
    this->cb.post = 0;
    this->cb.callData = 0;
    this->cb.clientData = 0;
}

//-----------------------------------------------------------------------------
cpl_wxWorker::~cpl_wxWorker() {
    wxCriticalSectionLocker enter(this->Owner->PThreadCS);    
    // the thread is being destroyed; make sure not to leave dangling pointers around    
    this->Owner->PWorker = NULL;
}
