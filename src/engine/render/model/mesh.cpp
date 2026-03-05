module;
#include <vector>
#include <glad/glad.h>
#include <string>

module Mesh;

namespace ogl {

   Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const std::vector<Texture>& textures)
      : vertices(vertices), indices(indices), textures(textures)
   {
      setupMesh();
   }

   void Mesh::draw(const Shader& shader) const {
      unsigned int diffuseNr = 1;
      unsigned int specularNr = 1;
      unsigned int normalNr = 1;
      unsigned int heightNr = 1;
      for(unsigned int i = 0; i < textures.size(); i++) {
         glActiveTexture(GL_TEXTURE0 + i);
         std::string number;
         std::string type = textures[i].type;
         if(type == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
         } else if(type == "texture_specular") {
            number = std::to_string(specularNr++);
         } else if(type == "texture_normal") {
            number = std::to_string(normalNr++);
         } else if(type == "texture_height") {
            number = std::to_string(heightNr++);
         }

         glUniform1i(glGetUniformLocation(shader.id, (type + number).c_str()), i);
         glBindTexture(GL_TEXTURE_2D, textures[i].id);
      }

      glBindVertexArray(vao);
      glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
      glBindVertexArray(0);

      glActiveTexture(GL_TEXTURE0);
   }

   void Mesh::setupMesh() {
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
      glGenBuffers(1, &ebo);

      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(nullptr));

      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex_coords)));

      glEnableVertexAttribArray(3);
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));

      glEnableVertexAttribArray(4);
      glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, bitangent)));

      glEnableVertexAttribArray(5);
      glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_bone_ids)));

      glEnableVertexAttribArray(6);
      glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_weights)));
      glBindVertexArray(0);
   }

}