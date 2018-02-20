#ifndef CPL_LUASCRIPTFRAMEINCLUDE_H
#define CPL_LUASCRIPTFRAMEINCLUDE_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#endif

//class definitions

//-----------------------------------------------------------------------------
//standard system includes.
//-----------------------------------------------------------------------------
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
//interface includes.
//-----------------------------------------------------------------------------
//
#include "interfaceluascriptproxy.h"

//-----------------------------------------------------------------------------
//class includes.
//-----------------------------------------------------------------------------
//
#include "cpl_luascript.h"
#include "cpl_luascriptutility.h"
#include "cpl_luamanager.h"

#endif //CPL_LUASCRIPTFRAMEINCLUDE_H
