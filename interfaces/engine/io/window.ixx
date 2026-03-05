module;
#include <GLFW/glfw3.h>
#include <string>

export module Window;

export namespace ogl {

   class Window {
      public:
         Window(float w, float h, std::string name);
         ~Window();

         [[nodiscard]] bool shouldClose() const { return glfwWindowShouldClose(window); }
         [[nodiscard]] GLFWwindow* getWindow() const { return window; }
         [[nodiscard]] float getWidth() const { return width; }
         [[nodiscard]] float getHeight() const { return height; }

      private:
         void initWindow();
         static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

         std::string window_name;
         GLFWwindow* window{};
         float width;
         float height;
   };

}