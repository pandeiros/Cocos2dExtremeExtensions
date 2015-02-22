#ifndef __XX_XML_PARSER_DEFINES_H__
#define __XX_XML_PARSER_DEFINES_H__

// Parsing defines ==============================================
#define XML_READ_ONE_CHAR(content) \
    if (eof) { \
        return (nested == 0); \
    } \
    else if (index < content.size()) { \
        ch = content[index++]; \
        if (ch == '\n') { ++lines; } \
        if (index == content.size()) { eof = true; } \
    }

#define XML_CHECK_NEXT_CHAR(ch) ((index < content.size() - 1 && ch == content[index]) ? (true) : (false))

#define XML_CHECK_ELEM_NAME (((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) ||  \
    (ch >= 97 && ch <= 122) || (ch == '-') || (ch == '.') || (ch == '_')) ? (true) : (false))

#define XML_CHECK_STOP ((eof && nested == 0) ? (true) : (false))
// ==============================================================


// Content defines ==============================================
#define XML_TAG_EMPTY(__NODE__, __NAME__) (  \
    (__NODE__->name == __NAME__ &&  \
    __NODE__->type == XMLDocument::XMLNode::EMPTY_TAG  \
    ) ? (true) : (false))

#define XML_TAG_NEMPTY(__NODE__, __NAME__) (  \
    (__NODE__->name == __NAME__ &&  \
    __NODE__->type == XMLDocument::XMLNode::NON_EMPTY_TAG_BEGIN \
    ) ? (true) : (false))

#define XML_TAG_BOTH(__NODE__, __NAME__) (  \
    (__NODE__->name == __NAME__ &&  \
    (__NODE__->type == XMLDocument::XMLNode::EMPTY_TAG || \
    __NODE__->type == XMLDocument::XMLNode::NON_EMPTY_TAG_BEGIN) \
    ) ? (true) : (false))

#define XML_TAG_END(__NODE__, __NAME__) (  \
    (__NODE__->name == __NAME__ &&  \
    __NODE__->type == XMLDocument::XMLNode::NON_EMPTY_TAG_END \
    ) ? (true) : (false))
// ==============================================================


// Tag types defines ============================================
#define XML_IS_ATTR(__NODE__) ( \
    (__NODE__->type == XMLDocument::XMLNode::ATTRIBUTE \
    ) ? (true) : (false))

#define XML_IS_TAG_END(__NODE__) ( \
    (__NODE__->type == XMLDocument::XMLNode::NON_EMPTY_TAG_END \
    ) ? (true) : (false))

#define XML_IS_TAG_BOTH(__NODE__) (  \
    (__NODE__->type == XMLDocument::XMLNode::EMPTY_TAG || \
    __NODE__->type == XMLDocument::XMLNode::NON_EMPTY_TAG_BEGIN \
    ) ? (true) : (false))
// ==============================================================


#endif  // __XX_XML_PARSER_DEFINES_H__