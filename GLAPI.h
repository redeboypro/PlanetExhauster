//
// Created by redeb on 12.05.2024.
//

#ifndef GLAPI_H
#define GLAPI_H

#include <cstdint>
#include <vector>
#include <windows.h>
#include "GL/gl.h"

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

typedef enum : GLuint {
    GL_VERTEX_SHADER        =                     0x8B31,
    GL_FRAGMENT_SHADER      =                     0x8B30,
    GL_ARRAY_BUFFER         =                     34962,
    GL_ELEMENT_ARRAY_BUFFER =                     34963,
    GL_STATIC_DRAW          =                     0x88E0,
    GL_STATIC_READ          =                     0x88E6,
    GL_STATIC_COPY          =                     0x88E6,
    GL_DYNAMIC_DRAW         =                     0x88E8,
    GL_DYNAMIC_READ         =                     0x88E9,
    GL_DYNAMIC_COPY         =                     0x88EA
} MGLenum;

#define GLdataptr void*
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef char GLchar;

using wglCreateContextAttribsARBPtrt = HGLRC WINAPI(
    HDC hdc,
    HGLRC hShareContext,
    const int32_t *attribList);
using wglChoosePixelFormatARBPtrt = bool WINAPI(
    HDC hdc,
    const int32_t* piAttribIList,
    const float* pfAttribFList,
    uint32_t nMaxFormats,
    int32_t* piFormats,
    uint32_t *nNumFormats);
using wglSwapIntervalEXTPtrt = int32_t WINAPI(int32_t interval);
using glActiveTexturePtrt = void WINAPI(GLuint texture);
using glGenVertexArraysPtrt = void WINAPI(GLsizei n, GLuint* arrays);
using glDeleteVertexArraysPtrt = void WINAPI(GLsizei n, const GLuint *arrays);
using glBindVertexArrayPtrt = void WINAPI(GLuint array);
using glGenBuffersPtrt = void WINAPI(GLsizei n, GLuint* buffers);
using glDeleteBuffersPtrt = void WINAPI(GLsizei n, const GLuint* buffers);
using glBindBufferPtrt = void WINAPI(GLenum target, GLuint buffer);
using glBufferDataPtrt = void WINAPI(
    GLenum target,
    GLsizeiptr size,
    const GLdataptr data,
    GLenum usage);
using glBufferSubDataPtrt = void WINAPI(
    GLenum target,
    GLintptr offset,
    GLsizeiptr size,
    const GLdataptr data);
using glEnableVertexAttribArrayPtrt = void WINAPI(GLuint index);
using glDisableVertexAttribArrayPtrt = void WINAPI(GLuint index);
using glVertexAttribPointerPtrt = void WINAPI(
    GLuint index,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const GLdataptr pointer);
using glCreateProgramPtrt = GLuint WINAPI();
using glAttachShaderPtrt = void WINAPI(GLuint program, GLuint shader);
using glDetachShaderPtrt = void WINAPI(GLuint program, GLuint shader);
using glLinkProgramPtrt = void WINAPI(GLuint program);
using glValidateProgramPtrt = void WINAPI(GLuint program);
using glUseProgramPtrt = void WINAPI(GLuint program);
using glDeleteShaderPtrt = void WINAPI(GLuint shader);
using glDeleteProgramPtrt = void WINAPI(GLuint program);
using glBindAttribLocationPtrt = void WINAPI(
    GLuint program,
    GLuint index,
    const GLchar* name);
