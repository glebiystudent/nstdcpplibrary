#pragma once

// filesystem.hpp
// fast, light and easy-to-use filesystem wrapper


#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace nstd {
    inline void write(const std::string& path, const std::string& data) noexcept(true) {
        std::ofstream f;
        f.open(path);
        if(!f.is_open()) return;

        f << data;
        f.close();
    }

    inline void write(const std::string& path, const std::vector<std::string>& data) noexcept(true) {
        std::ofstream f;
        f.open(path);
        if(!f.is_open()) return;

        for(const auto& e : data)
            f << e << "\n";
        f.close();   
    }


    [[nodiscard]] inline std::string read(const std::string& path) noexcept(true) {
        std::ifstream f;
        f.open(path, std::ios::in);
        if(!f.is_open()) return "cannot open your file";

        std::stringstream ret;
        ret << f.rdbuf();
        return ret.str();
    }

    [[nodiscard]] inline std::vector<std::string> read_lines(const std::string& path) noexcept(true) {
        std::ifstream f;
        f.open(path, std::ios::in);
        if(!f.is_open()) return { "cannot open your file" };

        std::vector<std::string> ret;
        for(std::string line = ""; std::getline(f, line);)
            ret.emplace_back(line + "\n");
        return ret;
    }

    inline void create_directory(const std::string& path) noexcept(true) {
        std::filesystem::create_directory(path);
    }
}