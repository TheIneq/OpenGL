module;
#include <GLFW/glfw3.h>

export module Camera;
export import Shader;
export import glm;

export namespace ogl {

   class Camera {
      public:
         Camera(const float& width, const float& height, const glm::vec3& position);

         void inputs(GLFWwindow* window, float delta_time);
         void updateMatrix(const float& fov = 45.0f, const float& near_Plane = 0.1f, const float& far_plane = 1000000.0f);
         void matrix(const Shader& shader, const char* uniform);

         glm::vec3 position;
         glm::vec3 orientation{0.f, 0.f, -1.f};
         glm::vec3 up{0.f, 1.f, 0.f};
         glm::mat4 cameraMatrix{1.f};

         bool first_click{true};
         float width;
         float height;
         float speed{1.f};
         float sensitivity{.1f};
   };

}