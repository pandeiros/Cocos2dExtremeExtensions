#ifndef __POLY_QUICK_MENU_H__
#define __POLY_QUICK_MENU_H__

#include "../polyConfig.h"

#include "polyQuickMenuDefines.h"
#include "Utils/XMLDocument/polyXMLDocument.h"
#include "Utils/StringUtilities/polyStringUtilities.h"
#include "ui/UILayout.h"

#include <stack>

NS_POLY_BEGIN

/**
 * QuickMenu provides quick and easy cocos2d::Menu creation based on a XML file.
 *
 * Features:
 *  - Support Image and Label menu item types.
 *  - Attributes for MenuItems
 *  - (Under dev.) Attributes for Menu.
 *  - (TBA) Different MenuItems alignment in Menu.
 *  - (TBA) Nested submenus.
 *  - (TBA) Transitions between submenus.
 *  - (TBA) Hover functionality for menu items.
 *
 * For sample QuickMenu XML file, check TestScenes/QuickMenu/QuickMenuExample.xml
 */
class POLY_DLL QuickMenu : private cocos2d::Ref
{
public:
    /**
     * Create empty QuickMenu. You can call setContent() and
     * prepare() methods subsequently.
     * @return Autoreleased QuickMenu object.
     */
    CREATE_FUNC(QuickMenu)

    /**
     * Create QuickMenu with content. You can call prepare() method
     * subsequently to assign layer.
     * @param string filename : Path to file for XMLDocument to load content.
     * @return Autoreleased QuickMenu object.
     */
    POLY_CREATE_WITH_FILE_FUNC(QuickMenu)

    /**
     * Create empty QuickMenu with content and layer assigned.
     * @param Layer layer : Cocos2d layer for menu to be assigned to.
     * @param string filename : Path to file for XMLDocument to load content.
     * @return Autoreleased QuickMenu object.
     */
    QM_CREATE_FULL_FUNC

    /**
     * Assign layer and create menu objects.
     * @param Layer* layer : Cocos2d layer for menu to be assigned to.
     * @return True if success.
     */
    bool prepare(cocos2d::Layer * layer);

    /**
     * Set content of XML document from a reference.
     * @param XMLDocument xmlDocument : Reference to object to get XML content from.
     */
    void setContent(XMLDocument & xmlDocument);

    /**
     * Set content of XML document from a reference.
     * @param string filename : Path to file for XMLDocument to load content.
     */
    bool setContentFromFile(const std::string & filename);
    static void callback(cocos2d::Ref* pSender)
    {
        cocos2d::Director::getInstance()->end();
    }

private:
    // Vector of MenuItems* to be assigned to Menu.
    typedef cocos2d::Vector<cocos2d::MenuItem*> MenuItemVector;

    // Stack of MenuItems* currently being processed and wait for assigment.
    typedef std::stack<cocos2d::MenuItem*> PendingItems;

    // Shorter forms.
    typedef cocos2d::MenuItemImage MIImage;
    typedef cocos2d::MenuItemFont MIFont;
    typedef XMLDocument::XMLNode Node;

    /**
     * Helper class to set up transitions between menus/submenus.
     */
    class POLY_DLL Transition
    {
    public:

    private:

    };

    /**
     * Container for cocos2d::Menu and related transitions.
     */
    class POLY_DLL MenuObject
    {
    public:
        /**
         * Constructor with cocos2d::Menu* parameter.
         * @param cocos2d::Menu * menu : Pointer to menu to be stored in this object.
         */
        MenuObject(cocos2d::Menu * menu);

        /**
         * Set menu's visibility.
         * @param bool isVisible : True if menu is visible as a layer's child.
         */
        void setVisible(bool isVisible);

        cocos2d::Menu * getMenu()
        {
            return menu;
        }

    private:
        // Menu itself.
        cocos2d::Menu * menu;

        // (optional) Transition to other menu/submenu.
        Transition transition;
    };

    /**
     * Initialize empty QuickMenu with nullptr layer.
     * @return True if success.
     */
    POLY_INIT_FUNC;

    /**
     * Initialize QuickMenu with content from a file.
     * @param string filename : Path to file for XMLDocument to load content.
     * @return True if success.
     */
    POLY_INIT_WITH_FILE_FUNC;

    /**
     * Add new Menu/Submenu with attributes and transitions.
     */
    void addMenu();

    /**
     * Add new MenuItem with attributes.
     */
    void addMenuItem();

    /**
     * Add attribute to lastly created Menu.
     * @param cocos2d::Menu * menu : Currently processed menu.
     */
    void addMenuAttributes(cocos2d::Menu * menu);

    /**
     * Add common attributes to lastly created MenuItem.
     * @param cocos2d::MenuItem * item : Currently processed menu item.
     */
    void addCommonAttributes(cocos2d::MenuItem * item);

    /**
     * Add attributes to lastly created MenuItemImage.
     * @param cocos2d::MenuItemImage * item : Currently processed image.
     */
    void addImageAttributes(MIImage * item);

    /**
     * Add attributes to lastly created MenuItemFont.
     * @param cocos2d::MenuItemFont * item : Currently processed font.
     */
    void addFontAttributes(MIFont * item);

    /**
     * Add transition between menus/submenus.
     */
    void addTransition();// cocos2d::Menu * menu);

    // Container for MenuObjects
    std::vector<MenuObject> menus;

    // Items waiting for assignment.
    PendingItems pendingItems;

    // Pointer to cocos2d Layer which holds Menu(s).
    cocos2d::Layer * layer;

    // TODO IS CONTENT REALLY NEEDED?
    // XML Document content with Menu(s) structure.
    XMLDocument::Content content;

    // XML Node stack for MenuItems assignment.
    XMLDocument::RevAttrStack revAttrStack;
};

NS_POLY_END

#endif  // __POLY_QUICK_MENU_H__
