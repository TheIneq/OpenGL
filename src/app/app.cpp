module;
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

module App;
import glm;
import Model;
import Timer;
import Camera;

namespace ogl {

   App::App() {
      loadSkybox();
   }

   void App::run() const {
      const Shader shader("../src/engine/shaders/default.vert", "../src/engine/shaders/default.frag");
      const Shader lightCubeShader("../src/engine/shaders/light.vert", "../src/engine/shaders/light.frag");

      const Model ourModel("../resources/models/sphere/Sphere.obj");
      const Model lightModel("../resources/models/cube.obj");
      auto lightColor = glm::vec3(1.f, 1.f, 1.f);

      Camera camera(window.getWidth(), window.getHeight(), glm::vec3(0.f, 0.f, 2.f));
      Timer timer;

      timer.start();
      while (!window.shouldClose()) {
         glfwPollEvents();

         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         camera.inputs(window.getWindow(), timer.timeElapsedS());
         camera.updateMatrix();

         skybox->draw(camera);

         shader.use();
         camera.matrix(shader, "cameraMatrix");
         shader.setVec3("lightColor", lightColor);
         shader.setVec3("lightPos", glm::vec3(1.2f, 1.f, 2.f));
         shader.setVec3("viewPos", camera.position);

         auto model = glm::mat4(1.0f);
         model = glm::gtc::translate(model, glm::vec3(0.f, 0.f, 0.f));
         model = glm::gtc::scale(model, glm::vec3(.5f));
         shader.setMat4("model", model);
         ourModel.draw(shader);

         lightCubeShader.use();
         camera.matrix(shader, "cameraMatrix");
         model = glm::mat4(1.0f);
         model = glm::gtc::translate(model, glm::vec3(1.2f, 1.f, 2.f));
         model = glm::gtc::scale(model, glm::vec3(.1f));
         lightCubeShader.setMat4("model", model);
         lightCubeShader.setVec3("lightColor", lightColor);
         lightModel.draw(lightCubeShader);

         glfwSwapBuffers(window.getWindow());
      }

      timer.stop();
   }

   void App::loadSkybox() {
      skyboxShader = std::make_unique<Shader>("../src/engine/shaders/skybox.vert", "../src/engine/shaders/skybox.frag");
      skybox = std::make_unique<Skybox>(skyboxShader.get());

      const std::vector<std::string> faces = {
         "../resources/textures/skybox/right.jpg",
         "../resources/textures/skybox/left.jpg",
         "../resources/textures/skybox/top.jpg",
         "../resources/textures/skybox/bottom.jpg",
         "../resources/textures/skybox/front.jpg",
         "../resources/textures/skybox/back.jpg"
      };
      skybox->addFacesTextures(faces);

      skybox->setShader(skyboxShader.get());
   }

}