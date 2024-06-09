#pragma once

// benchmark.hpp
// a clock class + external functions to calculate time and work with it


#include <chrono>
#include <vector>
#include <utility>
#include <string>


namespace nstd {
    template<typename F>
    class benchmark {
        public:
            benchmark(F&& func) {
                time = std::chrono::duration<float>::zero();
                start = std::chrono::high_resolution_clock::now();
                std::forward<F>(func)();
                end = std::chrono::high_resolution_clock::now();
                time = end - start;
            }

            benchmark(F&& func, const std::size_t n) {
                time = std::chrono::duration<float>::zero();
                for(std::size_t i = 0; i < n; ++i) {
                    start = std::chrono::high_resolution_clock::now();
                    std::forward<F>(func)();
                    end = std::chrono::high_resolution_clock::now();
                    time += (end - start);
                }
                time /= n;
            }

            // compares the current benchmark to the other benchmark
            template<typename F_>
            [[nodiscard]] inline float cmp(benchmark<F_>& b) noexcept(true) {
                return this->elapsed() / b.elapsed();
            }

            // compares the current benchmark to the other benchmark (human-readable)
            template<typename F_>
            [[nodiscard]] inline std::string compare(benchmark<F_>& b) noexcept(true) {
                float p = this->elapsed() / b.elapsed();
                std::cout << p << "\n";
                return (p < 1 ? (std::to_string((1 - p) * 100) + "% faster") : (std::to_string((p - 1) * 100) + "% slower"));
            }

            [[nodiscard]] inline float elapsed(void) noexcept(true) {
                return time.count();
            }

            ~benchmark() = default;
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
            std::chrono::duration<float> time;
    };
}