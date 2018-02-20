#ifndef CPL_CRITICALSECTION_H
#define CPL_CRITICALSECTION_H

#ifdef CPL_USE_SPROC
#include <abi_mutex.h>
typedef abilock_t cpl_CritSecType;
#endif

#ifdef CPL_USE_PTHREADS
#include <pthread.h>
typedef pthread_mutex_t cpl_CritSecType;
#endif

#ifdef _WIN32
#include <winbase.h>
typedef CRITICAL_SECTION cpl_CritSecType;
#endif

#ifndef CPL_USE_SPROC
#ifndef CPL_USE_PTHREADS
#ifndef _WIN32
typedef int cpl_CritSecType;

#endif
#endif
#endif

//-----------------------------------------------------------------------------
//cpl_SimpleCriticalSection
//-----------------------------------------------------------------------------

class cpl_SimpleCriticalSection {

public:
    /** create instance */
    static cpl_SimpleCriticalSection * New();

    /** delete itself */
    void Delete() { delete this; }

    /** get class name */
    virtual const char * GetClassName() { return "cpl_SimpleCriticalSection"; };

    /** lock the cpl_CriticalSection */
    void Lock(void);

    /** unlock the cpl_CriticalSection */
    void Unlock(void);

public:
    /** constructor */
    cpl_SimpleCriticalSection();

    /** destructor */
    virtual ~cpl_SimpleCriticalSection();

protected:
    cpl_CritSecType CritSec;
};


//-----------------------------------------------------------------------------
//cpl_CriticalSection
//-----------------------------------------------------------------------------

class cpl_CriticalSection {

public:
    /** create instance */
    static cpl_CriticalSection * New();

    /** lock the cpl_CriticalSection */
    void Lock(void);

    /** unlock the cpl_CriticalSection */
    void Unlock(void);

protected:
    cpl_SimpleCriticalSection SimpleCriticalSection;
};

//-----------------------------------------------------------------------------
inline void cpl_CriticalSection::Lock(void) {
    this->SimpleCriticalSection.Lock();
}

//-----------------------------------------------------------------------------
inline void cpl_CriticalSection::Unlock(void) {
    this->SimpleCriticalSection.Unlock();
}

#endif //CPL_CRITICALSECTION_H
