#include "cpl_frameobjectincludes.h"

//-----------------------------------------------------------------------------
// class cpl_CriticalSection
//-----------------------------------------------------------------------------
//
cpl_CriticalSection * cpl_CriticalSection::New() {
    return new cpl_CriticalSection;
}

//-----------------------------------------------------------------------------
// cpl_SimpleCriticalSection
//-----------------------------------------------------------------------------
//
cpl_SimpleCriticalSection::cpl_SimpleCriticalSection() {
#ifdef CPL_USE_SPROC
    init_lock(& this->CritSec);
#endif

#ifdef _WIN32
    InitializeCriticalSection(& this->CritSec);
#endif

#ifdef CPL_USE_PTHREADS
#ifdef CPL_HP_PTHREADS
    pthread_mutex_init(& (this->CritSec), pthread_mutexattr_default);
#else
    pthread_mutex_init(& (this->CritSec), NULL);
#endif
#endif
}

//-----------------------------------------------------------------------------
cpl_SimpleCriticalSection::~cpl_SimpleCriticalSection() {
#ifdef _WIN32
    DeleteCriticalSection(& this->CritSec);
#endif

#ifdef CPL_USE_PTHREADS
    pthread_mutex_destroy(& this->CritSec);
#endif
}

//-----------------------------------------------------------------------------
void cpl_SimpleCriticalSection::Lock() {
#ifdef CPL_USE_SPROC
    spin_lock(& this->CritSec);
#endif

#ifdef _WIN32
    EnterCriticalSection(& this->CritSec);
#endif

#ifdef CPL_USE_PTHREADS
    pthread_mutex_lock(& this->CritSec);
#endif
}

//-----------------------------------------------------------------------------
void cpl_SimpleCriticalSection::Unlock() {
#ifdef CPL_USE_SPROC
    release_lock(& this->CritSec);
#endif

#ifdef _WIN32
    LeaveCriticalSection(& this->CritSec);
#endif

#ifdef CPL_USE_PTHREADS
    pthread_mutex_unlock(& this->CritSec);
#endif
}
