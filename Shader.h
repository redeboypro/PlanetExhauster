//
// Created by redeb on 21.05.2024.
//

#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <gtc/type_ptr.inl>

#include "GLAPI.h"

#define SHADER_POSITION_ATTRIB_NAME "in_position"
#define SHADER_TEXCOORD_ATTRIB_NAME "in_uv"

struct ShaderAttrib final {
   GLuint location;
   std::string name;
};

class Shader final {
   GLuint m_programId = 0;
   GLuint m_vertexShaderId = 0;
   GLuint m_fragmentShaderId = 0;
   std::unordered_map<std::string, GLint> m_uniforms;

   GLint getUniformLocation(const std::string& uniformName) {
      if (const auto it = m_uniforms.find(uniformName); it != m_uniforms.end()) {
         return it->second;
      }
      return m_uniforms[uniformName] = glGetUniformLocation(m_programId, uniformName.c_str());
   }
public:
   Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, auto... attribs) {
      m_vertexShaderId = loadShaderFromSource(vertexShaderCode, GL_VERTEX_SHADER);
      m_fragmentShaderId = loadShaderFromSource(fragmentShaderCode, GL_FRAGMENT_SHADER);

      m_programId = glCreateProgram();

      glAttachShader(m_programId, m_vertexShaderId);
      glAttachShader(m_programId, m_fragmentShaderId);

      (bindAttrib(attribs.location, attribs.name), ...);

      glLinkProgram(m_programId);
      glValidateProgram(m_programId);
   }

   ~Shader() {
      destroy();
   }

   void use() const {
      glUseProgram(m_programId);
   }

   void bindAttrib(const GLuint attributeLocation, const std::string& attributeName) const {
      glBindAttribLocation(m_programId, attributeLocation, attributeName.c_str());
   }

   void uniform1f(const std::string& uniformName, const GLfloat value) {
      glUniform1f(getUniformLocation(uniformName), value);
   }

   void uniform1i(const std::string& uniformName, const GLint value) {
      glUniform1i(getUniformLocation(uniformName), value);
   }

   void uniform2f(const std::string& uniformName,
      const GLfloat v0,
      const GLfloat v1) {
      glUniform2f(getUniformLocation(uniformName), v0, v1);
   }

   void uniform2i(const std::string& uniformName,
      const GLint v0,
      const GLint v1) {
      glUniform2i(getUniformLocation(uniformName), v0, v1);
   }

   void uniform3f(const std::string& uniformName,
      const GLfloat v0,
      const GLfloat v1,
      const GLfloat v2) {
      glUniform3f(getUniformLocation(uniformName), v0, v1, v2);
   }

   void uniform3i(const std::string& uniformName,
      const GLint v0,
      const GLint v1,
      const GLint v2) {
      glUniform3i(getUniformLocation(uniformName), v0, v1, v2);
   }

   void uniform4f(const std::string& uniformName,
      const GLfloat v0,
      const GLfloat v1,
      const GLfloat v2,
      const GLfloat v3) {
      glUniform4f(getUniformLocation(uniformName), v0, v1, v2, v3);
   }

   void uniform4i(const std::string& uniformName,
      const GLint v0,
      const GLint v1,
      const GLint v2,
      const GLint v3) {
      glUniform4i(getUniformLocation(uniformName), v0, v1, v2, v3);
   }

   void uniformMatrix4fv(const std::string& uniformName, const GLfloat* matrix4x4, const GLboolean transpose) {
      glUniformMatrix4fv(getUniformLocation(uniformName), 1, transpose, matrix4x4);
   }

   void destroy() const {
      glUseProgram(0);
      glDetachShader(m_programId, m_vertexShaderId);
      glDetachShader(m_programId, m_fragmentShaderId);
      glDeleteShader(m_vertexShaderId);
      glDeleteShader(m_fragmentShaderId);
      glDeleteProgram(m_programId);
   }

   static GLuint loadShaderFromSource(const std::string& source, const MGLenum type) {
      const GLuint shaderId = glCreateShader(type);
      const char* sourcePtr = source.c_str();

      glShaderSource(shaderId, 1, &sourcePtr, nullptr);
      glCompileShader(shaderId);

      GLint infoLogLength;
      glGetShaderiv(shaderId, 0x8B84/*GL_INFO_LOG_LENGTH*/, &infoLogLength);

      if (infoLogLength > 0) {
         auto* infoLog = new GLchar[infoLogLength + 1];
         glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog);
         std::cout << "Shader info log:\n" << infoLog << std::endl;
         delete[] infoLog;
      }

      return shaderId;
   }
};

#endif //SHADER_H
