#ifndef CPL_FRAMEWORKINCLUDE_H
#define CPL_FRAMEWORKINCLUDE_H

/* first include the local configuration for this machine */
#define __CPL__SYSTEM_INCLUDES__INSIDE
#include "cpl_win32header.h"
#undef  __CPL__SYSTEM_INCLUDES__INSIDE

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#endif

//
//----macro to implement the standard form of the New() method
//
#define CPL_StandardNewCommandMacro(thisClass) \
  thisClass* thisClass::New() \
  { \
    cpl_Object* ret = cpl_ObjectFactory::CreateInstance(#thisClass); \
    if(ret) \
      { \
      return static_cast<thisClass*>(ret); \
      } \
    return new thisClass; \
  }

#define CPL_CREATE_CREATE_FUNCTION(classname) \
  static cpl_Object* cpl_ObjectFactoryCreate##classname() \
  { \
     return classname::New(); \
  }

//-----------------------------------------------------------------------------
//class predefinitions.
//-----------------------------------------------------------------------------
//
class cpl_TimeStamp;
class cpl_ObjectBase;
class cpl_Object;
class cpl_ObjectFactory;
class cpl_ObjectFactoryPool;
class cpl_Directory;
class cpl_DynamicLoader;
class cpl_CriticalSection;

//-----------------------------------------------------------------------------
//standard definitions.
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#ifdef WIN32
#include <windows.h>
#include <direct.h>
#include <sys\stat.h>
#endif

//-------------------------------------------------------------------------
typedef struct _DGUID {
    int   Data1;
    short Data2;
    short Data3;
    char  Data4[8];
} DGUID;

#define REFDGUID const DGUID&

//-------------------------------------------------------------------------
typedef void* (*CREATE_FUNC)();

//-------------------------------------------------------------------------
typedef struct _ImplementationProxy {
    char progId[64];
    DGUID classId;
    CREATE_FUNC func;
} 
ImplementationProxy;

//-------------------------------------------------------------------------
inline BOOL IsEqualDGUID(REFDGUID r1, REFDGUID r2) 
{ return !memcmp(&r1, &r2, sizeof(DGUID)); }

inline BOOL operator == (REFDGUID r1, REFDGUID r2) 
{ return !memcmp(&r1, &r2, sizeof(DGUID)); }

inline BOOL operator != (REFDGUID r1, REFDGUID r2) 
{ return !(r1 == r2); }

typedef ImplementationProxy* (*IMPLEMENTPROXY_FUNC)(int&);

//-----------------------------------------------------------------------------
//plugin interface.
//-----------------------------------------------------------------------------
//
//#include <zplcom.h>

//-----------------------------------------------------------------------------
//class includes.
//-----------------------------------------------------------------------------
//

typedef ImplementationProxy cpl_ImplementationProxy;

#include "cpl_timestamp.h"
#include "cpl_objectbase.h"
#include "cpl_object.h"
#include "cpl_criticalsection.h"
#include "cpl_objectfactory.h"
#include "cpl_objectfactorypool.h"
#include "cpl_systemtools.h"
#include "cpl_directory.h"
#include "cpl_dynamicloader.h"
#include "cpl_string.h"
#include "cpl_stringcollection.h"
#include "cpl_hashtablestring.h"
#include "cpl_hashtableobject.h"
#include "cpl_creator.h"
#include "cpl_filefilter.h"
#include "cpl_multifilefilter.h"
#include "cpl_implementionproxycollection.h"

#endif //CPL_FRAMEWORKINCLUDE_H
