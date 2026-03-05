module;
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>
#include <fstream>
#include <vector>

export module Model;
export import Mesh;

export namespace ogl {

   class Model {
      public:
         explicit Model(const char* path, bool gamma = false);
         void draw(const Shader& shader) const;

      private:
         void loadModel(const std::string& path);
         void processNode(const aiNode* node, const aiScene* scene);
         Mesh processMesh(aiMesh* mesh, const aiScene* scene);
         std::vector<Texture> loadMaterialTextures(const aiMaterial* mat, aiTextureType type, const char* typeName);

         bool gamma_correction;
         std::vector<Texture> textures_loaded;
         std::vector<Mesh> meshes{};
         std::string directory;
   };

}