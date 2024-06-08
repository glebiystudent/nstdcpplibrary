#pragma once

// warning for compressed library users on accidental use of functions
#ifdef __compressed
#include <string>
namespace nstd {
    template<typename T>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline std::string format(const T& t) noexcept(true) {
        return "";
    }
}
#else

// format.hpp
// module that adds a formatting mechanism
// available only in a non-compressed version of a library


#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <concepts>

namespace __ {
    // to_string wrapper for converting numbers to a string
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline std::string __str(const T& data) noexcept(true) {
        return std::to_string(data);
    }

    // to_string wrapper for a normal string
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
        return "[vector: {" + ret.substr(0, ret.size() - 2) + "}] ";
    }

    // std::stack
    template<typename T>
        requires std::same_as<std::stack<typename T::value_type>, T>
    [[nodiscard]] inline std::string __compose(const T& t_) noexcept(true) {
        std::string ret = "";
        auto t = t_;
        for(; !t.empty(); ) {
            ret += __str(t.top()) + ", ";
            t.pop();
        }
        return "[stack: {" + ret.substr(0, ret.size() - 2) + "}] ";
    }

    // unordered_map
    template<typename T>
        requires std::same_as<std::unordered_map<typename T::key_type, typename T::mapped_type>, T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        std::string ret = "";
        for(const auto& [key, value] : t)
            ret += "(" + __str(key) + ": " + __str(value) + "), ";
    
        return "[unordered_map: {" + ret.substr(0, ret.size() - 2) + "}] ";
    }
    
    // map
    template<typename T>
        requires std::same_as<std::map<typename T::key_type, typename T::mapped_type>, T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        std::string ret = "";
        for(const auto& [key, value] : t)
            ret += "(" + __str(key) + ": " + __str(value) + "), ";
    
        return "[map: {" + ret.substr(0, ret.size() - 2) + "}] ";
    }

    // int / float / double / boolean
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        return std::to_string(t) + " ";
    }

    // std::string
    template<typename T>
        requires std::assignable_from<std::string&, T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        const std::string str = __str(t);
        if(str.ends_with("\n")) return str; else return str + " ";
    }

    // not recognized by the overloading system
    template<typename T>
    [[nodiscard]] inline std::string __compose(const T& t) noexcept(true) {
        return "<undefined> ";
    }
}

namespace nstd {
    // converts a stack to a string representation
    template<typename T>
    [[nodiscard]] std::string format(std::stack<T> data) noexcept(true) {
        return __::__compose(data);
    }

    // converts a vector to a string representation
    template<typename T>
    [[nodiscard]] std::string format(const std::vector<T>& data) noexcept(true) {
        return __::__compose(data);
    }

    // converts an unordered_map to a string representation
    template<typename K, typename V>
    [[nodiscard]] std::string format(const std::unordered_map<K, V>& data) noexcept(true) {
        return __::__compose(data);
    }

    // converts a map to a string representation
    template<typename K, typename V>
    [[nodiscard]] std::string format(const std::map<K, V>& data) noexcept(true) {
        return __::__compose(data);
    }
}
#endif