module;
#include <glad/glad.h>
#include <string>

export module Texture;
export import Shader;

export namespace ogl {

   class Texture {
      public:
         Texture(const char* image, const char* textureType, GLenum slot);

         GLuint id;
         const char* type;
         std::string path;
   };

}