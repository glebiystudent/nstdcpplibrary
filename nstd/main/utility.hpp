#pragma once

// utility.hpp
// utility addition to C++. miscellaneous


#include <cstdlib>
#include <utility>
#include <string>
#include <type_traits>

// REMOVE THIS
#include <iostream>

namespace nstd {
    // repeats a callback function n times with forwarded arguments into it
    template<typename F>
    inline void repeat(const std::size_t n, F&& func) noexcept(true) {
        for(std::size_t i = 0; i < n; ++i)
            std::forward<F>(func)();
    }

    // a complete remake of a switch statement in C++ but with strings
    template<typename... Ts>
    inline void switch_string(Ts&&... ts) noexcept(true) {
        if(sizeof...(Ts) % 2 == 0)
            return;

        auto tuple = std::forward_as_tuple(ts...);
        auto statement = std::get<0>(tuple);
        bool found = false; bool __found = false;
        
        auto f = [&](const std::size_t idx, auto val) {
            if(idx == 0)
                return;
                
            if constexpr(std::is_assignable_v<std::string&, decltype(val)>) {
                if(statement == val) {
                    found = true; __found = true;
                }
            } else {
                if(found) {
                    val(); found = false;
                }
            }
        };
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(ts)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
 
        // default case
        if(constexpr std::size_t idx = sizeof...(Ts); !__found && std::get<idx - 2>(tuple) == "__default")
            std::get<idx - 1>(tuple)();
    }
}