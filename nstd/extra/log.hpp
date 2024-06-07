#pragma once

// warning for compressed library users on accidental use of functions
#ifdef __compressed
namespace nstd {
    template<typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline void log(Ts&&... ts) noexcept(true) {

    }
}
#else
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <concepts>

namespace nstd {
    // to_string wrapper
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline std::string __str(const T& data) noexcept(true) {
        return std::to_string(data);
    }
    
    [[nodiscard]] inline std::string __str(const std::string& data) noexcept(true) { 
        return data;
    }

    // std::vector
    template<typename T>
        requires std::same_as<std::vector<typename T::value_type>, T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        std::string ret = "";
        for(const auto& e : t)
            ret += __str(e) + ", ";
        return "[vector: {" + ret.substr(0, ret.size() - 2) + "}]";
    }

    // unordered_map
    template<typename T>
        requires std::same_as<std::unordered_map<typename T::key_type, typename T::mapped_type>, T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        std::string ret = "";
        for(const auto& [key, value] : t)
            ret += "(" + __str(key) + ": " + __str(value) + "), ";
    
        return "[unordered_map: {" + ret.substr(0, ret.size() - 2) + "}]";
    }
    
    // map
    template<typename T>
        requires std::same_as<std::map<typename T::key_type, typename T::mapped_type>, T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        std::string ret = "";
        for(const auto& [key, value] : t)
            ret += "(" + __str(key) + ": " + __str(value) + "), ";
    
        return "[map: {" + ret.substr(0, ret.size() - 2) + "}]";
    }

    // int / float / double / boolean
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        return std::to_string(t);
    }

    // std::string
    template<typename T>
        requires std::assignable_from<std::string&, T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        return t;
    }

    // not recognized by the overloading system
    template<typename T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        return "<undefined>";
    }

    // the main log function
    template<typename... Ts>
    inline void log(Ts&&... args) noexcept(true) {
        auto func = [&]<typename T>(T&& t){
            std::cout << __compose(std::forward<T>(t)) << " ";
        };
        (func(std::forward<Ts>(args)), ...);
    }
}
#endif