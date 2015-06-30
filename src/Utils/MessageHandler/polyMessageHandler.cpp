#include "Utils/MessageHandler/polyMessageHandler.h"

USING_NS_POLY;

// Static init.
std::map <MessageHandler::Type, std::string> MessageHandler::MsgHeaders = MessageHandler::fillMsgHeaders ();

void MessageHandler::printMessage (const std::string message, Type type) {
    std::string output = "";

    output += MsgHeaders[type] + message;

    if (type == _TIME)
        output += " [sec] ====";

    output += "\n";

#ifdef COCOS2D_DEBUG
    POLY_LOG (output.c_str ());
#endif
}

void MessageHandler::printDebugSection (const std::string title, bool isBegin) {
    if (isBegin) {
        std::cout << "====== Debug section: " << title << " ======\n";
    }
    else {
        std::cout << std::setw (10 + title.size ()) << std::setfill ('=') << "" << " End of section ===\n\n";
        std::cout << std::setfill (' ');
    }
}

std::map<MessageHandler::Type, std::string> MessageHandler::fillMsgHeaders () {
    std::map <MessageHandler::Type, std::string> newMap;

    newMap[MessageHandler::_NO_FORMAT] = "   ";
    newMap[MessageHandler::_ERROR] = "   <!!!> ERROR : ";
    newMap[MessageHandler::_INFO] = "   > Information <  ";
    newMap[MessageHandler::_WARNING] = "   <?> Warning : ";
    newMap[MessageHandler::_TIME] = "   ============ Time:\t";

    return newMap;
}
