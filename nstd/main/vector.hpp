#pragma once 

// vector.hpp
// an addition to a standard vector and simplifying life while working with them


#include <vector>
#include <algorithm>
#include <concepts>
#include <functional>
#include <ranges>
#include <type_traits>

#include "random.hpp"


namespace nstd {
    // creates a vector by your variadic arguments
    template<typename T = int, typename... Ts>
    [[nodiscard]] inline std::vector<T> vector(Ts&&... args) noexcept(true) {
        std::vector<T> ret;
        ret.reserve(sizeof...(Ts));
        ((ret.emplace_back(std::forward<Ts>(args))), ...);
        return ret;
    }

    template<typename T = int>
        requires std::integral<T>
    [[nodiscard]] inline std::vector<T> generate_random(nstd::random& r, const std::size_t n = 10, const std::pair<T, T>& _range = {-100, 100}) noexcept(true) {
        std::vector<T> ret(n);
        std::generate(ret.begin(), ret.end(), [&]{ return r.range(_range); });
        return ret;
    }

    // creates a vector of a specific size and fills it by zeroes(0)
    template<typename T>
        requires std::integral<T>
    [[nodiscard]] inline std::vector<T> create_fillzeroes(const std::size_t size) noexcept(true) {
        std::vector<T> ret(size);
        return ret;
    }

    // creates a vector of a specific size and fills it by ones(1)
    template<typename T>
        requires std::integral<T>
    [[nodiscard]] inline std::vector<T> create_fillones(const std::size_t size) noexcept(true) {
        std::vector<T> ret(size);
        std::fill(ret.begin(), ret.end(), 1);
        return ret;
    }

    // creates a vector of a specific size and fills it by your number
    template<typename T>
        requires std::integral<T>
    [[nodiscard]] inline std::vector<T> create_fillnumbers(const std::size_t size, T&& number) noexcept(true) {
        std::vector<T> ret(size);
        std::fill(ret.begin(), ret.end(), std::forward<T>(number));
        return ret;
    }

    // returns a sorted vector in an ascending order
    template<typename T>
    [[nodiscard]] inline std::vector<T> sort_asc(std::vector<T> vec) noexcept(true) {
        std::sort(vec.begin(), vec.end(), std::less<T>());
        return vec;
    }


    // returns a sorted vector in an ascending order
    template<typename T>
    [[nodiscard]] inline std::vector<T> sort_desc(std::vector<T> vec) noexcept(true) {
        std::sort(vec.begin(), vec.end(), std::greater<T>());
        return vec;
    }

    // returns a reversed vector
    template<typename T>
    [[nodiscard]] inline std::vector<T> reverse(std::vector<T> vec) noexcept(true) {
        std::reverse(vec.begin(), vec.end());
        return vec;
    }

    // returns a sliced vector by index(inclusive). leave the last argument for the automatic end of the vector
    template<typename T>
    [[nodiscard]] inline std::vector<T> slice(const std::vector<T>& vec, const std::size_t from, std::size_t to = -1) noexcept(true) {
        if(to == -1)
            to = vec.size() - 1;
        std::vector<T> ret(abs(from - to) + 1);
        std::copy_n(vec.begin() + from, abs(from - to) + 1, ret.begin());

        return ret;
    }
    
    // merges two or more(infinite) vectors together
    template<typename T, typename... Ts>
        requires (std::same_as<T, Ts> && ...)
    [[nodiscard]] inline std::vector<T> merge(const std::vector<Ts>&... vectors) noexcept(true) {
        std::vector<T> ret;
        ret.reserve((vectors.size() + ...));
        ((std::for_each(vectors.begin(), vectors.end(), [&](const T& e){ ret.emplace_back(e); })), ...);
        return ret;
    }


    // applies a check function on each and every value in the vector. returns true if every value matched your condition
    template<typename T>
    inline bool every(const std::vector<T>& vec, const std::function<bool(T)>& func) noexcept(true) {
        bool ret = true;
        for(const auto& e : vec)
            if(!func(e)) {
                ret = false;
                break;
            }
        return ret;
    }

    // returns a new vector with replaced values in your index range(others are untouched)
    template<typename T>
    [[nodiscard]] inline std::vector<T> replace(const std::vector<T>& vec, const T& value, const std::size_t from, std::size_t to = -1) noexcept(true) {
        if(to == -1)
            to = vec.size() - 1;
        std::vector<T> ret(vec.size());
        
        std::size_t idx = -1;
        std::replace_copy_if(vec.begin(), vec.end(), ret.begin(), [&idx, from, to](const T& e) {
            return ++idx >= from && idx <= to;
        }, value);
        return ret;
    }


    // applies a function to each element of a vector and changes it
    template<typename T, typename F>
    [[nodiscard]] inline std::vector<T> for_each(std::vector<T> vec, F&& func) noexcept(true) {
        std::for_each(vec.begin(), vec.end(), std::forward<F>(func));
        return vec;
    }


    // filters a vector and returns a new vector with values filtered by a callback function
    template<typename T>
    [[nodiscard]] inline std::vector<T> filter(const std::vector<T>& vec, const std::function<bool(T)>& func, const bool resize = true) noexcept(true) {
        std::vector<T> ret(vec.size());
        std::size_t filtered = 0;
        std::remove_copy_if(vec.begin(), vec.end(), ret.begin(), [&func, &filtered](const T& e) { bool _ = !func(e); if(_) ++filtered; return _; });
        if(resize)
            ret.resize(vec.size() - filtered);
        return ret;
    }

    // finds a first value in a vector specified by your filter callback function
    template<typename T>
    [[nodiscard]] inline T find(const std::vector<T>& vec, const std::function<bool(T)>& func) noexcept(true) {
        return *std::find_if(vec.begin(), vec.end(), func);
    }

    // finds an index of a first value in your vector
    template<typename T>
    [[nodiscard]] inline std::size_t find_index(const std::vector<T>& vec, const T& value) noexcept(true) {
        for(std::size_t i = 0; i < vec.size(); ++i)
            if(vec[i] == value)
                return i;
        return -1;
    }

    // sums up all the elements in an array(has to be integral / floating / boolean)
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline T sum(const std::vector<T>& vec) noexcept(true) {
        T ret = 0;
        for(const auto e : vec)
            ret += e;
        return ret; 
    }

    // multiplicates(be careful) up all the elements in an array(has to be integral / floating / boolean)
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    [[nodiscard]] inline T mul(const std::vector<T>& vec) noexcept(true) {
        T ret = 1;
        for(const auto e : vec)
            ret *= e;
        return ret; 
    }

    // pop elements from the front(n for additional elements popped)
    template<typename T>
    [[nodiscard]] inline std::vector<T> pop_front(std::vector<T> vec, const std::size_t n = 0) noexcept(true) {
        vec.erase(vec.begin(), vec.begin() + n + 1);
        return vec;
    }
}