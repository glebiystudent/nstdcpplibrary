#pragma once

#include <unordered_map>
#include <map>

#ifndef __compressed
#include <iostream>
#endif

namespace nstd {
#ifndef __compressed
    template<typename T, typename T_>
    inline void log(const std::unordered_map<T, T_>& map) noexcept(true) {
        for(const auto& [k, v] : map)
            std::cout << k << ": " << v << "\n";
    }

    template<typename T, typename T_>
    inline void log(const std::map<T, T_>& map) noexcept(true) {
        for(const auto& [k, v] : map)
            std::cout << k << ": " << v << "\n";
    }
#endif
}