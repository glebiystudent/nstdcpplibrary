#pragma once

#ifdef __compressed
namespace nstd {
    template<typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline void log(Ts&&... ts) noexcept(true) {

    }
}
#else
#include <concepts>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

namespace nstd {
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

    template<typename T>
    inline void log(const std::vector<T>& arr, const std::size_t end_newlines = 1, const std::string& spacer = " ") noexcept(true) {
        for(const auto& e : arr)
            std::cout << e << spacer;
        for(std::size_t i = 0; i < end_newlines; ++i)
            std::cout << "\n";
    }

    template<typename... Ts>
        requires ((std::integral<Ts> || std::floating_point<Ts> || std::convertible_to<Ts, std::string>) && ...)
    inline void log(Ts&&... vars) noexcept(true) {
        ((std::cout << std::forward<Ts>(vars) << " "), ...);
        std::cout << "\n";
    }

    // work in progress
    template<typename... Ts>
    inline void advanced_log(Ts&&... args) noexcept(true) {
        auto func = [&]<typename T>(T&& t){
            if constexpr(std::is_same_v<T, int>)
                std::cout << std::forward<T>(t) << "\n";
        };
        (func(std::forward<Ts>(args)), ...);
    }
}
#endif