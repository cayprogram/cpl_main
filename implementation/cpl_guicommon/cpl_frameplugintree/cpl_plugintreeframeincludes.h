#ifndef CPL_PLUGINTREEFRAMEINCLUDES_H
#define CPL_PLUGINTREEFRAMEINCLUDES_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#pragma warning( disable : 4800 ) // disable  unreferenced formal parameter
#endif

//-----------------------------------------------------------------------------
//precondition interface
//-----------------------------------------------------------------------------

class IPluginTreeNode;
class IPluginTreePath;
class IPluginTree;

//-----------------------------------------------------------------------------
//predefined class
//-----------------------------------------------------------------------------

class cpl_PluginTree;
class cpl_PluginTreeNode;
class cpl_PluginTreePath;
class cpl_PluginTreeMap;

//-----------------------------------------------------------------------------
//standard includes.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
//interface includes
//-----------------------------------------------------------------------------

#include "iplugintreenode.h"
#include "iplugintreepath.h"
#include "iplugintree.h"

//-----------------------------------------------------------------------------
//dependency includes.
//-----------------------------------------------------------------------------

#include <cpl_frameplugin/cpl_pluginframeincludes.h>

//-----------------------------------------------------------------------------
//class includes
//-----------------------------------------------------------------------------

#include "cpl_plugintree.h"
#include "cpl_plugintreenode.h"
#include "cpl_plugintreepath.h"
#include "cpl_plugintreemap.h"

#endif //CPL_PLUGINTREEFRAMEINCLUDES_H
