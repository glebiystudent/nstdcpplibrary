#pragma once

// utility.hpp
// utility addition to C++. miscellaneous


#include <cstdlib>
#include <utility>

namespace nstd {
    template<typename F>
    inline void repeat(const std::size_t n, F&& func) noexcept(true) {
        for(std::size_t i = 0; i < n; ++i)
            std::forward<F>(func)();
    }
}