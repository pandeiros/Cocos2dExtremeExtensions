#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

#include "../../xxDefines.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../MessageHandler/MessageHandler.h"
#include "XMLParserDefines.h"

/**
    XML file parser. 
*/
class XX_DLL XMLParser {
public:
    // Constructor with filename argument.
    // \param string filename : Name of the file to be parsed.
    XMLParser (const std::string filename);

    struct XMLNode {
        enum Type {
            NONE,
            HEADER,
            EMPTY_TAG,
            NON_EMPTY_TAG_BEGIN,
            NON_EMPTY_TAG_END,
            ATTRIBUTE
        } type;

        std::string name = "";
        std::string value = "";
    };

    typedef std::vector <XMLNode> Scheme;

    // Parse given file. Returns true if operation was successful, false otherwise.
    bool parse ();

    void printAll ();

private:
    Scheme scheme;

    bool openFile (std::string & content);
    bool parseContent (std::string & content);

    bool parseTag (std::string & content);
    bool parseAttribute (std::string & content);
    bool parseComment (std::string & content);

    enum State {
        NONE,
        TAG_NAME,
        TAG_INSIDE,
        ATTR_NAME,
        ATTR_VALUE,
        NEMPTY_TAG_END,
        POSSIBLE_COMMENT,
        COMMENT,
        POSSIBLE_COMMENT_END,
        COMMENT_END
    };

    // Name of the file to be parsed.
    std::string mFilename = "";

    // Parsing variables.
    unsigned int index = 0;
    unsigned int nested = 0;
    unsigned int lines = 1;
    unsigned int insertPos = -1;
    char ch = ' ';
    std::string s = "";    
    bool eof = false;
    bool isHeader = false;
    State state = NONE;
};

//template <typename Type>
//inline bool XMLParser::searchValue (Tag & tag, const std::string & tagName,
//                                    const std::string & attributeName, Type & value) {
//    // Check name of the tag.
//    if (tag.name == tagName) {
//
//        // Check attributes of current tag.
//        for (Attribute & attr : tag.attributes) {
//            if (attr.name == attributeName) {
//
//                // Convert string value to Type value.
//                std::stringstream ss;
//                ss.str (attr.value);
//                ss >> value;
//                return true;
//            }
//        }
//    }
//
//    // No need to go deeper.
//    if (tag.isEmpty || tag.tags.size () == 0) {
//        return false;
//    }
//    else {
//        for (Tag & childTag : tag.tags) {
//            if (searchValue (childTag, tagName, attributeName, value))
//                return true;
//        }
//    }
//
//    return false;
//}

#endif