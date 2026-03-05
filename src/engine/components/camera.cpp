module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>

module Camera;

namespace ogl {

   Camera::Camera(const float& width, const float& height, const glm::vec3& position) : position(position), width(width), height(height) {}

   void Camera::updateMatrix(const float& fov, const float& near_Plane, const float& far_plane) {
      const glm::mat4 view = glm::gtc::lookAt(position, position + orientation, up);
      const glm::mat4 projection = glm::gtc::perspective(glm::radians(fov), width / height, near_Plane, far_plane);

      cameraMatrix = projection * view;
   }

   void Camera::matrix(const Shader& shader, const char* uniform) {
      glUniformMatrix4fv(glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, glm::gtc::value_ptr(cameraMatrix));
   }

   void Camera::inputs(GLFWwindow* window, const float delta_time) {
      if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

         const float velocity = speed * delta_time;
         if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { position += velocity * orientation; }
         if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { position += velocity * -glm::normalize(glm::cross(orientation, up)); }
         if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { position += velocity * -orientation; }
         if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { position += velocity * glm::normalize(glm::cross(orientation, up)); }
         if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { position += velocity * up; }
         if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { position += velocity * -up; }

         if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            speed = 0.5f;
         } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            speed = 2.0f;
         } else {
            speed = 1.0f;
         }

         static double lastX = width / 2.0;
         static double lastY = height / 2.0;

         double mouseX, mouseY;
         glfwGetCursorPos(window, &mouseX, &mouseY);

         if (first_click) {
            lastX = mouseX;
            lastY = mouseY;
            first_click = false;
         }

         const auto deltaX = static_cast<float>(mouseX - lastX);
         const auto deltaY = static_cast<float>(lastY - mouseY);

         lastX = mouseX;
         lastY = mouseY;

         const float yaw   = -deltaX * sensitivity;
         const float pitch = deltaY * sensitivity;

         const glm::vec3 right = glm::normalize(glm::cross(orientation, up));

         if (const glm::vec3 newOrientation = glm::gtc::rotate(orientation, glm::radians(pitch),right);
            glm::dot(newOrientation, up) < 0.99f && glm::dot(newOrientation, up) > -0.99f)
         {
            orientation = newOrientation;
         }

         orientation = glm::normalize(glm::gtc::rotate(orientation, glm::radians(yaw), up));
      } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
         first_click = true;
      }
   }

}