module;
#include <thread>
#include <functional>

module Timer;

namespace ogl {

   Timer::Timer() : flag(true) {}

   void Timer::start() {
      epoch = Clock::now();
   }


   void Timer::stop() {
      flag = false;
   }

   bool Timer::isActive() const {
      return flag;
   }

   std::chrono::system_clock::duration Timer::timeElapsed() const {
      return Clock::now() - epoch;
   }

   float Timer::timeElapsedS() {
      const std::chrono::duration<float> delta = now() - epoch;
      epoch = now();
      return delta.count();
   }

   void Timer::setTimeout(const std::function<void()>& function, const long ms_delay) const {
      std::thread([=, this] {
          if(!flag) {
             return;
          }

         const auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(ms_delay);
         std::this_thread::sleep_until(x);

         if(flag) {
            return;
         }

        function();
    }).detach();
   }

   void Timer::setInterval(const std::function<void()>& function, const long ms_interval) const {
      std::thread([=, this] {
         while (flag) {
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(ms_interval);
            function();
            std::this_thread::sleep_until(x);
         }
      }).detach();
   }

   Timer::Clock::time_point Timer::now() {
      return Clock::now();
   }

}
