#ifndef __XX_QUICK_MENU_H__
#define __XX_QUICK_MENU_H__

#define xxQM QuickMenu

#include "xxConfig.h"

#include "xxQuickMenuDefines.h"
#include "ui/UILayout.h"
#include "Utils/XMLParser/xxXMLParser.h"

#include <stack>

NS_XX_BEGIN

class XX_DLL QuickMenu : private cocos2d::Ref {
public:
    CREATE_FUNC (QuickMenu)
    CREATE_WITH_FILE_FUNC (QuickMenu)

    void prepare (cocos2d::Layer * layer);

    void setScheme (XMLParser::Scheme * scheme);
    bool setSchemeFromFile (const std::string & filename);

private:
    typedef cocos2d::Vector<cocos2d::MenuItem*> MenuItemVector;
    typedef std::stack<XMLParser::XMLNode*> PendingNodes;

    INIT_FUNC;
    INIT_WITH_FILE_FUNC;

    void addNewElement (const std::string type);
    PendingNodes pendingNodes;

    cocos2d::Layer * layer;
    XMLParser::Scheme scheme;
    cocos2d::Node * currentNode;

};

NS_XX_END

#endif  // __XX_QUICK_MENU_H__