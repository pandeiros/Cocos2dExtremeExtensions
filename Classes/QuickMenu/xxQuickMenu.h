#ifndef __XX_QUICK_MENU_H__
#define __XX_QUICK_MENU_H__

#define xxQM QuickMenu

#include "xxConfig.h"

#include "xxQuickMenuDefines.h"
#include "ui/UILayout.h"
#include "Utils/XMLParser/xxXMLParser.h"

NS_XX_BEGIN

class XX_DLL QuickMenu : public cocos2d::Ref {
public:
    bool init ();
    void setLayer (cocos2d::Layer * layer);
    void setScheme (XMLParser::Scheme * scheme);
    void setSchemeFromFile (const std::string & filename);

    CREATE_FUNC (QuickMenu)

private:
    cocos2d::Layer * layer;

    
};

NS_XX_END

#endif  // __XX_QUICK_MENU_H__