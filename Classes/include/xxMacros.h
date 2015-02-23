#ifndef __XX_MACROS_H__
#define __XX_MACROS_H__

// Messages
#define XX_LOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)

#define XX_ERROR(message) xx::MessageHandler::printMessage (message, xx::MessageHandler::_ERROR)
#define XX_ERROR_RETURN(message) xx::MessageHandler::printMessage (message, xx::MessageHandler::_ERROR); return
#define XX_ERROR_RETURN_FALSE(message) xx::MessageHandler::printMessage (message, xx::MessageHandler::_ERROR); return false

// Create macros
#define XX_CREATE_WITH_FILE_FUNC(__TYPE__) \
static __TYPE__* create(const std::string & filename) \
{ \
    __TYPE__ * pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithFile(filename)) \
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

// Init macros
#define XX_INIT_WITH_FILE_FUNC \
bool initWithFile (const std::string & filename)

#define XX_INIT_FUNC \
bool init()


#endif // __XX_MACROS_H__