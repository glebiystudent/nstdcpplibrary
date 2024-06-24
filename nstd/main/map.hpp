#pragma once

// map.hpp
// quality of life module for unordered_maps and maps(regular ones)


#include <unordered_map>
#include <map>
#include <utility>

#define umap unordered_map

namespace nstd {
    // creates an unordered_map from your variadic arguments: nstd::unordered_map<keytype, valuetype>(key, value, key, value, ...)
    template<typename K, typename V, typename... Ts>
    [[nodiscard]] inline std::unordered_map<K, V> unordered_map(Ts&&... ts) noexcept(true) {
        if(sizeof...(Ts) % 2 != 0)
            return {};

        std::unordered_map<K, V> ret; ret.reserve(sizeof...(Ts) / 2);
        K key;
        auto f = [&](const std::size_t idx, auto val) {
            idx % 2 == 0 ? key = val : ret[key] = val;
        };

        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(ts)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
        return ret;
    }

    // creates an unordered_map from your variadic arguments: nstd::unordered_map<keytype, valuetype>(key, value, key, value, ...)
    template<typename K, typename V, typename... Ts>
    [[nodiscard]] inline std::map<K, V> map(Ts&&... ts) noexcept(true) {
        if(sizeof...(Ts) % 2 != 0)
            return {};

        std::map<K, V> ret; ret.reserve(sizeof...(Ts) / 2);
        K key;
        auto f = [&](const std::size_t idx, auto val) {
            idx % 2 == 0 ? key = val : ret[key] = val;
        };

        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(ts)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
        return ret;
    }
}