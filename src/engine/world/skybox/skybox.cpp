module;
#include <glad/glad.h>
#include <stb_image.h>
#include <print>

module Skybox;

namespace ogl {

   Skybox::Skybox(Shader* shader) : shader(shader) {
      vertices = {
         -1.0f, 1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, 1.0f, -1.0f,
         -1.0f, 1.0f, -1.0f,

         -1.0f, -1.0f, 1.0f,
         -1.0f, -1.0f, -1.0f,
         -1.0f, 1.0f, -1.0f,
         -1.0f, 1.0f, -1.0f,
         -1.0f, 1.0f, 1.0f,
         -1.0f, -1.0f, 1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

         -1.0f, -1.0f, 1.0f,
         -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         -1.0f, -1.0f, 1.0f,

         -1.0f, 1.0f, -1.0f,
         1.0f, 1.0f, -1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         -1.0f, 1.0f, 1.0f,
         -1.0f, 1.0f, -1.0f,

         -1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f
      };

      setup();
   }

   Skybox::Skybox(const std::vector<float>& vertices, Shader* shader) : shader(shader), vertices(vertices) {
      setup();
   }

   Skybox::~Skybox() {
      glDeleteVertexArrays(1, &vao);
      glDeleteBuffers(1, &vbo);
   }

   void Skybox::setup() {
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));

      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   void Skybox::addFacesTextures(const std::vector<std::string>& faces) {
      this->faces = faces;
      texture_id = loadCubeMap(faces);
   }

   unsigned int Skybox::loadCubeMap(const std::vector<std::string>& faces) {
      unsigned int textureID;
      glGenTextures(1, &textureID);
      glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

      int width, height, nrChannels;
      stbi_set_flip_vertically_on_load(false);
      for (unsigned int i = 0; i < faces.size(); i++) {
         if (unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0)) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
         } else {
            std::println("Cube map tex failed to load at path: {}", faces[i]);
            stbi_image_free(data);
         }
      }

      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

      return textureID;
   }

   void Skybox::draw(Camera &camera) const {
      glDepthFunc(GL_LEQUAL);
      glDepthMask(GL_FALSE);
      shader->use();
      camera.matrix(*shader, "cameraMatrix");
      shader->setVec3("cameraPos", camera.position);
      glBindVertexArray(vao);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glBindVertexArray(0);
      glDepthMask(GL_TRUE);
      glDepthFunc(GL_LESS);
   }

}