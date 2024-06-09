#pragma once

// async.hpp
// easy asynchronous work added to C++


#include <thread>
#include <utility>

namespace nstd {
    template<typename F, typename... Ts>
    inline void async(F&& func, Ts&&... ts) noexcept(true) {
        std::thread(func, std::forward<Ts>(ts)...).detach();
    }
}