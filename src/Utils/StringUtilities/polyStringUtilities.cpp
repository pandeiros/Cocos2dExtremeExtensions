#include "Utils/StringUtilities/polyStringUtilities.h"

USING_NS_POLY;

void StringUtilities::replaceKeyword (const std::string & keyword, const std::string & value, std::string & text) {
    // If keyword is not found, print an error.
    unsigned int keywordPos = text.find (keyword);
    if (keywordPos == std::string::npos) {
        POLY_ERROR_RETURN ("Keyword '" + keyword + "' cannot be found!");
    }

    // Otherwise...
    while (keywordPos != std::string::npos) {
        std::string before = "", after = "";
        before = text.substr (0, keywordPos);
        after = text.substr (keywordPos + keyword.size (), text.size () - (keywordPos + keyword.size ()));

        text = before + value + after;
        keywordPos = text.find (keyword);
    }
}

cocos2d::Color3B StringUtilities::getColor3BFromHex (const std::string & color) {
    // #ff00ff or #f0f
    POLY_ASSERT (color[0] == '#' && (color.size () == 4 || color.size () == 7));

    std::string red = "", green = "", blue = "";
    unsigned int iRed, iGreen, iBlue;
    std::stringstream ss;

    // Short form.
    if (color.size () == 4) {
        red = color.substr(1,1);
        green = color.substr (2, 1);
        blue = color.substr (3, 1);
        red += red;
        green += green;
        blue += blue;
    }
    // Full form.
    else {
        red = color.substr (1, 2);
        green = color.substr (3, 2);
        blue = color.substr (5, 2);
    }

    // Convert to ints.
    ss << std::hex << red;
    ss >> iRed;
    ss.clear ();

    ss << std::hex << green;
    ss >> iGreen;
    ss.clear ();

    ss << std::hex << blue;
    ss >> iBlue;

    return cocos2d::Color3B (iRed, iGreen, iBlue);
}
