#include "xxXMLParser.h"

USING_NS_XX;

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

void XMLParser::printAll () {
    std::string indent = "";
    for (XMLNode & node : scheme) {
        std::string attrIndent = "";

        if (node.type == XMLNode::ATTRIBUTE)
            attrIndent = "  + ";
        else if (node.type == XMLNode::NON_EMPTY_TAG_END)
            indent = indent.substr (0, indent.size () - 3);

        MessageHandler::printMessage (indent + attrIndent + node.name + " " + node.value, MessageHandler::_NO_FORMAT);

        if (node.type == XMLNode::NON_EMPTY_TAG_BEGIN)
            indent += "   ";

    }
}

XMLParser::Scheme * XMLParser::getScheme () {
    return &scheme;
}

bool XMLParser::openFile (std::string & content) {
    // Check filename.
    if (mFilename == "") {
        XX_ERROR_RETURN_FALSE ("Requested file parsing on empty filename!");
    }

    std::ifstream xmlFile;

    // Open file
    xmlFile.open (mFilename, std::ios::in);
    if (!xmlFile.is_open ()) {
        XX_ERROR_RETURN_FALSE ("Cannot open XML config file! (file: " + mFilename + ")");
    }

    std::stringstream ss;

    // Copy file content into std::string.
    ss << xmlFile.rdbuf ();
    content = ss.str ();

    return true;
}

bool XMLParser::parseContent (std::string & content) {
    while (true) {

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
                    if (!this->parseTag (content))
                        return false;
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid header tag name (line " + std::to_string (lines) + ").");
                }
            }

            // Possible Comment.
            else if (XML_CHECK_EXCLAM) {
                if (!this->parseComment (content))
                    return false;
            }

            // Tag.
            else if (XML_CHECK_ALFANUM || XML_CHECK_SLASH) {
                if (!this->parseTag (content))
                    return false;
            }
            else {
                std::string temp = "";
                temp += ch;
                XX_ERROR_RETURN_FALSE ("Invalid character combination '<" + temp + "' (line " + std::to_string (lines) + ").");
            }

        }
        else {
            XX_ERROR_RETURN_FALSE ("Invalid first character in XML content (line " + std::to_string (lines) + ").");
        }
    }
    return true;
}

bool XMLParser::parseTag (std::string & content) {
    // Prepare new node.
    XMLNode node;
    node.type = XMLNode::NONE;
    state = XMLParser::TAG_NAME;
    ++nested;

    // Check for closing tag.
    if (ch == '/') {
        state = XMLParser::NEMPTY_TAG_END;
    }
    else {
        node.name += ch;
    }

    // Check for header.
    if (isHeader)
        node.type = XMLNode::HEADER;

    bool isFinished = false;

    // Parse tag.
    while (!isFinished) {
        XML_READ_ONE_CHAR (content);

        switch (state) {
            case XMLParser::TAG_NAME:
                if (XML_CHECK_ALFANUM)
                    node.name += ch;
                else if (XML_CHECK_SPACE) {
                    insertPos = scheme.size ();
                    state = TAG_INSIDE;
                }
                else if (XML_CHECK_CLOSE_BRACKET) {
                    isFinished = true;
                    node.type = XMLNode::NON_EMPTY_TAG_BEGIN;
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid tag name character (line " + std::to_string (lines) + ").");
                }
                break;

            case XMLParser::NEMPTY_TAG_END:
                if (XML_CHECK_ALFANUM)
                    node.name += ch;
                else if (XML_CHECK_CLOSE_BRACKET) {
                    node.type = XMLNode::NON_EMPTY_TAG_END;
                    isFinished = true;
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid tag name character (line " + std::to_string (lines) + ").");
                }
                break;

            case XMLParser::TAG_INSIDE:
                if (XML_CHECK_SPACE)
                    continue;
                else if (XML_CHECK_ALFANUM) {
                    if (!this->parseAttribute (content))
                        return false;

                    state = TAG_INSIDE;
                }
                else if (XML_CHECK_CLOSE_BRACKET) {
                    if (isHeader) {
                        XX_ERROR_RETURN_FALSE ("Wrong header tag type! Has to be 'empty-tag' (line " + std::to_string (lines) + ").");
                    }
                    else {
                        node.type = XMLNode::NON_EMPTY_TAG_BEGIN;
                        isFinished = true;
                    }
                }
                else if (XML_CHECK_SLASH) {
                    if (isHeader) {
                        XX_ERROR_RETURN_FALSE ("Wrong header tag type! Has to be 'empty-tag' (line " + std::to_string (lines) + ").");
                    }
                    else if (XML_CHECK_NEXT_CHAR ('>')) {
                        ++index;
                        node.type = XMLNode::EMPTY_TAG;

                        isHeader = false;
                        //--nested;
                        isFinished = true;
                    }
                    else {
                        XX_ERROR_RETURN_FALSE ("Invalid tag closing (line " + std::to_string (lines) + ").");
                    }
                }
                else if (XML_CHECK_QUESTION) {
                    if (!isHeader) {
                        XX_ERROR_RETURN_FALSE ("Header type tags are not allowed here (line " + std::to_string (lines) + ").");
                    }
                    else if (XML_CHECK_NEXT_CHAR ('>')) {
                        ++index;
                        node.type = XMLNode::HEADER;

                        isHeader = false;
                        //--nested;
                        isFinished = true;
                    }
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid character used inside the tag (line " + std::to_string (lines) + ").");
                }
                break;
        }
    }

    // If attributes were not inserted, just push back a new node.
    if (insertPos == -1 || insertPos == scheme.size ())
        scheme.push_back (node);
    else {
        // Otherwise insert tag before its attributes.
        Scheme::iterator iter = scheme.begin ();
        scheme.insert (iter + insertPos, node);
    }

    --nested;
    insertPos = -1;

    return true;
}

