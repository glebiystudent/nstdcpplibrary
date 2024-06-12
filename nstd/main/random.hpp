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

            [[nodiscard]] inline int32_t range(const std::pair<int32_t, int32_t>& _range = {-100, 100}) noexcept(true) {
                return std::uniform_int_distribution(_range.first, _range.second)(r);
            }

            [[nodiscard]] inline std::mt19937 engine(void) noexcept(true) {
                return r;
            } 
        private:
            std::mt19937 r;
    };  
}