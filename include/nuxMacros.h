#ifndef __NUX_MACROS_H__
#define __NUX_MACROS_H__

// Messages
#define NUX_LOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)
#define NUX_ASSERT(condition) assert(condition)

#define NUX_ERROR(message) nux::MessageHandler::printMessage (message, nux::MessageHandler::_ERROR)
#define NUX_ERROR_RETURN(message) nux::MessageHandler::printMessage (message, nux::MessageHandler::_ERROR); return
#define NUX_ERROR_RETURN_FALSE(message) nux::MessageHandler::printMessage (message, nux::MessageHandler::_ERROR); return false

// Create macros
#define NUX_CREATE_WITH_FILE_FUNC(__TYPE__) \
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
#define NUX_INIT_WITH_FILE_FUNC \
bool initWithFile (const std::string & filename)

#define NUX_INIT_FUNC \
bool init()


#endif // __NUX_MACROS_H__