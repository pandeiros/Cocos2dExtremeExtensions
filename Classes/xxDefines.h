#ifndef __XX_DEFINES_H__
#define __XX_DEFINES_H__

#include "cocos2d.h"

// Versions
#define XX_VERSION 0x00000100
#define MIN_REQUIRED_CC_VERSION 0x00030400
#define MAX_TESTED_CC_VERSION 0x00030400

#if (MIN_REQUIRED_CC_VERSION > COCOS2D_VERSION)
    #error  "Minimum cocos2d-x version requirements are not met."
#endif
#if (MAX_TESTED_CC_VERSION < COCOS2D_VERSION)
    #error  "Currently used cocos2d-x version are not yet compatible."
#endif

// Namespace macros
#define NS_XX_BEGIN                     namespace xx {
#define NS_XX_END                       }
#define USING_NS_XX                     using namespace xx
#define NS_XX                           ::xx

// DLL Export Macro
#define XX_DLL __declspec(dllexport)


#endif  // __XX_MACROS_H__