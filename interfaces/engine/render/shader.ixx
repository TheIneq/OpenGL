export module Shader;
export import glm;

export namespace ogl {

   class Shader {
      public:
         Shader(const char* vertexPath, const char* fragmentPath);

         void use() const;

         void setBool(const char* name, const bool& value) const;
         void setInt(const char* name, const int& value) const;
         void setFloat(const char* name, const float& value) const;
         void setVec2(const char* name, const glm::vec2& value) const;
         void setVec3(const char* name, const glm::vec3& value) const;
         void setVec4(const char* name, const glm::vec4& value) const;
         void setMat2(const char* name, const glm::mat2& value) const;
         void setMat3(const char* name, const glm::mat3& value) const;
         void setMat4(const char* name, const glm::mat4& value) const;

         unsigned int id{};
      private:
         static void checkCompileErrors(unsigned int shader, const char* type);
   };

}