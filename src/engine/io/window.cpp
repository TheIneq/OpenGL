module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include <utility>

module Window;
import Camera;

namespace ogl {

   Window::Window(const float w, const float h, std::string name) : width(w), height(h), window_name(std::move(name)) {
      initWindow();
   }

   Window::~Window() {
      glfwDestroyWindow(window);
      glfwTerminate();
   }

   void Window::initWindow() {
      if (!glfwInit()) {
         throw std::runtime_error("Failed to initialize GLFW!");
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwWindowHint(GLFW_SAMPLES, 4);

      window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
      if (window == nullptr) {
         glfwTerminate();
         throw std::runtime_error("Failed to create GLFW window!");
      }

      glfwMakeContextCurrent(window);
      glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
      glfwMaximizeWindow(window);

      if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
         throw std::runtime_error("Failed to initialize GLAD!");
      }
      glEnable(GL_DEPTH_TEST);
   }

   void Window::framebufferResizeCallback(GLFWwindow* window, const int width, const int height) {
      glViewport(0, 0, width, height);
   }

}