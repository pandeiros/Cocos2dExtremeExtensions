#ifndef __XX_XML_PARSER_DEFINES_H__
#define __XX_XML_PARSER_DEFINES_H__

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

#define XML_CHECK_OPEN_BRACKET ((ch == '<') ? (true) : (false))
#define XML_CHECK_CLOSE_BRACKET ((ch == '>') ? (true) : (false))
#define XML_CHECK_SPACE ((ch == ' ') ? (true) : (false))
#define XML_CHECK_WHITE_CHAR ((ch == ' ' || ch == '\n') ? (true) : (false))
#define XML_CHECK_QUESTION ((ch == '?') ? (true) : (false))
#define XML_CHECK_EXCLAM ((ch == '!') ? (true) : (false))
#define XML_CHECK_EQUAL ((ch == '=') ? (true) : (false))
#define XML_CHECK_QUOTE ((ch == '"') ? (true) : (false))
#define XML_CHECK_BACKSLASH ((ch == '\\') ? (true) : (false))
#define XML_CHECK_SLASH ((ch == '/') ? (true) : (false))
#define XML_CHECK_DASH ((ch == '-') ? (true) : (false))
#define XML_CHECK_ALFANUM (((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) ? (true) : (false))

#define XML_CHECK_STOP ((eof && nested == 0) ? (true) : (false))


#endif  // __XX_XML_PARSER_DEFINES_H__