#ifndef CPL_PLUGINFRAMEINCLUDES_H
#define CPL_PLUGINFRAMEINCLUDES_H

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
//interface definitions
//----------------------------------------------------------------------------
class IPlugin;
class IPluginCodon;

//
//-----------------------------------------------------------------------------
//class definitions
//----------------------------------------------------------------------------

class cpl_Plugin;
class cpl_PluginCodon;
class cpl_PluginCodonCollection;
class cpl_PluginExtension;
class cpl_PluginExtensionCollection;
class cpl_CompositePlugin;
class cpl_PluginXmlReader;
class cpl_PluginManager;

//-----------------------------------------------------------------------------
//system includes
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
//interface includes
//-----------------------------------------------------------------------------

#include <iplugin.h>
#include <iplugincodon.h>

//-----------------------------------------------------------------------------
//dependent package
//-----------------------------------------------------------------------------

#include <cpl_frameobject/cpl_frameobjectincludes.h>

//-----------------------------------------------------------------------------
//class includes
//-----------------------------------------------------------------------------
//
#include "cpl_plugin.h"
#include "cpl_plugincodon.h"
#include "cpl_plugincodoncollection.h"
#include "cpl_pluginextension.h"
#include "cpl_pluginextensioncollection.h"
#include "cpl_plugincomposite.h"
#include "cpl_pluginxmlreader.h"
#include "cpl_pluginmanager.h"

#endif //CPL_PLUGINFRAMEINCLUDES_H
