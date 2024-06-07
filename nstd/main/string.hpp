#pragma once

// string.hpp
// simplifies overall life working with strings


#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ranges>
#include <cctype>

namespace nstd {
    // splits a string by a delimeter (by default it is a space)
    [[nodiscard]] inline std::vector<std::string> split(const std::string& str, const char c = ' ') noexcept(true) { 
        std::vector<std::string> ret;
        std::stringstream stream(str);
        for(std::string segment; std::getline(stream, segment, c);)
            ret.emplace_back(segment);
        return ret;
    }

    // converts a string to all lower characters
    [[nodiscard]] inline std::string tolower(std::string str) noexcept(true) {
        std::transform(str.begin(), str.end(), str.begin(), [](auto c) {return std::tolower(c); });
        return str;
    }

    // converts a string to all upper characters
    [[nodiscard]] inline std::string toupper(std::string str) noexcept(true) {
        std::transform(str.begin(), str.end(), str.begin(), [](auto c) {return std::toupper(c); });
        return str;
    }

    // erases all characters in your string from the second argument string
    [[nodiscard]] inline std::string erase_characters(std::string str, const std::string& characters) noexcept(true) {
        std::erase_if(str, [&characters](const auto c){return characters.find_first_of(c) != std::string::npos;});
        return str;
    }
    
    // replaces all the characters in your string from the second argument string by the third argument value
    [[nodiscard]] inline std::string replace_characters(std::string str, const std::string& characters, const char value) noexcept(true) {
        std::replace_if(str.begin(), str.end(), [&characters](const auto c){ return characters.find_first_of(c) != std::string::npos;}, value);
        return str;
    }

    // replaces all characters from your string from 'from' to 'to' by index(inclusive) 
    [[nodiscard]] inline std::string replace_by_idx(std::string str, const char value, const std::size_t from, std::size_t to = -1) noexcept(true) {
        if(to == -1)
            to = str.size() - 1;
        std::size_t idx = -1;
        std::replace_if(str.begin(), str.end(), [=](const auto c) mutable { return ++idx >= from && idx <= to; }, value);
        return str;
    }
}