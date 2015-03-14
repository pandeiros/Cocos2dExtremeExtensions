#include "../../include/QuickMenu/xxQuickMenu.h"

USING_NS_XX;

// =========================
// QuickMenu class methods
// =========================
bool QuickMenu::prepare (cocos2d::Layer * layer) {
    if (!layer) {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Requested menu creation on invalid layer.");
    }
    else if (content.empty ()) {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Menu preparation failed: Content is empty.");
    }

    this->layer = layer;

    if (revAttrStack.top ().name == "Menu")
        this->addMenu ();
    else {
        XX_ERROR_RETURN_FALSE ("<QuickMenu> Invalid root closing tag. Preparing menu failed.");
    }


    // === TEMP
    //MenuItemVector vec;
    //for (int i = 0; i < 2; ++i) {
    //cocos2d::MenuItemImage * newItem = cocos2d::MenuItemImage::create ("btnNormal.png", "btnSelected.png");
    //vec.pushBack (newItem);
    //}
    //cocos2d::Menu * menu = cocos2d::Menu::createWithArray (vec);
    //menu->alignItemsVerticallyWithPadding (10.f);
    ////menu->alignItemsInColumns (1, 2, 4, 3, NULL);
    //layer->addChild (menu, 10);
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

    while (!revAttrStack.empty()) {
        Node node = revAttrStack.top ();

        // Possible nested submenu.
        if (node.type == Node::NON_EMPTY_TAG_END) {
            if (node.name == "Image" || node.name == "Label") {
                revAttrStack.pop ();

                node = revAttrStack.top ();

                // New menu -> recursive call.
                if (node.type == Node::NON_EMPTY_TAG_END && node.name == "Menu") {
                    addMenu ();
                    // !!!! REGISTER TRANSISTIONS
                }
                else {
                    XX_ERROR_RETURN ("<QuickMenu> Invalid submenu declaration.");
                }

            }
        }

        // Possible end of menu declaration.
        else if (node.type == Node::NON_EMPTY_TAG_BEGIN) {

            // Insert new menu.
            if (node.name == "Menu") {
                // Reverse MenuItems
                MenuItemVector menuItems;
                while (!pendingItems.empty ()) {
                    menuItems.pushBack (pendingItems.top ());
                    pendingItems.pop ();
                }

                // Create menu. Add to layer.
                cocos2d::Menu * menu = cocos2d::Menu::createWithArray (menuItems);
                layer->addChild (menu);

                // Add menu attributes
                revAttrStack.pop ();
                node = revAttrStack.top ();
                while (node.type == Node::ATTRIBUTE) {
                    // TEMP Default aligmnment.
                    menu->alignItemsVertically ();

                    revAttrStack.pop ();
                    node = revAttrStack.top ();
                }

                // Add MenuObject
                menus.push_back (MenuObject (menu));
                // TODO Add Transitions.

                return;
            }

            // Insert new menu item.
            else if (node.name == "Image" || node.name == "Label") {
                this->addMenuItem ();
            }
        }

        // MenuItem tag
        else if (node.type == Node::EMPTY_TAG) {
            this->addMenuItem ();

            continue;
            // ????
        }

        revAttrStack.pop ();
    }

    // !!!!! REMEMBER TO REVERSE THE ITEM VECTOR

}

void QuickMenu::addMenuItem () {
    // Get MenuItem tag and pop it.
    Node node = revAttrStack.top ();
    revAttrStack.pop ();

    if (node.name == "Image") {
        MIImage * newItem = MIImage::create ();
        pendingItems.push (newItem);
        this->addImageAttributes (newItem);
    }
    else if (node.name == "Label") {
        MIFont * newItem = MIFont::create ("TEXT NOT FOUND");
        pendingItems.push (newItem);
        this->addFontAttributes (newItem);
    }
}

void QuickMenu::addImageAttributes (MIImage * item) {
    // Add image attributes.
    Node node = revAttrStack.top ();
    while (node.type == Node::ATTRIBUTE) {
        if (node.name == "Normal" && node.value.size() > 0) {
            cocos2d::Sprite * img = cocos2d::Sprite::create (node.value);
            item->setNormalImage (img);
        }
        else if (node.name == "Selected" && node.value.size () > 0) {
            cocos2d::Sprite * img = cocos2d::Sprite::create (node.value);
            item->setSelectedImage (img);
        }

        revAttrStack.pop ();
        node = revAttrStack.top ();
    }
}

void QuickMenu::addFontAttributes (MIFont * item) {

}

void QuickMenu::addCommonAttributes () {

}

// =========================
// MenuObject class methods
// =========================
QuickMenu::MenuObject::MenuObject (cocos2d::Menu * menu)
    : menu (menu) {

}