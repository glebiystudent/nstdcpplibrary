#pragma once

// async.hpp
// easy asynchronous work added to C++


#include <thread>
#include <utility>

namespace nstd {
    // runs a callback function asynchronously with the specified arguments
    template<typename F, typename... Ts>
    inline std::thread async(F&& func, Ts&&... ts) noexcept(true) {
        return std::thread(std::forward<F>(func), std::forward<Ts>(ts)...);
    }

    // forces your thread to sleep for your duration in milliseconds
    inline void sleep(const std::size_t ms) noexcept(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}