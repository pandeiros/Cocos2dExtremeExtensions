#ifndef __POLY_STRING_UTILITIES_H__
#define __POLY_STRING_UTILITIES_H__

#include "polyConfig.h"

#include "Utils/MessageHandler/polyMessageHandler.h"

#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

NS_POLY_BEGIN

/**
 * Non-instantiable class. Provides various string operations.
 */
class StringUtilities
{
public:
    /**
     * Convert given argument from std::string to Type.
     * @typename Type : Conversion target.
     * @param string value : Value to be converted.
     */
    template <typename Type>
    static Type convertFromString(const std::string value);

    /**
     * Replace given keyword in referenced text with value.
     * @param string keyword : Keyword in text to be found and replaced.
     * @param string value : String to be inserted instead of the given keyword.
     * @param string & text : Reference to text, in which the replacement is done.
     */
    static void replaceKeyword(const std::string & keyword, const std::string & value, std::string & text);

    /**
     * Convert hex color code to cocos2d::Color3B object.
     * @param string color : Hex color code.
     * @return Color3B object.
     */
    static cocos2d::Color3B getColor3BFromHex(const std::string & color);
};


template <typename Type>
inline Type StringUtilities::convertFromString(const std::string value)
{
    std::stringstream ss;
    ss.str(value);
    Type conversion;
    ss>>conversion;
    return conversion;
}

NS_POLY_END

#endif  // __POLY_STRING_UTILITIES_H__
