#pragma once

// string.hpp
// simplifies overall life working with strings


#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ranges>
#include <concepts>
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

    // reverses your string
    [[nodiscard]] inline std::string reverse(std::string str) noexcept(true) {
        std::reverse(str.begin(), str.end());
        return str;
    }


    // splits the string into three parts with partition in the middle
    [[nodiscard]] inline std::vector<std::string> partition(const std::string& str, const std::string& partition) noexcept(true) {
        const std::size_t found = str.find(partition);
        if(found == std::string::npos)
            return {};

        return { str.substr(0, found), str.substr(found, partition.size()), str.substr(found + partition.size())};
    }


    // splits the string into three parts with partition in the middle(last occurence)
    [[nodiscard]] inline std::vector<std::string> rpartition(const std::string& str, const std::string& partition) noexcept(true) {
        const std::size_t found = str.rfind(partition);
        if(found == std::string::npos)
            return {};

        return { str.substr(0, found), str.substr(found, partition.size()), str.substr(found + partition.size())};
    }


    // removes any whitespaces from a string
    [[nodiscard]] inline std::string trim(const std::string& str) noexcept(true) {
        return nstd::erase_characters(str, " ");
    }


    // removes any whitespaces from a lits of strings
    [[nodiscard]] inline std::vector<std::string> trim(std::vector<std::string> vec) noexcept(true) {
        std::for_each(vec.begin(), vec.end(), [](auto& e){ e = nstd::trim(e); });
        return vec;
    }


    // concatenates all the values from vector into one big string by a delimeter(can be changed)
    [[nodiscard]] inline std::string join(const std::vector<std::string>& vec, const std::string& space = " ") noexcept(true) {
        std::string ret = "";
        for(const auto& e : vec | std::views::take(vec.size() - 1))
            ret += e + space;
        return ret + vec[vec.size() - 1];
    }


    // concatenates all the values(int/float/bool) from vector into one big string by a delimeter(can be changed) 
    template<typename T>   
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline std::string concat(const std::vector<T>& vec, const std::string& space = " ") noexcept(true) {
        std::string ret = "";
        for(const auto& e : vec | std::views::take(vec.size() - 1))
            ret += std::to_string(e) + space;
        return ret + std::to_string(vec[vec.size() - 1]);
    }
}