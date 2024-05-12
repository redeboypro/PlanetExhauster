//
// Created by redeb on 12.05.2024.
//

#ifndef GLAPI_H
#define GLAPI_H

#include <cstdint>
#include <windows.h>

#define DUMMY_WND_CLASSNAME "_DUMMY_WND"
#define GLMSG L"GL"
#define WINAPIMSG L"WINAPI"
#define ERR_MSG(API, MSG) MessageBoxW(nullptr, API L": " MSG, L"Error", MB_OK | MB_ICONEXCLAMATION)
#define FAIL_EXIT exit(EXIT_FAILURE)

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB                      0x2023
#define WGL_FULL_ACCELERATION_ARB                 0x2027
#define WGL_TYPE_RGBA_ARB                         0x202B

using wglCreateContextAttribsARBPtrt = HGLRC __attribute__((__stdcall__))(HDC hdc, HGLRC hShareContext, const int32_t *attribList);
using wglChoosePixelFormatARBPtrt = bool __attribute__((__stdcall__))(HDC hdc,
    const int32_t* piAttribIList,
    const float* pfAttribFList,
    uint32_t nMaxFormats,
    int32_t* piFormats,
    uint32_t *nNumFormats);

inline wglCreateContextAttribsARBPtrt* wglCreateContextAttribsARB;
inline wglChoosePixelFormatARBPtrt* wglChoosePixelFormatARB;

static void glInitExtensions();
static HGLRC glInit(HDC hdc);

#endif //GLAPI_H