using glUniform1fPtrt = void WINAPI(GLint location, GLfloat v0);
using glUniform2fPtrt = void WINAPI(GLint location, GLfloat v0, GLfloat v1);
using glUniform3fPtrt = void WINAPI(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
using glUniform4fPtrt = void WINAPI(
    GLint location,
    GLfloat v0,
    GLfloat v1,
    GLfloat v2,
    GLfloat v3);
using glUniform2fvPtrt = void WINAPI(
    GLint location,
    GLsizei count,
    const GLfloat* value);
using glUniform3fvPtrt = void WINAPI(
    GLint location,
    GLsizei count,
    const GLfloat* value);
using glUniform1iPtrt = void WINAPI(GLint location, GLint v0);
using glUniform2iPtrt = void WINAPI(GLint location, GLint v0, GLint v1);
using glUniform3iPtrt = void WINAPI(GLint location, GLint v0, GLint v1, GLint v2);
using glUniform4iPtrt = void WINAPI(
    GLint location,
    GLint v0,
    GLint v1,
    GLint v2,
    GLint v3);
using glUniformMatrix4fvPtrt = void WINAPI(
    GLint location,
    GLsizei count,
    GLboolean transpose,
    const GLfloat* value);
using glGetUniformLocationPtrt = GLint WINAPI(GLuint program, const GLchar* name);
using glCreateShaderPtrt = GLuint WINAPI(GLenum type);
using glShaderSourcePtrt = void WINAPI(
    GLuint shader,
    GLsizei count,
    const GLchar** string,
    const GLint* length);
using glCompileShaderPtrt = void WINAPI(GLuint shader);
using glGetShaderivPtrt = void WINAPI(GLuint shader, GLenum pname, GLint *params);
using glGetShaderInfoLogPtrt = void WINAPI(
    GLuint shader,
    GLsizei maxLength,
    GLsizei* length,
    GLchar* infoLog);

inline wglCreateContextAttribsARBPtrt* wglCreateContextAttribsARB;
inline wglChoosePixelFormatARBPtrt* wglChoosePixelFormatARB;
inline wglSwapIntervalEXTPtrt* wglSwapIntervalEXT;
inline glActiveTexturePtrt* glActiveTexture;
inline glGenVertexArraysPtrt* glGenVertexArrays;
inline glDeleteVertexArraysPtrt* glDeleteVertexArrays;
inline glBindVertexArrayPtrt* glBindVertexArray;
inline glGenBuffersPtrt* glGenBuffers;
inline glDeleteBuffersPtrt* glDeleteBuffers;
inline glBindBufferPtrt* glBindBuffer;
inline glBufferDataPtrt* glBufferData;
inline glBufferSubDataPtrt* glBufferSubData;
inline glEnableVertexAttribArrayPtrt* glEnableVertexAttribArray;
inline glDisableVertexAttribArrayPtrt* glDisableVertexAttribArray;
inline glVertexAttribPointerPtrt* glVertexAttribPointer;
inline glCreateProgramPtrt* glCreateProgram;
inline glAttachShaderPtrt* glAttachShader;
inline glDetachShaderPtrt* glDetachShader;
inline glLinkProgramPtrt* glLinkProgram;
inline glValidateProgramPtrt* glValidateProgram;
inline glUseProgramPtrt* glUseProgram;
inline glDeleteShaderPtrt* glDeleteShader;
inline glDeleteProgramPtrt* glDeleteProgram;
inline glBindAttribLocationPtrt* glBindAttribLocation;
inline glUniform1fPtrt* glUniform1f;
inline glUniform2fPtrt* glUniform2f;
inline glUniform3fPtrt* glUniform3f;
inline glUniform4fPtrt* glUniform4f;
inline glUniform2fvPtrt* glUniform2fv;
inline glUniform3fvPtrt* glUniform3fv;
inline glUniform1iPtrt* glUniform1i;
inline glUniform2iPtrt* glUniform2i;
inline glUniform3iPtrt* glUniform3i;
inline glUniform4iPtrt* glUniform4i;
inline glUniformMatrix4fvPtrt* glUniformMatrix4fv;
inline glGetUniformLocationPtrt* glGetUniformLocation;
inline glCreateShaderPtrt* glCreateShader;
inline glShaderSourcePtrt* glShaderSource;
inline glCompileShaderPtrt* glCompileShader;
inline glGetShaderivPtrt* glGetShaderiv;
inline glGetShaderInfoLogPtrt* glGetShaderInfoLog;

void glInitExtensions();
void glInitFeatures();
HGLRC glInit(HDC hdc, int32_t major, int32_t minor);
GLuint glGenBuffer();

template<MGLenum BUFFER_TYPE>
class BufferObject final {
    GLuint m_id;
    bool m_stored = false;
public:
    explicit BufferObject();
    ~BufferObject();

    static constexpr MGLenum type = BUFFER_TYPE;

    void destroy() const;
    void bind() const;

    template<typename T>
    void store(T* data, GLsizei bufferSize);
};

using VBO = BufferObject<GL_ARRAY_BUFFER>;
using EBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER>;

class VAO final {
    GLuint m_id = 0;
public:
    VAO();
    ~VAO();

    void bind() const;
    void destroy() const;
};

#endif //GLAPI_H
