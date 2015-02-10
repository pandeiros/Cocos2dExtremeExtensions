#ifndef __QUICK_MENU_H__
#define __QUICK_MENU_H__

#include "../xxDefines.h"
#include "ui/UILayout.h"
#include "../Utils/XMLParser/XMLParser.h"

NS_XX_BEGIN

class XX_DLL QuickMenu {
public:
    void setLayer (cocos2d::Layer * layer);
    void setScheme (XMLParser::Scheme & scheme);
    void setSchemeFromFile (const std::string filename);

private:
    cocos2d::Layer * layer;
};

NS_XX_END

#endif  // __QUICK_MENU_H__