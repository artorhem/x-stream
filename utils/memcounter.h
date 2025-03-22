#ifndef DEF_FLEXOGRAPH_PROFILE_MEMCOUNTER
#define DEF_FLEXOGRAPH_PROFILE_MEMCOUNTER

#include <sys/resource.h>

namespace _flexograph_profile {
  /**
   * Copied from Blaze. This class is used to measure the memory usage of the program.
   */
  class MemoryCounter {
  public:
    MemoryCounter() {
      getrusage(RUSAGE_SELF, &__memory);
      __previous_mem = __memory.ru_maxrss;
    }

    ~MemoryCounter() {
      getrusage(RUSAGE_SELF, &__memory);
      uint64_t used_mem = __memory.ru_maxrss - __previous_mem;
      fprintf(stderr,"MemoryCounter: %lu MB -> %lu MB, %lu MB total\n", __previous_mem/1024, __memory.ru_maxrss/1024, used_mem/1024);
    }

  private:
    struct rusage __memory;
    uint64_t __previous_mem;
  };

  class Times
  {
  public:
    Times() = default;

    void start() { start_time = std::chrono::high_resolution_clock::now(); }

    void stop() { end_time = std::chrono::high_resolution_clock::now(); }

    [[maybe_unused]] [[nodiscard]] long double t_secs() const
    {
      return std::chrono::duration_cast<std::chrono::duration<double>>(
          end_time - start_time)
          .count();
    }

    [[maybe_unused]] [[nodiscard]] long double t_millis() const
    {
      return std::chrono::duration_cast<
             std::chrono::duration<double, std::milli>>(end_time -
                                                        start_time)
          .count();
    }

    [[maybe_unused]] [[nodiscard]] long double t_nanos() const
    {
      return std::chrono::duration_cast<
             std::chrono::duration<double, std::nano>>(end_time -
                                                       start_time)
          .count();
    }

    [[nodiscard]] long double t_micros() const
    {
      return std::chrono::duration_cast<
             std::chrono::duration<double, std::micro>>(end_time -
                                                        start_time)
          .count();
    }

  private:
    std::chrono::high_resolution_clock::time_point start_time, end_time;
  };

} // end namespace _flexograph_profile

#endif