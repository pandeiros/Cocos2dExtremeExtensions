#ifndef __XX_QUICK_MENU_DEFINES_H__
#define __XX_QUICK_MENU_DEFINES_H__

#define QM_EMPTY_MENU \
cocos2d::Menu * newMenu = cocos2d::Menu::create()

#define QM_MENU_WITH_VEC(__VEC__) \
cocos2d::Menu * newMenu = cocos2d::Menu::createWithArray(__VEC__)

#define QM_ITEM_IMAGE_N_S(__NORMAL__, __SELECT__) \
cocos2d::MenuItemImage * newItem = cocos2d::MenuItemImage::create(__NORMAL__, __SELECT__)

#define QM_ITEM_IMAGE_N_S_C(__NORMAL__, __SELECT__, __CALLBCK__) \
cocos2d::MenuItemImage * newItem = cocos2d::MenuItemImage::create(__NORMAL__, __SELECT__, __CALLBCK__)

#endif  // __XX_QUICK_MENU_DEFINES_H__