#ifndef __XX_MACROS_H__
#define __XX_MACROS_H__

// Errors messages
#define XX_ERROR(message) xx::MessageHandler::printMessage (message, xx::MessageHandler::_ERROR)
#define XX_ERROR_RETURN_FALSE(message) xx::MessageHandler::printMessage (message, xx::MessageHandler::_ERROR); return false


#endif // __XX_MACROS_H__