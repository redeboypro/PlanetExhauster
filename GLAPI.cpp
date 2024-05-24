//
// Created by redeb on 12.05.2024.
//

#include "GLAPI.h"

#include <iostream>

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
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32,
        .cAlphaBits = 8,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE,
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

    glInitFeatures();

    wglMakeCurrent(dummyDC, nullptr);
    wglDeleteContext(dummyWGLContext);
    ReleaseDC(dummyWndHandle, dummyDC);
    DestroyWindow(dummyWndHandle);
}

void glInitFeatures() {
    wglCreateContextAttribsARB = reinterpret_cast<wglCreateContextAttribsARBPtrt *>(wglGetProcAddress(
        "wglCreateContextAttribsARB"));
    wglChoosePixelFormatARB = reinterpret_cast<wglChoosePixelFormatARBPtrt *>(wglGetProcAddress(
        "wglChoosePixelFormatARB"));
    wglSwapIntervalEXT = reinterpret_cast<wglSwapIntervalEXTPtrt *>(wglGetProcAddress("wglSwapIntervalEXT"));
    glActiveTexture = reinterpret_cast<glActiveTexturePtrt *>(wglGetProcAddress("glActiveTexture"));
    glGenVertexArrays = reinterpret_cast<glGenVertexArraysPtrt *>(wglGetProcAddress("glGenVertexArrays"));
    glDeleteVertexArrays = reinterpret_cast<glDeleteVertexArraysPtrt *>(wglGetProcAddress("glDeleteVertexArrays"));
    glBindVertexArray = reinterpret_cast<glBindVertexArrayPtrt *>(wglGetProcAddress("glBindVertexArray"));
    glGenBuffers = reinterpret_cast<glGenBuffersPtrt *>(wglGetProcAddress("glGenBuffers"));
    glDeleteBuffers = reinterpret_cast<glDeleteBuffersPtrt *>(wglGetProcAddress("glDeleteBuffers"));
    glBindBuffer = reinterpret_cast<glBindBufferPtrt *>(wglGetProcAddress("glBindBuffer"));
    glBufferData = reinterpret_cast<glBufferDataPtrt *>(wglGetProcAddress("glBufferData"));
    glBufferSubData = reinterpret_cast<glBufferSubDataPtrt *>(wglGetProcAddress("glBufferSubData"));
    glEnableVertexAttribArray = reinterpret_cast<glEnableVertexAttribArrayPtrt *>(wglGetProcAddress(
        "glEnableVertexAttribArray"));
    glDisableVertexAttribArray = reinterpret_cast<glDisableVertexAttribArrayPtrt *>(wglGetProcAddress(
        "glDisableVertexAttribArray"));
    glVertexAttribPointer = reinterpret_cast<glVertexAttribPointerPtrt *>(wglGetProcAddress("glVertexAttribPointer"));
    glCreateProgram = reinterpret_cast<glCreateProgramPtrt *>(wglGetProcAddress("glCreateProgram"));
    glAttachShader = reinterpret_cast<glAttachShaderPtrt *>(wglGetProcAddress("glAttachShader"));
    glDetachShader = reinterpret_cast<glDetachShaderPtrt *>(wglGetProcAddress("glDetachShader"));
    glLinkProgram = reinterpret_cast<glLinkProgramPtrt *>(wglGetProcAddress("glLinkProgram"));
    glValidateProgram = reinterpret_cast<glValidateProgramPtrt *>(wglGetProcAddress("glValidateProgram"));
    glUseProgram = reinterpret_cast<glUseProgramPtrt *>(wglGetProcAddress("glUseProgram"));
    glDeleteShader = reinterpret_cast<glDeleteShaderPtrt *>(wglGetProcAddress("glDeleteShader"));
    glDeleteProgram = reinterpret_cast<glDeleteProgramPtrt *>(wglGetProcAddress("glDeleteProgram"));
    glBindAttribLocation = reinterpret_cast<glBindAttribLocationPtrt *>(wglGetProcAddress("glBindAttribLocation"));
    glUniform1f = reinterpret_cast<glUniform1fPtrt *>(wglGetProcAddress("glUniform1f"));
    glUniform2f = reinterpret_cast<glUniform2fPtrt *>(wglGetProcAddress("glUniform2f"));
    glUniform3f = reinterpret_cast<glUniform3fPtrt *>(wglGetProcAddress("glUniform3f"));
    glUniform4f = reinterpret_cast<glUniform4fPtrt *>(wglGetProcAddress("glUniform4f"));
    glUniform2fv = reinterpret_cast<glUniform2fvPtrt *>(wglGetProcAddress("glUniform2fv"));
    glUniform3fv = reinterpret_cast<glUniform3fvPtrt *>(wglGetProcAddress("glUniform3fv"));
    glUniform1i = reinterpret_cast<glUniform1iPtrt *>(wglGetProcAddress("glUniform1i"));
    glUniform2i = reinterpret_cast<glUniform2iPtrt *>(wglGetProcAddress("glUniform2i"));
    glUniform3i = reinterpret_cast<glUniform3iPtrt *>(wglGetProcAddress("glUniform3i"));
    glUniform4i = reinterpret_cast<glUniform4iPtrt *>(wglGetProcAddress("glUniform4i"));
    glUniformMatrix4fv = reinterpret_cast<glUniformMatrix4fvPtrt *>(wglGetProcAddress("glUniformMatrix4fv"));
    glGetUniformLocation = reinterpret_cast<glGetUniformLocationPtrt *>(wglGetProcAddress("glGetUniformLocation"));
    glCreateShader = reinterpret_cast<glCreateShaderPtrt *>(wglGetProcAddress("glCreateShader"));
    glShaderSource = reinterpret_cast<glShaderSourcePtrt *>(wglGetProcAddress("glShaderSource"));
    glCompileShader = reinterpret_cast<glCompileShaderPtrt *>(wglGetProcAddress("glCompileShader"));
    glGetShaderiv = reinterpret_cast<glGetShaderivPtrt *>(wglGetProcAddress("glGetShaderiv"));
    glGetShaderInfoLog = reinterpret_cast<glGetShaderInfoLogPtrt *>(wglGetProcAddress("glGetShaderInfoLog"));
}

HGLRC glInit(HDC hdc, const int32_t major, const int32_t minor) {
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
        0
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

GLuint glGenBuffer() {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    return bufferId;
}

VAO::VAO() {
    glGenVertexArrays(1, &m_id);
}

VAO::~VAO() {
    destroy();
}

void VAO::bind() const {
    glBindVertexArray(m_id);
}

void VAO::destroy() const {
    glDeleteVertexArrays(1, &m_id);
}

