#pragma once

#ifdef __compressed
namespace nstd {
    template<typename F, typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline void args_all(F&& func, Ts&&... args) noexcept(true) {

    }

    template<typename F, typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline void args_even(F&& func, Ts&&... args) noexcept(true) {

    }

    template<typename F, typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline void args_uneven(F&& func, Ts&&... args) noexcept(true) {

    }

    template<typename F, typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline void args_firstlast(F&& func, Ts&&... args) noexcept(true) {

    }

    template<typename T, typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline auto create_vector(Ts&&... args) noexcept(true) {

    }
}
#else
#include <tuple>
#include <utility>
#include <vector>

namespace nstd {
    template<typename F, typename... Ts>
    inline void args_all(F&& func, Ts&&... args) noexcept(true) {
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (func(I, std::forward<Ts>(args)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }

    template<typename F, typename... Ts>
    inline void args_even(F&& func, Ts&&... args) noexcept(true) {
        auto f = [&](const std::size_t idx, auto val) {
            if(idx % 2 == 0)
                func(idx, val);
        };
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(args)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }

    template<typename F, typename... Ts>
    inline void args_uneven(F&& func, Ts&&... args) noexcept(true) {
        auto f = [&](const std::size_t idx, auto val) {
            if(idx % 2 != 0)
                func(idx, val);
        };
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            (f(I, std::forward<Ts>(args)), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
    }

    template<typename F, typename... Ts>
    inline void args_firstlast(F&& func, Ts&&... args) noexcept(true) {
        constexpr std::size_t idx = sizeof...(Ts);
        if(idx < 2) return;
        const auto tuple = std::forward_as_tuple(args...);
        std::forward<F>(func)(0, std::get<0>(tuple));
        std::forward<F>(func)(idx - 1, std::get<idx - 1>(tuple));
    }

    template<typename T, typename... Ts>
    [[nodiscard]] inline std::vector<T> create_vector(Ts&&... args) noexcept(true) {
        std::vector<T> ret;

        return ret;
    }
}
#endif