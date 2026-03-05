module;
#include <vector>

export module Mesh;
export import glm;
export import Texture;

#define MAX_BONE_INFLUENCE 4

export namespace ogl {

   struct Vertex {
      glm::vec3 position;
      glm::vec3 normal;
      glm::vec2 tex_coords;
      glm::vec3 tangent;
      glm::vec3 bitangent;
      int m_bone_ids[MAX_BONE_INFLUENCE];
      float m_weights[MAX_BONE_INFLUENCE];
   };

   class Mesh {
      public:
         Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
         void draw(const Shader& shader) const;

         std::vector<Vertex> vertices;
         std::vector<unsigned int> indices;
         std::vector<Texture> textures;

      private:
         void setupMesh();
         unsigned int vao{}, vbo{}, ebo{};
   };

}