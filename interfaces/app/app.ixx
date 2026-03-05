module;
#include <memory>

export module App;
import Window;
import Skybox;
import Shader;

export namespace ogl {

   class App {
      public:
         const float WIDTH{1300};
         const float HEIGHT{800};

         App();
         void run() const;

      private:
         void loadSkybox();

         Window window{WIDTH, HEIGHT, "OpenGL"};
         std::unique_ptr<Skybox> skybox;
         std::unique_ptr<Shader> skyboxShader;
   };

}
