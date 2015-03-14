#ifndef __XX_XML_DOCUMENT_H__
#define __XX_XML_DOCUMENT_H__

#define xxXML XMLDocument

#include "../../xxConfig.h"

#include "xxXMLDocumentDefines.h"
#include "../MessageHandler/xxMessageHandler.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

NS_XX_BEGIN

/**
 * XMLDocument contains of:
 *  - XML Parser which stores content of a document and control
 *    proper XML syntax,
 *  - (TBA) XML Schema to check different classes' set of available
 *    elements and their attributes.
 */
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

    // Main storage type for XML Nodes.
    typedef std::vector <XMLNode> Content;

    // Reverse Attribute Stack.
    // Contains XML Nodes but in different order :
    // First come the attributes of the node from the last one to the first
    // and then the node itself. Nodes are put in normal order.
    typedef std::stack <XMLNode> RevAttrStack;

    /**
     * Constructor with filename argument.
     * @param string filename : Name of the XML document.
     */
    XMLDocument (const std::string filename);

    /**
     * Load XML Schema from file and check Content structure.
     * @param string filename : Path to XML Schema file.
     * @return True if success.
     */
    bool verifyWithSchema (const std::string filename);

    /**
     * Content getter.
     * @return Pointer to XMLDocument::Content
     */
    Content * getContent ();

    /**
     * Reverse Attribute Stack getter.
     * @return Pointer to XMLDocument::RevAttrStack
     */
    RevAttrStack * getRevAttrStack ();

    /**
     * Prints debug information about the XML structure via MessageHandler class.
     */
    void printAll ();

private:

    /**
     * XML file parser. Saves XML document in a vector of
     * XMLNodes (linear algorithm, linear storage).
     */
    class XX_DLL XMLParser {
    public:
        /**
         * Constructor with filename argument.
         * @param string filename : Name of the file to be parsed.
         */
        XMLParser (const std::string filename);

        /**
         * Prints debug information about the XML structure via MessageHandler class.
         */
        void printAll ();

        /**
         * Content getter.
         * @return Pointer to XMLDocument::Content
         */
        Content * getContent ();

        /**
         * Reverse Attribute Stack getter.
         * @return Pointer to XMLDocument::RevAttrStack
         */
        RevAttrStack * getRevAttrStack ();

    private:
        /**
         * Parse given file.
         * @return True if success.
         */
        bool parse ();

        /**
         * Prepare RevAttrStack based on Content.
         */
        void prepareRevAttrStack ();

        /// Specific parsing methods sharing the same 'content' with XML document.

        bool openFile (std::string & content);          // Opens specified file and copies content of it to std::string variable.
        bool parseContent (std::string & content);      // Parse content outside of any tag or comment.
        bool parseTag (std::string & content);          // Parse tag and its attributes.
        bool parseAttribute (std::string & content);    // Parse attribute and its value.
        bool parseComment (std::string & content);      // Parse comment.
        inline bool checkCharacter (const char c);
        inline bool checkNextCharacter (const std::string content, const char c);
        inline bool checkForElementName ();
        inline bool checkIfStop ();

        // Name of the file to be parsed.
        std::string mFilename = "";

        // XMLNodes storage for a particular instance of this class.
        Content content;

        // Stack of XML Nodes with reverse attributes order.
        RevAttrStack revAttrStack;

        // Different states for parser to be in.
        enum State {
            NONE, TAG_NAME, TAG_INSIDE, ATTR_NAME, ATTR_VALUE, NEMPTY_TAG_END,
            POSSIBLE_COMMENT, COMMENT, POSSIBLE_COMMENT_END,
        };

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

    /**
     * XML Schema verifier. (TBA) Check tags and their attributes, types
     * of data, nesting rules, default and obligatory values.
     */
    class XX_DLL XMLSchema {
    public:
        /**
         * Set Content to verify.
         * @param Content* content : XML Document content to verify by Schema.
         * @see XMLDocument::XMLSchema::setSchema()
         */
        void setContent (Content * content);

        /**
        * Set Schema for verification process.
        * @param Content* schema : Pointer XML Schema for content verification.
        * @see XMLDocument::XMLSchema::setContent()
        */
        void setSchema (Content * schema);

        /**
         * Verify content with given Schema.
         * @return True if success.
         */
        bool verify ();

    private:
        // Pointer to content of XML document
        Content * content;

        // Content of schema itself.
        Content schema;
    };

    // XML parser with content of a file.
    XMLParser xmlParser;

    // XML content verifier.
    XMLSchema xmlSchema;
};

NS_XX_END

#endif  // __XX_XML_DOCUMENT_H__