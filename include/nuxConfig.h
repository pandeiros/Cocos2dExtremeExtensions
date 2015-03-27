#ifndef __NUX_CONFIG_H__
#define __NUX_CONFIG_H__

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Cocos2D lib
#include "cocos2d.h"

// Shared, useful macros
#include "nuxMacros.h"

// Versions
#define NUX_VERSION 0x00000112
#define MIN_REQUIRED_CC_VERSION 0x00030400
#define MAX_TESTED_CC_VERSION 0x00030400

#if (MIN_REQUIRED_CC_VERSION > COCOS2D_VERSION)
    #error  "Minimum cocos2d-x version requirements are not met."
#endif
#if (MAX_TESTED_CC_VERSION < COCOS2D_VERSION)
    #error  "Currently used cocos2d-x version is not yet compatible."
#endif

// Namespaces
#define NS_NUX_BEGIN                     namespace nux {
#define NS_NUX_END                       }
#define USING_NS_NUX                     using namespace nux
#define NS_NUX                           ::nux

// DLL Export
#ifdef WIN32
    #define NUX_DLL __declspec(dllexport)
#else
    #define NUX_DLL
#endif


#endif  // __NUX_CONFIG_H__