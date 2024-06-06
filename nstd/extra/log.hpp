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
#include <span>
#include <unordered_map>
#include <map>
#include <ranges>

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

    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    std::string __str(T data) {
        return std::to_string(data);
    }
    
    std::string __str(const std::string& data) { 
        return data;
    }

    // work in progress
    template<typename T>
        requires std::same_as<std::vector<typename T::value_type>, T>
    [[nodiscard]] inline std::string __compose(T t) noexcept(true) {
        std::string ret = "";
        for(const auto& e : t | std::views::take(t.size() - 1))
            ret += __str(e) + ", ";
        return "{" + ret + __str(t[t.size() - 1]) + "}";
    }

    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline std::string __compose(T t) noexcept(true) {
        return std::to_string(t);
    }

    template<typename T>
        requires std::assignable_from<std::string&, T>
    [[nodiscard]] inline std::string __compose(T t) noexcept(true) {
        return t;
    }

    template<typename T>
    [[nodiscard]] inline std::string __compose(T t) noexcept(true) {
        return "<undefined>";
    }

    template<typename... Ts>
    inline void advanced_log(Ts&&... args) noexcept(true) {
        auto func = [&]<typename T>(T&& t){
            std::cout << __compose(std::forward<T>(t)) << " ";
        };
        (func(std::forward<Ts>(args)), ...);
    }
}
#endif