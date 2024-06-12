#pragma once

// random.hpp
// easing life while working with random numbers 


#include <random>
#include <ctime>

namespace nstd {
    class random {
        public:
            inline random(void) noexcept(true) {
                r = std::mt19937((std::random_device())());
            }

            [[nodiscard]] inline int32_t range(const int32_t from, const int32_t to) noexcept(true) {
                return std::uniform_int_distribution(from, to)(r);
            }

            [[nodiscard]] inline std::mt19937 engine(void) noexcept(true) {
                return r;
            } 
        private:
            std::mt19937 r;
    };  
}