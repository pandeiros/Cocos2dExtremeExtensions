#ifndef __POLY_MACROS_H__
#define __POLY_MACROS_H__

// Messages
#define POLY_LOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)
#define POLY_ASSERT(condition) assert(condition)

#define POLY_ERROR(message) poly::MessageHandler::printMessage (message, poly::MessageHandler::_ERROR)
#define POLY_ERROR_RETURN(message) poly::MessageHandler::printMessage (message, poly::MessageHandler::_ERROR); return
#define POLY_ERROR_RETURN_FALSE(message) poly::MessageHandler::printMessage (message, poly::MessageHandler::_ERROR); return false

// Create macros
#define POLY_CREATE_WITH_FILE_FUNC(__TYPE__) \
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
#define POLY_INIT_WITH_FILE_FUNC \
bool initWithFile (const std::string & filename)

#define POLY_INIT_FUNC \
bool init()

// A macro to disallow the copy constructor and operator= functions.
// This should be used in the private: declarations for a class.
#define POLY_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);                   \
  void operator=(const TypeName&)


#endif // __POLY_MACROS_H__
