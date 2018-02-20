#include "cpl_frameobjectincludes.h"

//-----------------------------------------------------------------------------
static cpl_SimpleCriticalSection TimeStampCritSec;

//-----------------------------------------------------------------------------
// class cpl_TimeStamp
//-----------------------------------------------------------------------------
//
cpl_TimeStamp * cpl_TimeStamp::New() {
    return new cpl_TimeStamp;
}

//-----------------------------------------------------------------------------
void cpl_TimeStamp::Modified() {
    static unsigned long cpl_TimeStampTime = 0;
    TimeStampCritSec.Lock();
    this->ModifiedTime = ++cpl_TimeStampTime;
    TimeStampCritSec.Unlock();
}
