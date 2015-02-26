#include "../../include/QuickMenu/xxQuickMenu.h"

USING_NS_XX;

bool QuickMenu::prepare (cocos2d::Layer * layer) {
    if (!layer) {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Requested menu creation on invalid layer.");
    }
    else if (content.empty ()) {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Menu preparation failed: Content is empty.");
    }

    this->layer = layer;

    if (revAttrStack.top ()->name == "Menu")
        this->addMenu ();
    else {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Invalid root closing tag. Preparing menu failed.");
    }


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
        Node * node = revAttrStack.top ();

        // Menu tag.
        if (node->name == "Menu") {

            // New menu -> recursive call.
            if (node->type == Node::NON_EMPTY_TAG_END) {
                addMenu ();
                // !!!! REGISTER TRANSISTIONS
            }
            // Register menu and return.
            else if (node->type == Node::NON_EMPTY_TAG_BEGIN) {

                // ????
            }
        }

        // MenuItem tag
        else if (node->type == Node::NON_EMPTY_TAG_BEGIN || 
                 node->type == Node::EMPTY_TAG) {
            this->addMenuItem ();
            

            // ????
        }
        else if (node->name == "Item" && node->type == Node::NON_EMPTY_TAG_END) {
            continue;
        }

    }

    // !!!!! REMEMBER TO REVERSE THE ITEM VECTOR

}

void QuickMenu::addMenuItem () {
    // Get MenuItem tag and pop it.
    Node * node = revAttrStack.top ();
    revAttrStack.pop ();

    if (node->name == "Image") {
        MIImage * newItem = MIImage::create ();
        this->addImageAttributes (newItem);
        pendingItems.push (newItem);
    }
    else if (node->name == "Label") {
        MIFont * newItem = MIFont::create ("TEXT NOT FOUND");
        this->addFontAttributes (newItem);
        pendingItems.push (newItem);
    }
}

void QuickMenu::addImageAttributes (MIImage * item) {

}

void QuickMenu::addFontAttributes (MIFont * item) {

}

void QuickMenu::addCommonAttributes () {

}

