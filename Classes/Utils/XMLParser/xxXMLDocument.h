#ifndef __XX_XML_DOCUMENT_H__
#define __XX_XML_DOCUMENT_H__

#define xxXML XMLDocument

#include "xxConfig.h"

#include "xxXMLDocumentDefines.h"
#include "Utils/MessageHandler/xxMessageHandler.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

NS_XX_BEGIN

class XX_DLL XMLDocument {
public:
    // Types of nodes to be stored in the XML content.
    class XMLNode {
    public:
        enum Type {
            NONE, HEADER, EMPTY_TAG, NON_EMPTY_TAG_BEGIN, NON_EMPTY_TAG_END, ATTRIBUTE
        } type;

        std::string name = "";
        std::string value = "";
    };

    // Constructor with filename argument.
    // \param string filename : Name of the XML document.
    XMLDocument (const std::string filename);

    // Main storage type for XML Nodes.
    typedef std::vector <XMLNode> Content;

    // Contains XML Nodes but in different order :
    // First come the attributes from the last one to the first and
    // then the node itself. Nodes are put in normal order.
    typedef std::stack <XMLNode*> RevAttrStack;

    // Return pointer to the XML Content.
    Content * getContent ();

    // Return pointer to node stack.
    RevAttrStack * getRevAttrStack ();

private:

    /**
     * XML file parser. Saves XML document in a vector of XMLNodes (linear algorithm, linear storage).
     */
    class XX_DLL XMLParser {
    public:
        // Constructor with filename argument.
        // \param string filename : Name of the file to be parsed.
        XMLParser (const std::string filename);

        // Prints debug information about the XML structure via MessageHandler class.
        void printAll ();

        // Return pointer to the XML Content.
        Content * getContent ();

        // Return pointer to node stack.
        RevAttrStack * getRevAttrStack ();

    private:
        // Parse given file. Returns true if operation was successful, false otherwise.
        bool parse ();

        // Prepare RevAttrStack based on Content.
        void prepareRevAttrStack ();

        /// Specific parsing methods sharing the same 'content' with XML document.

        bool openFile (std::string & content);          // Opens specified file and copies content of it to std::string variable.
        bool parseContent (std::string & content);      // Parse content outside of any tag or comment.
        bool parseTag (std::string & content);          // Parse tag and its attributes.
        bool parseAttribute (std::string & content);    // Parse attribute and its value.
        bool parseComment (std::string & content);      // Parse comment.
        inline bool checkCharacter (const char c);

        // XMLNodes storage for a particular instance of this class.
        Content content;

        // Stack of XML Nodes with reverse attributes order.
        RevAttrStack revAttrStack;

        // Different states for parser to be in.
        enum State {
            NONE, TAG_NAME, TAG_INSIDE, ATTR_NAME, ATTR_VALUE, NEMPTY_TAG_END,
            POSSIBLE_COMMENT, COMMENT, POSSIBLE_COMMENT_END,
        };

        // Name of the file to be parsed.
        std::string mFilename = "";

        /// Parsing variables.

        unsigned int index = 0;     // Number of currently processed character.
        unsigned int nested = 0;    // Number of currently nested tags (should be 0 at the end of parsing).
        unsigned int lines = 1;     // Number of the line currently processed from the file.
        int insertPos = -1;         // Position for tag to be inserted (cause its attributes are inserted first).
        char ch = ' ';              // Currently parsed character.
        bool eof = false;           // True if 'index' reached last character in a file. False otherwise.
        bool isHeader = false;      // Conditional variable to specify tag as a header type tag.
        State state = NONE;         // State that parser is currently in.

    };  // XMLParser class.

    class XX_DLL XMLSchema {

    };

    XMLParser xmlParser;

    XMLSchema xmlSchema;
};

NS_XX_END

#endif  // __XX_XML_DOCUMENT_H__