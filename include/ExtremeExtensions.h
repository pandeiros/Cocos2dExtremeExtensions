#ifndef __EXTREME_EXTENSIONS_H__
#define __EXTREME_EXTENSIONS_H__

/********************************************************************
 * /===================================\
 * | COCOS2D-X EXTREME EXTENSIONS PACK |
 * \===================================/
 *
 * Project supervised by KNTG Polygon.
 *
 * @authors
 *  - Paweł Kaczyński
 *
 * Extreme Extensions pack contains many tools simplifying creation
 * of commonly used features in game development. The maing goal is
 * to reduce the amount of work on non-gameplay and backend features
 * to minimum. It is a great pack to use on game jams.
 *
 * Content:
 *  - QuickMenu : Easy cocos2d::Menu creation based on a XML file.
 *
 *********************************************************************/

// Cocos2D lib
#include "cocos2d.h"

// Extreme Extensions defines
#include "xxConfig.h"

// XX Main Packages
#include "QuickMenu/xxQuickMenu.h"

// XX Utility Classes
#include "Utils/XMLDocument/xxXMLDocument.h"
#include "Utils/MessageHandler/xxMessageHandler.h"
#include "Utils/StringUtilities/xxStringUtilities.h"

 // XX Test file
 #include "xxTest.h"

NS_XX_BEGIN

XX_DLL const char* xxVersion ();

NS_XX_END

#endif  // __EXTREME_EXTENSIONS_H__