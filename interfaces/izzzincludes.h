#ifndef INTERFACEZZZINCLUDE_H
#define INTERFACEZZZINCLUDE_H

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
#include "iruntimecontextproxy.h"
#include "ifileioproxy.h"
#include "imultifileioproxy.h"
#include "igraphicwindow.h"
#include "ioutputstatus.h"
#include "ioutputmessage.h"
#include "ipanelproxy.h"
#include "isessionproxy.h"
#include "iresimageproxy.h"
#include "ilayoutproxy.h"
#include "ithreadfunc.h"

//plugin tree.
#include "iplugin.h"
#include "iplugincodon.h"
#include "iplugintreenode.h"
#include "iplugintreepath.h"
#include "iplugintree.h"

#endif //INTERFACEZZZINCLUDE_H
