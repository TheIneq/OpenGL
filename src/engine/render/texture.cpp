module;
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include <stdexcept>

module Texture;

namespace ogl {

   Texture::Texture(const char* image, const char* textureType, const GLenum slot) : type(textureType), path(image) {
      stbi_set_flip_vertically_on_load(true);
      int widthImg, heightImg, nrChannelsImg;
      unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &nrChannelsImg, 0);

      glGenTextures(1, &id);
      glActiveTexture(GL_TEXTURE0 + slot);
      glBindTexture(GL_TEXTURE_2D, id);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      if (nrChannelsImg == 4) {
         glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            widthImg,
            heightImg,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            bytes
         );
      } else if (nrChannelsImg == 3) {
         glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            widthImg,
            heightImg,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            bytes
         );
      } else if (nrChannelsImg == 1) {
         glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            widthImg,
            heightImg,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            bytes
         );
      } else {
         throw std::invalid_argument("Automatic Texture type recognition failed");
      }

      glGenerateMipmap(GL_TEXTURE_2D);
      stbi_image_free(bytes);
      glBindTexture(GL_TEXTURE_2D, 0);
   }

}