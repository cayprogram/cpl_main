#ifndef CPL_FRAMEIMAGEINCLUDES_H
#define CPL_FRAMEIMAGEINCLUDES_H

#define IMAGE_SPEEDUP_AND_SAVEMEMORY   1

//-----------------------------------------------------------------------------
//predefined class
//-----------------------------------------------------------------------------
//
class cpl_Image;
class cpl_ImagePackage;
class cpl_ImagePackageBlender;
class cpl_ImagePackageZip;
class cpl_ImagePackageObjectFactory;
class cpl_ImageManager;
class cpl_ImagePluginParser;

//-----------------------------------------------------------------------------
//standard includes.
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>
#include <vector>
#include <map>

//-----------------------------------------------------------------------------
//interface includes
//-----------------------------------------------------------------------------
#include "iresimageproxy.h"

//-----------------------------------------------------------------------------
//dependency includes.
//-----------------------------------------------------------------------------
//
#include <cpl_frameobject/cpl_frameobjectincludes.h>
#include <cpl_frameutils/cpl_systemconfig.h>
#include <cpl_frameplugin/cpl_pluginframeincludes.h>
#include <cpl_frameplugintree/cpl_plugintreeframeincludes.h>
#include <cpl_frameluascript/cpl_luascriptframeincludes.h>

//-----------------------------------------------------------------------------
//class includes
//-----------------------------------------------------------------------------
//
#include "cpl_image.h"
#include "cpl_imagepackage.h"
#include "cpl_imagepackageblender.h"
#include "cpl_imagepackagezip.h"
#include "cpl_imagepackagefactory.h"
#include "cpl_imagemanager.h"
#include "cpl_imagepluginparser.h"

#include "cpl_imagecommonproxy.h"

#endif //CPL_FRAMEIMAGEINCLUDES_H
