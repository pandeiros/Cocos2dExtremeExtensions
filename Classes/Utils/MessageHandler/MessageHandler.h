#ifndef __MESSAGE_HANDLER_H__
#define __MESSAGE_HANDLER_H__

#ifdef COCOS2D_DEBUG
#include "cocos2d.h"
#endif

#include "../../xxDefines.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <map>

/**
    Non-instantiable class for displaying formatted message results.
    Provides 3 message types: errors, warnings and information messages.
    Contains predefined templates for popular messages.
*/
class XX_DLL MessageHandler {
public:
    // Message type
    enum Type {
        _UNKNOWN,
        _NO_FORMAT,
        _INFO,
        _WARNING,
        _ERROR,
        _TIME
    };

    // TODO Implement later.
    // Message type headers.
    //static const std::map <Type, std::string> ErrorHeaders;

    // Prints custom message.
    // \param string message : Message to be display
    // \param (opt) Type type : Type of the message.
    // \see MessageHandler::Type
    static void printMessage (const std::string message, Type type = Type::_UNKNOWN);

    // Prints custom debug section indicator.
    // \param string title : Debug section title.
    // \param bool isBegin : True if start of the sectiom false if end.
    static void printDebugSection (const std::string title, bool isBegin);
};

#endif

