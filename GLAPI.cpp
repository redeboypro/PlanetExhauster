//
// Created by redeb on 12.05.2024.
//

#include "GLAPI.h"

void glInit() {
    const WNDCLASSA dummyWndClass = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = DefWindowProcA,
        .hInstance = GetModuleHandle(nullptr),
        .lpszClassName = DUMMY_WND_CLASSNAME,
    };

    if (!RegisterClassA(&dummyWndClass)) {
        ERR_MSG(WINAPIW, L"Failed to register dummy");
        exit(EXIT_FAILURE);
    }

    HWND dummyWndHandle = CreateWindowExA(
        0,
        dummyWndClass.lpszClassName,
        nullptr,
        0,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        dummyWndClass.hInstance,
        nullptr);

    if (!dummyWndHandle) {
        ERR_MSG(WINAPIW, L"Failed to register dummy");
        exit(EXIT_FAILURE);
    }

    HDC dummyDC = GetDC(dummyWndHandle);

    PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .iPixelType = PFD_TYPE_RGBA,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .cColorBits = 32,
        .cAlphaBits = 8,
        .iLayerType = PFD_MAIN_PLANE,
        .cDepthBits = 24,
        .cStencilBits = 8,
    };

    const int32_t pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDescriptor);
    if (!pixelFormat) {
        ERR_MSG(WINAPIW, L"Failed to set the modern OpenGL pixel format!");
        exit(EXIT_FAILURE);
    }

    if (!SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDescriptor)) {
        ERR_MSG(WINAPIW, L"Failed to set the modern OpenGL pixel format!");
        exit(EXIT_FAILURE);
    }

    HGLRC dummyWGLContext = wglCreateContext(dummyDC);
    if (!dummyWGLContext) {
        ERR_MSG(WINAPIW, L"Failed to activate modern OpenGL pixel format!");
        exit(EXIT_FAILURE);
    }

    if (!wglMakeCurrent(dummyDC, dummyWGLContext)) {
        ERR_MSG(WINAPIW, L"Failed to register dummy");
        exit(EXIT_FAILURE);
    }

    wglCreateContextAttribsARB = reinterpret_cast<wglCreateContextAttribsARBPtrt *>(wglGetProcAddress(
        "wglCreateContextAttribsARB"));

    wglChoosePixelFormatARB = reinterpret_cast<wglChoosePixelFormatARBPtrt *>(wglGetProcAddress(
        "wglChoosePixelFormatARB"));

    wglMakeCurrent(dummyDC, nullptr);
    wglDeleteContext(dummyWGLContext);
    ReleaseDC(dummyWndHandle, dummyDC);
    DestroyWindow(dummyWndHandle);
}
