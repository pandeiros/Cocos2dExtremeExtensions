#include "../../../include/Utils/XMLDocument/xxXMLDocument.h"

USING_NS_XX;

// =========================
// XMLDocument class methods
// =========================
XMLDocument::XMLDocument (const std::string filename) : xmlParser (filename) {
}

bool XMLDocument::verifyWithSchema (const std::string filename) {
    XMLParser schemaParser (filename);
    
    if (schemaParser.getContent ()->empty ()) {
        XX_ERROR_RETURN_FALSE ("Schema verification failed! (filename: " + filename + ")");
    }

    this->xmlSchema.setContent (xmlParser.getContent ());
    this->xmlSchema.setSchema (schemaParser.getContent ());

    return xmlSchema.verify ();
}

XMLDocument::Content * XMLDocument::getContent () {
    return xmlParser.getContent ();
}

XMLDocument::RevAttrStack * XMLDocument::getRevAttrStack () {
    return xmlParser.getRevAttrStack ();
}

// =======================
// XMLParser class methods
// =======================
XMLDocument::XMLParser::XMLParser (const std::string filename) : mFilename (filename) {
    if (!this->parse ()) {
        content.clear ();
        XX_ERROR_RETURN ("Parsing file failed! (filename: " + mFilename + ")");
    }
    else
        this->prepareRevAttrStack ();
}

