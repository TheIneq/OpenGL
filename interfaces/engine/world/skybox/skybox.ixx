module;
#include <vector>
#include <string>

export module Skybox;
import Shader;
import Camera;

export namespace ogl {

   class Skybox {
      public:
         explicit Skybox(Shader* shader);
         Skybox(const std::vector<float>& vertices, Shader* shader);
         ~Skybox();

         void draw(Camera& camera) const;
         void setShader(Shader* shader) { this->shader = shader; }
         void setVertices(const std::vector<float>& vertices) { this->vertices = vertices; }
         void addFacesTextures(const std::vector<std::string>& faces);

      private:
         void setup();
         static unsigned int loadCubeMap(const std::vector<std::string>& faces);

         unsigned int vao{}, vbo{};
         unsigned int texture_id{};
         Shader* shader;
         std::vector<std::string> faces;
         std::vector<float> vertices;
   };

}