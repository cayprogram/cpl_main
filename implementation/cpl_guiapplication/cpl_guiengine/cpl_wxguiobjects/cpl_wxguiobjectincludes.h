#ifndef CPL_WXGUIOBJECTINCLUDES_H
#define CPL_WXGUIOBJECTINCLUDES_H

//-----------------------------------------------------------------------------
//predefine class
//-----------------------------------------------------------------------------
//
class cpl_wxApp;
class cpl_wxOGLPanel;
class cpl_wxTaskPanel;
class cpl_wxMainFrame;
class cpl_wxMainToolbar;
class cpl_wxMainNormalToolbar;
class cpl_wxMainToolbox;
class cpl_wxMainMenubar;
class cpl_wxMainStatusbar;
class cpl_wxMainOutputPanel;
class cpl_wxMainOGLPanelManager;
class cpl_wxMainTaskPanelManager;
class cpl_wxMainFrameInfo;
class cpl_wxMainSystemPanel;
class cpl_wxMainSessionPanel;
class cpl_wxMainContextMenu;
class cpl_wxWorker;

//-----------------------------------------------------------------------------
//wxWidgets includes.
//-----------------------------------------------------------------------------
//
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //pre-compiled headers

#include "wx/math.h"
#include "wx/stockitem.h"

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/artprov.h>
#include "wx/glcanvas.h"
#include "wx/wxprec.h"
#include "wx/thread.h"
#include <wx/string.h>
#include <wx/regex.h>

//-----------------------------------------------------------------------------
//standard includes.
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>

//-----------------------------------------------------------------------------
//package includes.
//-----------------------------------------------------------------------------
//
#include <cpl_guiengine/cpl_guiengineframe/cpl_guiengineframeincludes.h>
#include <cpl_guiengine/cpl_applicationguiengineimpincludes.h>

//-----------------------------------------------------------------------------
//class includes.
//-----------------------------------------------------------------------------
//
#include "cpl_wxapp.h"
#include "cpl_wxmainframe.h"

#endif //CPL_WXGUIOBJECTINCLUDES_H