void XMLDocument::XMLParser::printAll () {
    std::string indent = "";
    for (XMLNode & node : content) {
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

XMLDocument::Content * XMLDocument::XMLParser::getContent () {
    return &content;
}

XMLDocument::RevAttrStack * XMLDocument::XMLParser::getRevAttrStack () {
    return &revAttrStack;
}

bool XMLDocument::XMLParser::parse () {
    std::string xmlContent = "";

    // Prepare file
    if (!this->openFile (xmlContent))
        return false;

    // Start parsing.
    if (!this->parseContent (xmlContent))
        return false;

    return true;
}

void XMLDocument::XMLParser::prepareRevAttrStack () {
    std::stack <XMLNode*> tempStack;

    for (XMLNode & node : content) {
        if (node.type == XMLNode::HEADER ||
            node.type == XMLNode::EMPTY_TAG ||
            node.type == XMLNode::ATTRIBUTE) {
            tempStack.push (&node);
        }
        else if (tempStack.empty () &&
                 node.type == XMLNode::NON_EMPTY_TAG_BEGIN) {
            tempStack.push (&node);
        }
        else if (!tempStack.empty () && (
            node.type == XMLNode::EMPTY_TAG ||
            node.type == XMLNode::NON_EMPTY_TAG_BEGIN ||
            node.type == XMLNode::NON_EMPTY_TAG_END)) {
            while (!tempStack.empty ()) {
                revAttrStack.push (tempStack.top ());
                tempStack.pop ();
            }

            tempStack.push (&node);
        }
    }
}

bool XMLDocument::XMLParser::openFile (std::string & content) {
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

bool XMLDocument::XMLParser::parseContent (std::string & content) {
    while (true) {

        // Read first character (skip white chars.)
        XML_READ_ONE_CHAR (content);

        // Continue...
        while (checkCharacter (' ') || checkCharacter ('\n')) {
            XML_READ_ONE_CHAR (content);
        }

        // If EOF, then exit.
        if (this->checkIfStop())
            return true;

        // Check for opening bracket - first allowed char.
        if (checkCharacter ('<')) {
            XML_READ_ONE_CHAR (content);

            // Possible Header Tag
            if (checkCharacter ('?')) {
                isHeader = true;

                XML_READ_ONE_CHAR (content);
                if (this->checkForElementName()) {
                    if (!this->parseTag (content))
                        return false;
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid header tag name (line " + std::to_string (lines) + ").");
                }
            }

            // Possible Comment.
            else if (checkCharacter ('!')) {
                if (!this->parseComment (content))
                    return false;
            }

            // Tag.
            else if (this->checkForElementName() || checkCharacter ('/')) {
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

bool XMLDocument::XMLParser::parseTag (std::string & content) {
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
                if (this->checkForElementName())
                    node.name += ch;
                else if (checkCharacter (' ')) {
                    insertPos = this->content.size ();
                    state = TAG_INSIDE;
                }
                else if (checkCharacter ('>')) {
                    isFinished = true;
                    node.type = XMLNode::NON_EMPTY_TAG_BEGIN;
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid tag name character (line " + std::to_string (lines) + ").");
                }
                break;

            case XMLParser::NEMPTY_TAG_END:
                if (this->checkForElementName())
                    node.name += ch;
                else if (checkCharacter ('>')) {
                    node.type = XMLNode::NON_EMPTY_TAG_END;
                    isFinished = true;
                }
                else {
                    XX_ERROR_RETURN_FALSE ("Invalid tag name character (line " + std::to_string (lines) + ").");
                }
                break;

            case XMLParser::TAG_INSIDE:
                if (checkCharacter (' '))
                    continue;
                else if (this->checkForElementName()) {
                    if (!this->parseAttribute (content))
                        return false;

                    state = TAG_INSIDE;
                }
                else if (checkCharacter ('>')) {
                    if (isHeader) {
                        XX_ERROR_RETURN_FALSE ("Wrong header tag type! Has to be 'empty-tag' (line " + std::to_string (lines) + ").");
                    }
                    else {
                        node.type = XMLNode::NON_EMPTY_TAG_BEGIN;
                        isFinished = true;
                    }
                }
                else if (checkCharacter ('/')) {
                    if (isHeader) {
                        XX_ERROR_RETURN_FALSE ("Wrong header tag type! Has to be 'empty-tag' (line " + std::to_string (lines) + ").");
                    }
                    else if (this->checkNextCharacter (content, '>')) {
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
                else if (checkCharacter ('?')) {
                    if (!isHeader) {
                        XX_ERROR_RETURN_FALSE ("Header type tags are not allowed here (line " + std::to_string (lines) + ").");
                    }
                    else if (this->checkNextCharacter (content, '>')) {
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
    if (insertPos == -1 || insertPos == this->content.size ())
        this->content.push_back (node);
    else {
        // Otherwise insert tag before its attributes.
        Content::iterator iter = this->content.begin ();
        this->content.insert (iter + insertPos, node);
    }

    --nested;
    insertPos = -1;

    return true;
}

bool XMLDocument::XMLParser::parseAttribute (std::string & content) {
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
                if (this->checkForElementName())
                    node.name += ch;
                else if (checkCharacter ('=')) {
                    if (this->checkNextCharacter (content, '"')) {
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
                if (checkCharacter ('"')) {
                    this->content.push_back (node);
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

bool XMLDocument::XMLParser::parseComment (std::string & content) {
    state = XMLParser::POSSIBLE_COMMENT;

    bool isFinished = false;

    while (!isFinished) {
        XML_READ_ONE_CHAR (content);

        switch (state) {
            case XMLParser::POSSIBLE_COMMENT:
                if (checkCharacter ('-')) {
                    if (this->checkNextCharacter (content, '-')) {
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
                if (checkCharacter ('-'))
                    state = XMLParser::POSSIBLE_COMMENT_END;
                else
                    continue;
                break;

            case XMLParser::POSSIBLE_COMMENT_END:
                if (checkCharacter ('-')) {
                    if (this->checkNextCharacter (content, '>')) {
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

bool XMLDocument::XMLParser::checkCharacter (const char c) {
    return (this->ch == c ? true : false);
}

bool  XMLDocument::XMLParser::checkNextCharacter (const std::string content, const char c) {
    return ((index < content.size () - 1 && c == content[index]) ? true : false);
}

bool  XMLDocument::XMLParser::checkForElementName () {
    return (((ch >= 48 && ch <= 57) ||
        (ch >= 65 && ch <= 90) ||
        (ch >= 97 && ch <= 122) ||
        (ch == '-') ||
        (ch == '.') ||
        (ch == '_')) ? true : false);
}

bool  XMLDocument::XMLParser::checkIfStop () {
    return ((eof && nested == 0) ? true : false);
}

// =======================
// XMLSchema class methods
// =======================
void XMLDocument::XMLSchema::setContent (Content * content) {
    this->content = content;
}

void XMLDocument::XMLSchema::setSchema (Content * schema) {
    this->schema = *schema;
}

bool XMLDocument::XMLSchema::verify () {
    

    return true;
}

