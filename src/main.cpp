import App;
#include <exception>
#include <stdexcept>

int main() {
   const ogl::App app{};

   try {
      app.run();
   } catch (std::exception &e) {
      throw std::runtime_error(e.what());
   }

   return 0;
}
