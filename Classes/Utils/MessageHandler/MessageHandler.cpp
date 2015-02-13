#include "MessageHandler.h"

void MessageHandler::printMessage (const std::string message, Type type) {
    std::string output = "";
    switch (type) {
        case _NO_FORMAT:
            output = message;
            break;
        case _ERROR :
            output = "\n<!!!> ERROR : " + message + "\n";
            break;
        case _WARNING:
            output = "\n<?> Warning : " + message + "\n";
            break;
        case _INFO:
            output = "\n   > > >  " + message + "  < < <\n";
            break;
        case _TIME:
            output = "=============== Time:\t" + message + " [sec] ====\n";
            break;

        default:
            break;
    }

#ifdef COCOS2D_DEBUG
    CCLOG (output.c_str());
#else
    std::cout << output << "\n";
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