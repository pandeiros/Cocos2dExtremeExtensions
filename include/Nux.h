#ifndef __NUX_H__
#define __NUX_H__

/********************************************************************
 * /=================================\
 * | COCOS2D-X "NUX" EXTENSIONS PACK |
 * \=================================/
 *
 * @authors
 *  - Paweł Kaczyński
 *
 * "Nux" (from latin "nut") contains many tools simplifying creation
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

// Nux defines
#include "nuxConfig.h"

// Nux Main Packages
#include "QuickMenu/nuxQuickMenu.h"

// Nux Utility Classes
#include "Utils/XMLDocument/nuxXMLDocument.h"
#include "Utils/MessageHandler/nuxMessageHandler.h"
#include "Utils/StringUtilities/nuxStringUtilities.h"

// Nux Test file
#include "nuxTest.h"

NS_NUX_BEGIN

NUX_DLL const char* nuxVersion ();

NS_NUX_END

#endif  // __NUX_H__