module;
#include <cstring>
#include <print>
#include <glad/glad.h>
#include <fstream>
#include <sstream>

module Shader;

namespace ogl {

   Shader::Shader(const char* vertexPath, const char* fragmentPath) {
      std::string vertex_code;
      std::string fragment_code;
      std::ifstream v_shader_file;
      std::ifstream f_shader_file;

      v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

      try {
         v_shader_file.open(vertexPath);
         f_shader_file.open(fragmentPath);
         std::stringstream vShaderStream, fShaderStream;

         vShaderStream << v_shader_file.rdbuf();
         fShaderStream << f_shader_file.rdbuf();
         v_shader_file.close();
         f_shader_file.close();

         vertex_code = vShaderStream.str();
         fragment_code = fShaderStream.str();
      } catch (std::ifstream::failure &e) {
         std::println("File not successfully read: {}", e.what());
      }

      const char* vShaderCode = vertex_code.c_str();
      const char* fShaderCode = fragment_code.c_str();

      unsigned int vertex, fragment;
      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &vShaderCode, nullptr);
      glCompileShader(vertex);
      checkCompileErrors(vertex, "VERTEX");

      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &fShaderCode, nullptr);
      glCompileShader(fragment);
      checkCompileErrors(fragment, "FRAGMENT");

      id = glCreateProgram();
      glAttachShader(id, vertex);
      glAttachShader(id, fragment);
      glLinkProgram(id);
      checkCompileErrors(id, "PROGRAM");

      glDeleteShader(vertex);
      glDeleteShader(fragment);
   }

   void Shader::use() const {
      glUseProgram(id);
   }

   void Shader::setBool(const char* name, const bool &value) const {
      glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
   }

   void Shader::setFloat(const char* name, const float &value) const {
      glUniform1f(glGetUniformLocation(id, name), value);
   }

   void Shader::setInt(const char* name, const int &value) const {
      glUniform1i(glGetUniformLocation(id, name), value);
   }

   void Shader::setVec2(const char* name, const glm::vec2 &value) const {
      glUniform2fv(glGetUniformLocation(id, name), 1, reinterpret_cast<const GLfloat*>(&value));
   }

   void Shader::setVec3(const char* name, const glm::vec3 &value) const {
      glUniform3fv(glGetUniformLocation(id, name), 1, reinterpret_cast<const GLfloat*>(&value));
   }

   void Shader::setVec4(const char* name, const glm::vec4 &value) const {
      glUniform4fv(glGetUniformLocation(id, name), 1, reinterpret_cast<const GLfloat*>(&value));
   }

   void Shader::setMat2(const char* name, const glm::mat2 &value) const {
      glUniformMatrix2fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::gtc::value_ptr(value));
   }

   void Shader::setMat3(const char* name, const glm::mat3 &value) const {
      glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::gtc::value_ptr(value));
   }

   void Shader::setMat4(const char* name, const glm::mat4 &value) const {
      glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::gtc::value_ptr(value));
   }

   void Shader::checkCompileErrors(const unsigned int shader, const char* type) {
      int success;
      char infoLog[1024];
      if (strcmp(type, "PROGRAM") != 0) {
         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
         if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::println("ShaderCompilation error of type: {}\n{}\n", type, infoLog);
         }
      } else {
         glGetProgramiv(shader, GL_LINK_STATUS, &success);
         if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::println("ProgramLinking error of type: {}\n{}\n", type, infoLog);
         }
      }
   }

}