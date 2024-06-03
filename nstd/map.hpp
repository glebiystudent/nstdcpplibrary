#pragma once

#include <unordered_map>
#include <map>
#include <vector>
#include <tuple>

#ifndef __compressed
#include <iostream>
#endif

namespace nstd {
#ifndef __compressed
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
#endif
    template<std::size_t... I, typename T>
    std::vector<int> get(std::index_sequence<I...>, T tuple) {
        std::vector<int> ret;
        ((ret.emplace_back(std::get<I>(tuple))), ...);
        return ret;
    }

    template<typename K, typename V, typename... Ts>
    inline void create_map(Ts&&... args) noexcept(true) {
        auto v = get(std::make_index_sequence<sizeof...(Ts)>{}, std::forward_as_tuple(args...));

        for(const auto& e : v) {
            std::cout << e << "\n";
        }
    }
}