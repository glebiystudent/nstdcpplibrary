#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <ranges>
#include <cctype>

#ifndef __compressed
#include <iostream>
#include <concepts>
#endif

namespace nstd {
#ifndef __compressed
    template<typename... Ts>
        requires ((std::integral<Ts> || std::floating_point<Ts> || std::convertible_to<Ts, std::string>) && ...)
    inline void log(Ts&&... vars) noexcept(true) {
        ((std::cout << vars << " "), ...);
        std::cout << "\n";
    }
#endif

    [[nodiscard]] inline std::vector<std::string> split(const std::string& str, const char c = ' ') noexcept(true) { 
        std::vector<std::string> ret;
        std::stringstream stream(str);
        for(std::string segment; std::getline(stream, segment, c);)
            ret.emplace_back(segment);
        return ret;
    }

    [[nodiscard]] inline std::string tolower(std::string str) noexcept(true) {
        std::transform(str.begin(), str.end(), str.begin(), [](auto c) {return std::tolower(c); });
        return str;
    }

    [[nodiscard]] inline std::string toupper(std::string str) noexcept(true) {
        std::transform(str.begin(), str.end(), str.begin(), [](auto c) {return std::toupper(c); });
        return str;
    }

    [[nodiscard]] inline std::string erase_characters(std::string str, const std::string& characters) noexcept(true) {
        std::erase_if(str, [&characters](const auto c){return characters.find_first_of(c) != std::string::npos;});
        return str;
    }
       
    [[nodiscard]] inline std::string replace_characters(std::string str, const std::string& characters, const char value) noexcept(true) {
        std::replace_if(str.begin(), str.end(), [&characters](const auto c){ return characters.find_first_of(c) != std::string::npos;}, value);
        return str;
    }

    [[nodiscard]] inline std::string replace_by_idx(std::string str, const char value, const std::size_t from, std::size_t to = -1) noexcept(true) {
        if(to == -1)
            to = str.size() - 1;
        std::size_t idx = -1;
        std::replace_if(str.begin(), str.end(), [=](const auto c) mutable { return ++idx >= from && idx <= to; }, value);
        return str;
    }
}