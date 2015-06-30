#ifndef __POLY_CONFIG_H__
#define __POLY_CONFIG_H__

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Cocos2D lib
#include "cocos2d.h"

// Shared, useful macros
#include "polyMacros.h"

// Versions
#define POLY_VERSION 0x00000201
#define MIN_REQUIRED_CC_VERSION 0x00030400
#define MAX_TESTED_CC_VERSION 0x00030400

#if (MIN_REQUIRED_CC_VERSION > COCOS2D_VERSION)
    #error  "Minimum cocos2d-x version requirements are not met."
#endif
#if (MAX_TESTED_CC_VERSION < COCOS2D_VERSION)
    #error  "Currently used cocos2d-x version is not yet compatible."
#endif

// Namespaces
#define NS_POLY_BEGIN                     namespace poly {
#define NS_POLY_END                       }
#define USING_NS_POLY                     using namespace poly
#define NS_POLY                           ::poly

// DLL Export
#ifdef WIN32
    #define POLY_DLL __declspec(dllexport)
#else
    #define POLY_DLL
#endif


#endif  // __POLY_CONFIG_H__
