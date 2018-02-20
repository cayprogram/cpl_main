#ifndef CPL_ACTIONFRAMEINCLUDES_H
#define CPL_ACTIONFRAMEINCLUDES_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#pragma warning( disable : 4514 ) // disable  unreferenced formal parameter
#endif

//-----------------------------------------------------------------------------
//predefine class
//-----------------------------------------------------------------------------
//
class cpl_Action;
class cpl_ActionComposite;
class cpl_ActionCompositeProxy;

//typedef for convenience.
typedef cpl_Action cpl_MenuItem;
typedef cpl_ActionComposite cpl_SubMenu;

//-----------------------------------------------------------------------------
//standard includes.
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
//class includes
//-----------------------------------------------------------------------------
//
#include "cpl_action.h"
#include "cpl_actioncomposite.h"
#include "cpl_actioncompositeproxy.h"

#endif //CPL_ACTIONFRAMEINCLUDES_H

