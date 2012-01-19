/****************************************************************************
*
*    Copyright (c) 2005 - 2011 by Vivante Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Vivante Corporation. This is proprietary information owned by
*    Vivante Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Vivante Corporation.
*
*****************************************************************************
*
*    Auto-generated file on 8/7/2011. Do not edit!!!
*
*****************************************************************************/




/*
 * Vivante specific definitions and declarations for EGL library.
 */

#ifndef __eglvivante_h_
#define __eglvivante_h_

#ifdef __cplusplus
extern "C" {
#endif

#define EGLAPIENTRY

#define LINUX  //horrible
#define EGL_API_FB

#if defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
/* Win32 and Windows CE platforms. */
#include <windows.h>
typedef HDC             EGLNativeDisplayType;
typedef HWND            EGLNativeWindowType;
typedef HBITMAP         EGLNativePixmapType;

#elif defined(LINUX) && defined(EGL_API_FB)
/* Linux platform for FBDEV. */
typedef struct _FBDisplay * EGLNativeDisplayType;
typedef struct _FBWindow *  EGLNativeWindowType;
typedef struct _FBPixmap *  EGLNativePixmapType;

EGLNativeDisplayType
fbGetDisplay(
    void
    );

void
fbGetDisplayGeometry(
    EGLNativeDisplayType Display,
    int * Width,
    int * Height
    );

void
fbDestroyDisplay(
    EGLNativeDisplayType Display
    );

EGLNativeWindowType
fbCreateWindow(
    EGLNativeDisplayType Display,
    int X,
    int Y,
    int Width,
    int Height
    );

void
fbGetWindowGeometry(
    EGLNativeWindowType Window,
    int * X,
    int * Y,
    int * Width,
    int * Height
    );

void
fbDestroyWindow(
    EGLNativeWindowType Window
    );

EGLNativePixmapType
fbCreatePixmap(
    EGLNativeDisplayType Display,
    int Width,
    int Height
    );

void
fbGetPixmapGeometry(
    EGLNativePixmapType Pixmap,
    int * Width,
    int * Height
    );

void
fbDestroyPixmap(
    EGLNativePixmapType Pixmap
    );

#elif defined(ANDROID)


#if ANDROID_SDK_VERSION >= 9
struct ANativeWindow;
typedef struct ANativeWindow *              EGLNativeWindowType;
#else
struct android_native_window_t;
typedef struct android_native_window_t *    EGLNativeWindowType;
#endif

struct egl_native_pixmap_t;
typedef struct egl_native_pixmap_t *        EGLNativePixmapType;
typedef void*                               EGLNativeDisplayType;

#elif defined(LINUX)
/* X11 platform. */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef Display *   EGLNativeDisplayType;
typedef Window      EGLNativeWindowType;

#ifdef CUSTOM_PIXMAP
typedef void *      EGLNativePixmapType;
#else
typedef Pixmap      EGLNativePixmapType;
#endif /* CUSTOM_PIXMAP */

/* Rename some badly named X defines. */
#ifdef Status
#   define XStatus      int
#   undef Status
#endif
#ifdef Always
#   define XAlways      2
#   undef Always
#endif

#else

#error "Platform not recognized"

/* VOID */
typedef void *  EGLNativeDisplayType;
typedef void *  EGLNativeWindowType;
typedef void *  EGLNativePixmapType;

#endif

#if defined(__EGL_EXPORTS) && !defined(EGLAPI)
#if defined(_WIN32) && !defined(__SCITECH_SNAP__)
#  define EGLAPI    __declspec(dllexport)
# else
#  define EGLAPI
# endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __eglvivante_h_ */
