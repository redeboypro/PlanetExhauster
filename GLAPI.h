//
// Created by redeb on 12.05.2024.
//

#ifndef GLAPI_H
#define GLAPI_H

#include <cstdint>
#include <windows.h>
#include <gl/gl.h>

#define DUMMY_WND_CLASSNAME "DUMMY_WND"
#define WINAPIW L"WINAPI"
#define ERR_MSG(API, MSG) MessageBoxW(nullptr, API L":" MSG, L"Error", MB_OK | MB_ICONEXCLAMATION)

using wglCreateContextAttribsARBPtrt = HGLRC WINAPI(HDC hdc, HGLRC hShareContext, const int32_t *attribList);
using wglChoosePixelFormatARBPtrt = bool WINAPI(HDC hdc,
    const int32_t* piAttribIList,
    const float* pfAttribFList,
    uint32_t nMaxFormats,
    int32_t* piFormats,
    uint32_t *nNumFormats);

inline wglCreateContextAttribsARBPtrt* wglCreateContextAttribsARB;
inline wglChoosePixelFormatARBPtrt* wglChoosePixelFormatARB;

static void glInit();

#endif //GLAPI_H
