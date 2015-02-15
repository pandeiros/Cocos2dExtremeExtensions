#ifndef __XX_STRING_UTILITIES_H__
#define __XX_STRING_UTILITIES_H__

#include "xxConfig.h"

#include <string>
#include <sstream>
#include <iostream>

NS_XX_BEGIN

/**
    Non-instantiable class. Provides various string operations.
*/
class StringUtilities {
public:
    // Converts given argument from std::string to Type
    template <typename Type>
    static Type convertFromString (const std::string value);

    // Replace file keyword with proper data
    // \param string keyword : Keyword in file to be found and replaced.
    // \param string value : String to be inserted instead of the given keyword.
    // \param string & text : Reference to text, in which the replacement is done.
    static void replaceKeyword (const std::string keyword, const std::string value, std::string & text);
};


template <typename Type>
inline Type StringUtilities::convertFromString (const std::string value) {
    std::stringstream ss;
    ss.str (value);
    Type conversion;
    ss >> conversion;
    return conversion;
}

NS_XX_END

#endif  // __XX_STRING_UTILITIES_H__
