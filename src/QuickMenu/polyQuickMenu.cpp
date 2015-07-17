#include "QuickMenu/polyQuickMenu.h"

USING_NS_POLY;

// =========================
// QuickMenu class methods
// =========================
bool QuickMenu::prepare (cocos2d::Layer * layer) {
    if (!layer) {
        POLY_ERROR_RETURN_FALSE ("<QuickMenu> Requested menu creation on invalid layer.");
    }
    else if (content.empty ()) {
        POLY_ERROR_RETURN_FALSE ("<QuickMenu> Menu preparation failed: Content is empty.");
    }

    this->layer = layer;

    if (revAttrStack.top ().name == "Menu")
        this->addMenu ();
    else {
        POLY_ERROR_RETURN_FALSE ("<QuickMenu> Invalid root closing tag. Preparing menu failed.");
    }

    // Display the last menu.
    if (menus.size () > 0) {
        menus.back ().setVisible (true);
    }

    // TEMP
    addTransition ();

    return true;
}

void QuickMenu::setContent (XMLDocument & xmlDocument) {
    this->content = *xmlDocument.getContent ();
    this->revAttrStack = *xmlDocument.getRevAttrStack ();
}

bool QuickMenu::setContentFromFile (const std::string & filename) {
    XMLDocument xmlDocument = XMLDocument (filename);
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

    while (!revAttrStack.empty ()) {
        Node node = revAttrStack.top ();

        // Possible nested submenu.
        if (node.type == Node::NON_EMPTY_TAG_END) {
            if (node.name == "Image" || node.name == "Label") {
                revAttrStack.pop ();

                node = revAttrStack.top ();

                // New menu -> recursive call. Save pending items in temp. container.
                if (node.type == Node::NON_EMPTY_TAG_END && node.name == "Menu") {
                    PendingItems tempItems = pendingItems;
                    addMenu ();
                    pendingItems = tempItems;

                    // !!!! REGISTER TRANSISTIONS
                    // Take last added MenuObject as a target.
                }
                else {
                    POLY_ERROR_RETURN ("<QuickMenu> Invalid submenu declaration.");
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
                menu->setVisible (false);

                // Add menu attributes
                revAttrStack.pop ();
                this->addMenuAttributes (menu);

                // Add MenuObject
                menus.push_back (MenuObject (menu));

                return;
            }

            // Insert new menu item.
            else if (node.name == "Image" || node.name == "Label") {
                this->addMenuItem ();

                // TODO Add Transitions to just created menus
                // ...take previously added target and add callback.
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
        MIFont * newItem = MIFont::create ("Default label");
        pendingItems.push (newItem);
        this->addFontAttributes (newItem);
    }
}

void QuickMenu::addMenuAttributes (cocos2d::Menu * menu) {
    Node node = revAttrStack.top ();
    float padding = 0.f;
    std::string align = "";

    while (node.type == Node::ATTRIBUTE) {
        if (node.name == "Align" && node.value.size () > 0) {
            align = node.value;
        }
        else if (node.name == "Padding" && node.value.size () > 0) {
            padding = StringUtilities::convertFromString<float> (node.value);
        }

        revAttrStack.pop ();
        node = revAttrStack.top ();
    }

    if (align == "Vertically") {
        menu->alignItemsVerticallyWithPadding (padding);
    }
    else if (align == "Horizontally") {
        menu->alignItemsHorizontallyWithPadding (padding);
    }
}

void QuickMenu::addImageAttributes (MIImage * item) {
    // Add image attributes.
    Node node = revAttrStack.top ();
    while (node.type == Node::ATTRIBUTE) {
        if (node.name == "Normal" && node.value.size () > 0) {
            cocos2d::Sprite * img = cocos2d::Sprite::create (node.value);
            item->setNormalImage (img);
        }
        else if (node.name == "Selected" && node.value.size () > 0) {
            cocos2d::Sprite * img = cocos2d::Sprite::create (node.value);
            item->setSelectedImage (img);
        }
        else {
            this->addCommonAttributes (item);
        }

        revAttrStack.pop ();
        node = revAttrStack.top ();
    }
}

void QuickMenu::addFontAttributes (MIFont * item) {
    // Add image attributes.
    Node node = revAttrStack.top ();
    while (node.type == Node::ATTRIBUTE) {
        if (node.name == "Text" && node.value.size () > 0) {
            item->setString (node.value);
        }
        else {
            this->addCommonAttributes (item);
        }

        revAttrStack.pop ();
        node = revAttrStack.top ();
    }
}

void QuickMenu::addTransition () {// (cocos2d::Menu * menu) {
    cocos2d::MenuItem * item = static_cast<cocos2d::MenuItem*>(menus.back ().getMenu ()->getChildByName ("label_1"));
    //item->setCallback (CC_CALLBACK_1 (QuickMenu::Transition::callback, QuickMenu::Transition));
    item->setCallback ([] (Ref* pSender) {QuickMenu::callback (pSender); });
}

void QuickMenu::addCommonAttributes (cocos2d::MenuItem * item) {
    // Add common attributes.
    Node node = revAttrStack.top ();

    if (node.name == "Color" && node.value.size () > 0) {
        item->setColor (StringUtilities::getColor3BFromHex (node.value));
    }
    else if (node.name == "Name" && node.value.size () > 0) {
        item->setName (node.value);
    }
}

// =========================
// MenuObject class methods
// =========================
QuickMenu::MenuObject::MenuObject (cocos2d::Menu * menu)
    : menu (menu) {

}

void QuickMenu::MenuObject::setVisible (bool isVisible) {
    this->menu->setVisible (isVisible);
}
