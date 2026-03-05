module;
#include <thread>
#include <functional>

export module Timer;

export namespace ogl {

   class Timer {
      public:
         typedef std::chrono::high_resolution_clock Clock;
         using s = std::chrono::duration<float>;

         Timer();

         void start();
         void stop();
         [[nodiscard]] bool isActive() const;
         [[nodiscard]] Clock::duration timeElapsed() const;
         float timeElapsedS();
         void setTimeout(const std::function<void()>& function, long ms_delay) const;
         void setInterval(const std::function<void()>& function, long ms_interval) const;

         static Clock::time_point now();

      private:
         Clock::time_point epoch;
         bool flag;
   };

}
