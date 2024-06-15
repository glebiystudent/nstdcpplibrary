#pragma once

#ifdef __nstdwindows

// windows.hpp
// extra library to ease your work with windows API
// define "__nstdwindows" before importing init.hpp


#include <unordered_map>
#include <functional>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace nstd { 
    class keypress_handler {
        public:
            inline keypress_handler(void) noexcept(true) {

            }

            inline void add(int32_t key, const std::function<void(void)>& f) noexcept(true) {
                storage[key] = f;
            }

            inline void remove(int32_t key) noexcept(true) {
                storage.erase(key);
            }

            inline void handle(void) noexcept(true) {
                for(const auto& [key, f] : storage) {
                    if(GetAsyncKeyState(key) & 0x8000) {
                        for(; GetAsyncKeyState(key); ) {}

                        f();
                    }
                }
            }

            inline std::thread async(void) noexcept(true) {
                return std::thread([&]{
                    for(;;)
                        handle();
                });
            }
        private:
            std::unordered_map<int32_t, std::function<void(void)>> storage;
    };
}

#endif