#ifndef __EXTREME_EXTENSIONS_H__
#define __EXTREME_EXTENSIONS_H__

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Cocos2D lib
#include "cocos2d/cocos/cocos2d.h"

// Extreme Extensions defines
#include "xxDefines.h"

// XX Packages
#include "QuickMenu/xxQuickMenu.h"

NS_XX_BEGIN

XX_DLL const char* xxVersion ();

NS_XX_END


#endif  // __XX_MACROS_H__