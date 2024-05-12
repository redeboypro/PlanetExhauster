//
// Created by redeb on 12.05.2024.
//

#include "GLAPI.h"

void glInitExtensions() {
    const WNDCLASSA dummyWndClass = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = DefWindowProcA,
        .hInstance = GetModuleHandle(nullptr),
        .lpszClassName = DUMMY_WND_CLASSNAME,
    };

    if (!RegisterClassA(&dummyWndClass)) {
        ERR_MSG(WINAPIMSG, L"Failed to register dummy class!");
        FAIL_EXIT;
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
        ERR_MSG(WINAPIMSG, L"Failed to create dummy window instance!");
        FAIL_EXIT;
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
        ERR_MSG(WINAPIMSG, L"Failed to choose the modern OpenGL pixel format!");
        FAIL_EXIT;
    }

    if (!SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDescriptor)) {
        ERR_MSG(WINAPIMSG, L"Failed to set the modern OpenGL pixel format!");
        FAIL_EXIT;
    }

    HGLRC dummyWGLContext = wglCreateContext(dummyDC);
    if (!dummyWGLContext) {
        ERR_MSG(GLMSG, L"Failed to activate modern OpenGL pixel format!");
        FAIL_EXIT;
    }

    if (!wglMakeCurrent(dummyDC, dummyWGLContext)) {
        ERR_MSG(GLMSG, L"Failed to register dummy!");
        FAIL_EXIT;
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

HGLRC glInit(HDC hdc, int32_t major, int32_t minor) {
    glInitExtensions();

    const int32_t pixelFormatAttributes[] = {
        WGL_DRAW_TO_WINDOW_ARB,     1,
        WGL_SUPPORT_OPENGL_ARB,     1,
        WGL_DOUBLE_BUFFER_ARB,      1,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };

    int32_t pixelFormat;
    uint32_t formatsNum;
    wglChoosePixelFormatARB(hdc, pixelFormatAttributes, nullptr, 1, &pixelFormat, &formatsNum);
    if (!formatsNum) {
        ERR_MSG(GLMSG, L"Failed to set the modern OpenGL pixel format!");
        exit(EXIT_FAILURE);
    }

    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
    DescribePixelFormat(hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDescriptor);
    if (!SetPixelFormat(hdc, pixelFormat, &pixelFormatDescriptor)) {
        ERR_MSG(GLMSG, "Failed to set the modern OpenGL pixel format!");
        FAIL_EXIT;
    }

    const int32_t glAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    HGLRC glContext = wglCreateContextAttribsARB(hdc, nullptr, glAttribs);
    if (!glContext) {
        ERR_MSG(GLMSG, "Failed to create the modern OpenGL context!");
        FAIL_EXIT;
    }

    if (!wglMakeCurrent(hdc, glContext)) {
        ERR_MSG(GLMSG, "Failed to activate the modern OpenGL rendering context!");
        FAIL_EXIT;
    }

    return glContext;
}