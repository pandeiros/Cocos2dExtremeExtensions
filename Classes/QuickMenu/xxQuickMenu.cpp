#include "xxQuickMenu.h"

USING_NS_XX;

bool QuickMenu::prepare (cocos2d::Layer * layer) {
    if (!layer) {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Requested menu creation on invalid layer.");
    }
    else if (content.empty ()) {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Menu preparation failed: Content is empty.");
    }

    this->layer = layer;

    //if (revAttrStack.top ()->name == "Menu")

    // === TEMP
    /*MenuItemVector vec;
    for (int i = 0; i < 10; ++i) {
        QM_ITEM_IMAGE_N_S ("CloseNormal.png", "CloseSelected.png");
        vec.pushBack (newItem);
    }
    QM_MENU_WITH_VEC (vec);
    newMenu->alignItemsVerticallyWithPadding (10.f);
    newMenu->alignItemsInColumns (1, 2, 4, 3, NULL);
    layer->addChild (newMenu, 10);    */
    // ===
    
    return true;
}

void QuickMenu::setContent (xxXML & xmlDocument) {
    this->content = *xmlDocument.getContent ();
    this->revAttrStack = *xmlDocument.getRevAttrStack ();
}

bool QuickMenu::setContentFromFile (const std::string & filename) {
    xxXML xmlDocument = xxXML (filename);
    if (!xmlDocument.getContent ()->empty ()) {
        this->content = *xmlDocument.getContent ();
        this->revAttrStack = *xmlDocument.getRevAttrStack ();
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
    return this->setContentFromFile (filename);
}

void QuickMenu::addMenu () {
    // Pop </Menu> tag.
    revAttrStack.pop ();

    while (true) {
        QM_GET_TOP_NODE;
        
        // New menu item.
        if (XML_TAG_END (node, "Menu")) {
            addMenu ();
            // !!!! REGISTER TRANSISTIONS
        }
        else if (XML_TAG_NEMPTY (node, "Menu")) {

            // ????
        }
        else if (XML_IS_TAG_BOTH (node)) {
            QM_ITEM_IMAGE;
            pendingItems.push (newItem);
            
            // ????
        }
        else if (XML_IS_ATTR (node)) {
            addAttribute ();
        }
        else if (XML_TAG_END (node, "Item")) {
            continue;
        }
        
    }

    // !!!!! REMEMBER TO REVERSE THE ITEM VECTOR

}

void QuickMenu::addAttribute () {
    
}
