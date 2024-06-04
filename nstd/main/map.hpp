#pragma once

#include <unordered_map>
#include <map>
#include <utility>
#include <tuple>
#include <iostream>


namespace nstd {
    template<typename... Ts>
    inline void enum_pack(Ts&&... args) noexcept(true) {
        auto f = [](const std::size_t idx, const auto val){ 
            if(idx % 2 == 0)
                std::cout << idx << ": " << val << "\n";
        };
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(args)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }
}