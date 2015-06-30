#ifndef __POLY_QUICK_MENU_DEFINES_H__
#define __POLY_QUICK_MENU_DEFINES_H__

// Create function
#define QM_CREATE_FULL_FUNC \
static QuickMenu * create(cocos2d::Layer * layer, const std::string filename) \
{ \
    QuickMenu * pRet = new(std::nothrow) QuickMenu(); \
    if (pRet && pRet->initWithFile(filename) && pRet->prepare(layer)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#endif  // __POLY_QUICK_MENU_DEFINES_H__
