#pragma once

// stack.hpp
// quality of life module for stack library


#include <stack>
#include <utility>
#include <functional>

namespace nstd {
    // creates a stack from your variadic arguments
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

    // reverses a stack not modifying the original one
    template<typename T>
    [[nodiscard]] inline std::stack<T> reverse(std::stack<T> stack) noexcept(true) {
        std::stack<T> ret;
        for(; !stack.empty(); ) {
            ret.push(stack.top());
            stack.pop();
        }
        return ret;
    }

    // checks if a stack contains a specific value of yours
    template<typename T>
    inline bool contains(std::stack<T> stack, const T& val) noexcept(true) {
        bool ret = false;
        for(; !stack.empty(); ) {
            if(stack.top() == val) {
                ret = true; break;
            }
            stack.pop();
        }
        return ret;
    }
    
    // applies a callback function to each element in a stack
    template<typename T>
    inline void for_each(std::stack<T> stack, const std::function<void(T)>& func) noexcept(true) {
        for(; !stack.empty(); ) {
            func(stack.top()); 
            stack.pop();
        }
    }

    // filters out elements from a stack by the callback function(should return true/false based on a value condition)
    template<typename T>
    [[nodiscard]] std::stack<T> filter(const std::stack<T>& stack, const std::function<bool(T)>& func) noexcept(true) {
        std::stack<T> ret;
        for_each<int>(stack, [&](T val){ if(func(val)) ret.push(val); });
        return ret;
    }
}