#pragma once

// clock.hpp
// a clock class + external functions to calculate time and work with it


#include <chrono>
#include <vector>
#include <utility>


namespace nstd {
    template<typename F>
    class clock {
        public:
            clock(F&& func) {
                start = std::chrono::high_resolution_clock::now();
                std::forward<F>(func)();
                end = std::chrono::high_resolution_clock::now();
                time = end - start;
            }

            clock(F&& func, const std::size_t n) {
                for(std::size_t i = 0; i < n; ++i) {
                    start = std::chrono::high_resolution_clock::now();
                    std::forward<F>(func)();
                    end = std::chrono::high_resolution_clock::now();
                    time += (end - start);
                }
                time /= n;
            }

            [[nodiscard]] inline float elapsed(void) noexcept(true) {
                return time.count();
            }

            ~clock() = default;
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
            std::chrono::duration<float> time;
    };
}