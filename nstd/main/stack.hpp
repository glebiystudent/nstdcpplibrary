#pragma once

// stack.hpp
// quality of life module for stack library


#include <stack>
#include <utility>
#include <iostream>

namespace nstd {
    template<typename T, typename... Ts>
    [[nodiscard]] inline std::stack<T> stack(Ts&&... ts) noexcept(true) {
        std::stack<T> ret;
        auto f = [&](const std::size_t idx, auto val) {
            ret.push(val);
        };
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(ts)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
        return ret;
    }
}