bool XMLParser::parseAttribute (std::string & content) {
    state = XMLParser::ATTR_NAME;
    ++nested;

    // Prepare new node.
    XMLNode node;
    node.type = XMLNode::ATTRIBUTE;
    node.name += ch;

    bool isFinished = false;

    while (!isFinished) {
        XML_READ_ONE_CHAR (content);

        switch (state) {
            case XMLParser::ATTR_NAME:
                if (XML_CHECK_ALFANUM)
                    node.name += ch;
                else if (XML_CHECK_EQUAL) {
                    if (XML_CHECK_NEXT_CHAR ('"')) {
                        ++index;
                        state = ATTR_VALUE;
                    }
                    else {
                        XX_ERROR_RETURN_FALSE ("Invalid attribute value opening character (line " + std::to_string (lines) + ").");
                    }
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid attribute name (line " + std::to_string (lines) + ").");
                }
                break;

            case XMLParser::ATTR_VALUE:
                if (XML_CHECK_QUOTE) {
                    scheme.push_back (node);
                    --nested;
                    isFinished = true;
                }
                else {
                    node.value += ch;
                }
                break;
        }
    }

    return true;
}

bool XMLParser::parseComment (std::string & content) {
    state = XMLParser::POSSIBLE_COMMENT;

    bool isFinished = false;

    while (!isFinished) {
        XML_READ_ONE_CHAR (content);

        switch (state) {
            case XMLParser::POSSIBLE_COMMENT:
                if (XML_CHECK_DASH) {
                    if (XML_CHECK_NEXT_CHAR ('-')) {
                        ++index;
                        state = XMLParser::COMMENT;
                    }
                    else {
                        XX_ERROR_RETURN_FALSE ("Invalid comment opening (line " + std::to_string (lines) + ").");
                    }
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid comment opening (line " + std::to_string (lines) + ").");
                }
                break;

            case XMLParser::COMMENT:
                if (XML_CHECK_DASH)
                    state = XMLParser::POSSIBLE_COMMENT_END;
                else
                    continue;
                break;

            case XMLParser::POSSIBLE_COMMENT_END:
                if (XML_CHECK_DASH) {
                    if (XML_CHECK_NEXT_CHAR ('>')) {
                        ++index;
                        isFinished = true;
                        break;
                    }
                    else
                        state = XMLParser::COMMENT;
                }
                else
                    state = XMLParser::COMMENT;
                break;

            default:
                break;
        }
    }

    return true;
}