#include "../../../include/Utils/MessageHandler/xxMessageHandler.h"

USING_NS_XX;

void MessageHandler::printMessage (const std::string message, Type type) {
    std::string output = "";

    switch (type) {
        case _NO_FORMAT:
            output = message;
            break;
        case _ERROR :
            output = "   <!!!> ERROR : " + message + "\n";
            break;
        case _WARNING:
            output = "   <?> Warning : " + message + "\n";
            break;
        case _INFO:
            output = "   > Information <  " + message + "\n";
            break;
        case _TIME:
            output = "   ============ Time:\t" + message + " [sec] ====\n";
            break;

        default:
            break;
    }

#ifdef COCOS2D_DEBUG
    CCLOG (output.c_str());
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