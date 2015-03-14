#ifndef __XX_QUICK_MENU_H__
#define __XX_QUICK_MENU_H__

#define xxQM QuickMenu

#include "../xxConfig.h"

#include "xxQuickMenuDefines.h"
#include "../Utils/XMLDocument/xxXMLDocument.h"
#include "ui/UILayout.h"

#include <stack>

NS_XX_BEGIN

/**
 * QuickMenu provides quick and easy cocos2d::Menu creation based on a XML file.
 *
 * Features:
 *  - (Under dev.) Support for all different MenuItem types.
 *  - (Under dev.) Attributes for Menu and MenuItems.
 *  - (TBA) Different MenuItems alignment in Menu.
 *  - (TBA) Nested submenus.
 *  - (TBA) Transitions between submenus.
 *
 * For sample QuickMenu XML file, check TestScenes/QuickMenu/QuickMenuExample.xml
 */
class XX_DLL QuickMenu : private cocos2d::Ref {
public:
    /**
     * Create empty QuickMenu. You can call setContent() and
     * prepare() methods subsequently.
     * @return Autoreleased QuickMenu object.
     */
    CREATE_FUNC (QuickMenu)

        /**
         * Create QuickMenu with content. You can call prepare() method
         * subsequently to assign layer.
         * @param string filename : Path to file for XMLDocument to load content.
         * @return Autoreleased QuickMenu object.
         */
         XX_CREATE_WITH_FILE_FUNC (QuickMenu)

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
           bool prepare (cocos2d::Layer * layer);

    /**
     * Set content of XML document from a reference.
     * @param XMLDocument xmlDocument : Reference to object to get XML content from.
     */
    void setContent (xxXML & xmlDocument);

    /**
     * Set content of XML document from a reference.
     * @param string filename : Path to file for XMLDocument to load content.
     */
    bool setContentFromFile (const std::string & filename);

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
     * Container for cocos2d::Menu and related transitions.
     */
    class XX_DLL MenuObject {
    public:
        /**
         * Constructor with cocos2d::Menu* parameter.
         * @param cocos2d::Menu * menu : Pointer to menu to be stored in this object.
         */
        MenuObject (cocos2d::Menu * menu);

    private:
        // Menu itself.
        cocos2d::Menu * menu;

        // True if menu is added as a child to a layer.
        bool isVisible = false;
    };

    /**
     * Initialize empty QuickMenu with nullptr layer.
     * @return True if success.
     */
    XX_INIT_FUNC;

    /**
     * Initialize QuickMenu with content from a file.
     * @param string filename : Path to file for XMLDocument to load content.
     * @return True if success.
     */
    XX_INIT_WITH_FILE_FUNC;

    /**
     * Add new Menu/Submenu with attributes and transitions.
     */
    void addMenu ();

    /**
     * Add new MenuItem with attributes.
     */
    void addMenuItem ();

    /**
     * Add common attributes to lastly created MenuItem.
     */
    void addCommonAttributes ();

    /**
     * Add attributes to lastly created MenuItemImage.
     */
    void addImageAttributes (MIImage * item);

    /**
     * Add attributes to lastly created MenuItemFont.
     */
    void addFontAttributes (MIFont * item);

    // Container for MenuObjects
    std::vector<MenuObject> menus;

    // Items waiting for assignment.
    PendingItems pendingItems;

    // Pointer to cocos2d Layer which holds Menu(s).
    cocos2d::Layer * layer;

    // TODO IS CONTENT REALLY NEEDED?
    // XML Document content with Menu(s) structure.
    xxXML::Content content;

    // XML Node stack for MenuItems assignment.
    xxXML::RevAttrStack revAttrStack;
};

NS_XX_END

#endif  // __XX_QUICK_MENU_H__