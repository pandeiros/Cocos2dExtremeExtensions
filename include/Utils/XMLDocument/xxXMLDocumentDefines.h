#ifndef __XX_XML_PARSER_DEFINES_H__
#define __XX_XML_PARSER_DEFINES_H__

// Reading next character from string content
#define XML_READ_ONE_CHAR(content) \
    if (eof) { \
        return (nested == 0); \
    } \
    else if (index < content.size()) { \
        ch = content[index++]; \
        if (ch == '\n') { ++lines; } \
        if (index == content.size()) { eof = true; } \
    }

#endif  // __XX_XML_PARSER_DEFINES_H__