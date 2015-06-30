#ifndef __POLY_H__
#define __POLY_H__

/********************************************************************
 * /=================================\
 * | COCOS2D-X "PolyCocos" EXTENSIONS PACK |
 * \=================================/
 *
 * @authors
 *  - Paweł Kaczyński
 *
 * "PolyCocos" contains many tools simplifying creation
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

// PolyCocos defines
#include "polyConfig.h"

// PolyCocos Main Packages
#include "QuickMenu/polyQuickMenu.h"

// PolyCocos Utility Classes
#include "Utils/XMLDocument/polyXMLDocument.h"
#include "Utils/MessageHandler/polyMessageHandler.h"
#include "Utils/StringUtilities/polyStringUtilities.h"

// PolyCocos Test file
#include "polyTest.h"

NS_POLY_BEGIN

POLY_DLL const char* polyVersion ();

NS_POLY_END

#endif  // __POLY_H__
