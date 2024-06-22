#pragma once

// utility.hpp
// utility addition to C++. miscellaneous


#include <utility>
#include <string>
#include <type_traits>
#include <vector>
#include <tuple>
#include <concepts>


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
                    found = true; 
                    __found = true;
                }
            } else {
                if(found) {
                    val(); 
                    found = false;
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

    // allowing you having infinite variables in one line of code
    // auto [a, b, c] = nstd::var(...);
    template<typename... Ts>
    [[nodiscard]] inline std::tuple<Ts...> var(Ts&&... ts) noexcept(true) {
        return std::forward_as_tuple(ts...);
    }

    // allowing you to destruct vector[n0, n1, ..., N] into variables
    // auto [a, b] = nstd::var<2>(...);
    template<std::size_t N, typename T>
    [[nodiscard]] inline auto var(const std::vector<T>& vec) noexcept(true) {
        return [&]<std::size_t... I>(std::index_sequence<I...>){
            return (std::make_tuple(vec[I]...));
        }(std::make_index_sequence<N>{});
    }

    template<typename T, typename... Ts>
        requires ((std::same_as<T, Ts> || std::assignable_from<T&, Ts> || std::assignable_from<Ts&, T>) && ...)
    inline bool contains(T&& v, Ts&&... ts) noexcept(true) {
        auto cmp = []<typename C, typename C_, typename F>(C&& a, C_&& b, F&& func){
            bool ret = std::forward<C>(a) == std::forward<C_>(b);
            if(ret) std::forward<F>(func)();
            return ret;
        };

        bool ret = false;
        ((cmp(std::forward<T>(v), std::forward<Ts>(ts), [&]{ ret = true; })), ...);
        return ret;
    }
}