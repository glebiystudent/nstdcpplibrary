#pragma once 

#include <vector>
#include <algorithm>
#include <concepts>
#include <string>
#include <functional>
#include <ranges>

namespace nstd {
    template<typename T = int, typename... Ts>
        requires (std::same_as<T, Ts> && ...)
    [[nodiscard]] inline std::vector<T> vector(Ts&&... args) noexcept(true) {
        std::vector<T> ret;
        ret.reserve(sizeof...(Ts));
        ((ret.emplace_back(std::forward<Ts>(args))), ...);
        return ret;
    }

    template<typename T>
        requires std::integral<T>
    [[nodiscard]] inline std::vector<T> create_fillzeroes(const std::size_t size) noexcept(true) {
        std::vector<T> ret(size);
        return ret;
    }

    template<typename T>
        requires std::integral<T>
    [[nodiscard]] inline std::vector<T> create_fillones(const std::size_t size) noexcept(true) {
        std::vector<T> ret(size);
        std::fill(ret.begin(), ret.end(), 1);
        return ret;
    }

    template<typename T>
        requires std::integral<T>
    [[nodiscard]] inline std::vector<T> create_fillnumbers(const std::size_t size, const T number) noexcept(true) {
        std::vector<T> ret(size);
        std::fill(ret.begin(), ret.end(), number);
        return ret;
    }


    template<typename T>
    [[nodiscard]] inline std::vector<T> reverse(const std::vector<T>& vec) noexcept(true) {
        return std::reverse(vec.begin(), vec.end());
    }

    template<typename T>
    [[nodiscard]] inline std::vector<T> slice(const std::vector<T>& vec, const std::size_t from, std::size_t to = -1) noexcept(true) {
        if(to == -1)
            to = vec.size() - 1;
        std::vector<T> ret(abs(from - to) + 1);
        std::copy_n(vec.begin() + from, abs(from - to) + 1, ret.begin());

        return ret;
    }
    
    template<typename T, typename... Ts>
        requires (std::same_as<T, Ts> && ...)
    [[nodiscard]] inline std::vector<T> merge(const std::vector<Ts>&... vectors) noexcept(true) {
        std::vector<T> ret;
        ret.reserve((vectors.size() + ...));
        ((std::for_each(vectors.begin(), vectors.end(), [&](const T& e){ ret.emplace_back(e); })), ...);
        return ret;
    }

    [[nodiscard]] inline std::string concat(const std::vector<std::string>& vec, const std::string& space = " ") noexcept(true) {
        std::string ret = "";
        for(const auto& e : vec | std::views::take(vec.size() - 1))
            ret += e + space;
        return ret + vec[vec.size() - 1];
    }

    template<typename T>
    [[nodiscard]] inline bool every(const std::vector<T>& vec, const std::function<bool(T)>& func) noexcept(true) {
        bool ret = true;
        for(const auto& e : vec)
            if(!func(e)) {
                ret = false;
                break;
            }
        return ret;
    }

    template<typename T>
    [[nodiscard]] inline std::vector<T> fill(const std::vector<T>& vec, const T& value, const std::size_t from, std::size_t to = -1) noexcept(true) {
        if(to == -1)
            to = vec.size() - 1;
        std::vector<T> ret(vec.size());
        
        std::size_t idx = -1;
        std::replace_copy_if(vec.begin(), vec.end(), ret.begin(), [&idx, from, to](const T& e) {
            return ++idx >= from && idx <= to;
        }, value);
        return ret;
    }

    template<typename T>
    [[nodiscard]] inline std::vector<T> filter(const std::vector<T>& vec, const std::function<bool(T)>& func, const bool resize = true) noexcept(true) {
        std::vector<T> ret(vec.size());
        std::size_t filtered = 0;
        std::remove_copy_if(vec.begin(), vec.end(), ret.begin(), [&func, &filtered](const T& e) { bool _ = !func(e); if(_) ++filtered; return _; });
        if(resize)
            ret.resize(vec.size() - filtered);
        return ret;
    }

    template<typename T>
    [[nodiscard]] inline T find(const std::vector<T>& vec, const std::function<bool(T)>& func) noexcept(true) {
        return *std::find_if(vec.begin(), vec.end(), func);
    }

    template<typename T>
    [[nodiscard]] inline std::size_t find_index(const std::vector<T>& vec, const T& value) noexcept(true) {
        for(std::size_t i = 0; i < vec.size(); ++i)
            if(vec[i] == value)
                return i;
        return -1;
    }
}