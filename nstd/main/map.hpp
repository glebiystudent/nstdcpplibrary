#pragma once

#include <unordered_map>
#include <map>
#include <utility>

namespace nstd {
    template<typename K, typename V, typename... Ts>
    [[nodiscard]] inline std::unordered_map<K, V> unordered_map(Ts&&... ts) noexcept(true) {
        std::unordered_map<K, V> ret;
        ret.reserve(sizeof...(Ts) / 2);
        
        K key;
        auto f = [&](const std::size_t idx, auto val) {
            std::cout << idx << ": " << val << "\n";
        };
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(ts)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
        return ret;
    }
}