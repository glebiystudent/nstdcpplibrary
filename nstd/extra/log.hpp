#pragma once

// warning for compressed library users on accidental use of functions
#ifdef __compressed
namespace nstd {
    template<typename... Ts>
    [[deprecated("you are using a compressed version of nstd. this function is not available")]] inline void log(Ts&&... ts) noexcept(true) {

    }
}
#else

// log.hpp
// advanced module that can log almost anything like a JS console.log!
// available only in a non-compressed version of a library


#include <iostream>

#include "format.hpp"

constexpr inline const char* newline = "\n";
constexpr inline const char* endl = "\n";

namespace nstd {


    // the main log function, you can insert almost anything here, otherwise you'll see <undefined>, don't worry
    template<typename... Ts>
    inline void log(Ts&&... args) noexcept(true) {
        auto func = [&]<typename T>(T&& t){
            std::cout << __::__compose(std::forward<T>(t));
        };
        (func(std::forward<Ts>(args)), ...);
    }
}
#endif