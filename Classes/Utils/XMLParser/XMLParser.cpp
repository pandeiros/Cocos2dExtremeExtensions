#include "XMLParser.h"

XMLParser::XMLParser (const std::string filename) : mFilename (filename) {
}

bool XMLParser::parse () {
    std::string xmlContent = "";

    // Prepare file
    if (!this->openFile (xmlContent))
        return false;

    // Start parsing.
    if (!this->parseContent (xmlContent))
        return false;

    return true;
}

bool XMLParser::openFile (std::string & content) {
    // Check filename.
    if (mFilename == "") {
        MessageHandler::printMessage ("Requested file parsing on empty filename!",
                                      MessageHandler::_ERROR);
        return false;
    }

    std::ifstream xmlFile;

    // Open file
    xmlFile.open (mFilename, std::ios::in);
    if (!xmlFile.is_open ()) {
        MessageHandler::printMessage ("Cannot open XML config file! (file: " + mFilename + ")",
                                      MessageHandler::_ERROR);
        return false;
    }

    std::stringstream ss;

    // Copy file content into std::string.
    ss << xmlFile.rdbuf ();
    content = ss.str ();

    return true;
}

bool XMLParser::parseContent (std::string & content) {
    // Read first character (skip white chars.)
    XML_READ_ONE_CHAR (content);
    while (XML_CHECK_WHITE_CHAR) {
        XML_READ_ONE_CHAR (content);
    }

    // If EOF, then exit.
    if (XML_CHECK_STOP)
        return true;

    // Check for opening bracket - first allowed char.
    if (XML_CHECK_OPEN_BRACKET) {
        XML_READ_ONE_CHAR (content);

        // Possible Header Tag
        if (XML_CHECK_QUESTION) {
            isHeader = true;

            XML_READ_ONE_CHAR (content);
            if (XML_CHECK_ALFANUM) {
                this->parseTag (content);
            }
            else {
                MessageHandler::printMessage ("Invalid header tag name (line " + std::to_string (lines) + ").",
                                              MessageHandler::_ERROR);
                return false;
            }
        }

        // Possible Comment.
        else if (XML_CHECK_EXCLAM) {
            this->parseComment (content);
        }

        // Tag.
        else if (XML_CHECK_ALFANUM) {
            this->parseTag (content);
        }
        else {
            MessageHandler::printMessage ("Invalid character combination '<" + std::to_string(ch) + "' (line " + std::to_string (lines) + ").",
                                          MessageHandler::_ERROR);
            return false;
        }
        
    }
    else {
        MessageHandler::printMessage ("Invalid first character in XML content (line " + std::to_string (lines) + ").", 
                                      MessageHandler::_ERROR);
    }
    
    return true;
}

bool XMLParser::parseTag (std::string & content) {
    state = XMLParser::TAG_NAME;
    ++nested;
    
    // Prepare new node.
    XMLNode node;
    node.type = XMLNode::NONE;
    node.name += ch;
    if (isHeader)
        node.type = XMLNode::HEADER;

    return true;
}

bool XMLParser::parseAttribute (std::string & content) {

    return true;
}

bool XMLParser::parseComment(std::string & content) {
    state = XMLParser::POSSIBLE_COMMENT;

    return true;
}