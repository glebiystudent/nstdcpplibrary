#pragma once

// interval.hpp
// JS' setInterval, setTimeout & more


#include <thread>
#include <chrono>

#include <iostream>


namespace nstd {
    template<typename F>
    inline std::thread set_timeout(const int32_t ms, F&& f) noexcept(true) {
        return std::thread([&]{
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            std::forward<F>(f)();
        });
    }

    template<typename F>
    inline std::thread set_interval(const int32_t ms, F&& f) noexcept(true) {
        return std::thread([&]{
            for(;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                std::forward<F>(f)();
            }
        });
    }
}