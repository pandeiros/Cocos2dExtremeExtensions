#include "xxQuickMenu.h"

USING_NS_XX;

void QuickMenu::prepare (cocos2d::Layer * layer) {
    if (!layer) {
        XX_ERROR_RETURN ("<QuickMenu> Requested menu creation on invalid layer.");
    }

    currentNode = layer;

    // === TEMP
    MenuItemVector vec;
    for (int i = 0; i < 10; ++i) {
        QM_ITEM_IMAGE_N_S ("CloseNormal.png", "CloseSelected.png");
        vec.pushBack (newItem);
    }
    QM_MENU_WITH_VEC (vec);
    newMenu->alignItemsVerticallyWithPadding (10.f);
    newMenu->alignItemsInColumns (1, 2, 4, 3, NULL);
    layer->addChild (newMenu, 10);    
    // ===
}

void QuickMenu::setScheme (XMLParser::Scheme * scheme) {
    this->scheme = *scheme;
}

bool QuickMenu::setSchemeFromFile (const std::string & filename) {
    XMLParser parser = XMLParser (filename);
    if (parser.parse ()) {
        this->scheme = *parser.getScheme ();
        return true;
    }
    else
        return false;
}

bool QuickMenu::init () {
    layer = nullptr;
    return true;
}

bool QuickMenu::initWithFile (const std::string & filename) {
    layer = nullptr;
    return this->setSchemeFromFile (filename);
}

void QuickMenu::addNewElement (const std::string type) {

}
