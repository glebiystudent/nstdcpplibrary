#pragma once

// warning for compressed library users on accidental use of functions
#ifdef __compressed
#include <string>
namespace nstd {
    template<typename T>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline std::string tostring(const T& t) noexcept(true) {
        return "";
    }
}
#else
// to_string.hpp
// module that allows converting containers and other things to a string representation
// available only in a non-compressed version of a library

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>

namespace nstd {
    // converts a stack to a string representation
    template<typename T>
    [[nodiscard]] std::string tostring(std::stack<T> data) noexcept(true) {
        return "";
    }

    // converts a vector to a string representation
    template<typename T>
    [[nodiscard]] std::string tostring(const std::vector<T>& data) noexcept(true) {
        return "";
    }

    // converts an unordered_map to a string representation
    template<typename K, typename V>
    [[nodiscard]] std::string tostring(const std::unordered_map<K, V>& data) noexcept(true) {
        return "";
    }

    // converts a map to a string representation
    template<typename K, typename V>
    [[nodiscard]] std::string tostring(const std::map<K, V>& data) noexcept(true) {
        return "";
    }
}
#endif