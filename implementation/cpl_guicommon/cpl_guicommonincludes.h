#ifndef CPL_GUICOMMONINCLUDES_H
#define CPL_GUICOMMONINCLUDES_H

#ifdef WIN32
#pragma warning( push ) // memorize the warning status
#pragma warning( disable : 4305 ) // disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 ) // disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 ) // disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 ) // disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 ) // disable " 'type conversion' ; possible loss of data" warning
#pragma warning( disable : 4100 ) // disable  unreferenced formal parameter
#endif

//-----------------------------------------------------------------------------
//standard system includes.
//-----------------------------------------------------------------------------
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
//interface includes.
//-----------------------------------------------------------------------------
//
#include <izzzincludes.h>

//-----------------------------------------------------------------------------
//package includes.
//-----------------------------------------------------------------------------
//
#include "cpl_frameutils/cpl_frameutilsincludes.h"
#include "cpl_frameobject/cpl_frameobjectincludes.h"
#include "cpl_framewidget/cpl_widgetframeincludes.h"
#include "cpl_frameaction/cpl_actionframeincludes.h"
#include "cpl_frameluascript/cpl_luascriptframeincludes.h"
#include "cpl_frameplugin/cpl_pluginframeincludes.h"
#include "cpl_frameplugintree/cpl_plugintreeframeincludes.h"
#include "cpl_frameicons/cpl_frameiconincludes.h"
#include "cpl_frameimages/cpl_frameimageincludes.h"
#include "cpl_frameoutput/cpl_outputframeincludes.h"

#endif //CPL_GUICOMMONINCLUDES_H
