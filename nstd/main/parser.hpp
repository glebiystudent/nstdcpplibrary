#pragma once

// parser.hpp
// difficult parser made easy for you


#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>

#include "../main/utility.hpp"
#include "../main/string.hpp"

namespace nstd {
    [[nodiscard]] std::vector<std::string> parse_paths(std::string str) noexcept(true) {
        struct brace {
            char type;
            std::size_t idx;
        };

        struct family {
            std::string parent;
            std::string child;
            std::string child_folder;
        };

        std::vector<brace> braces;
        std::map<std::size_t, std::vector<std::string>> levels;
        std::map<std::size_t, std::vector<family>> families;


        auto parse = [&]{
            str = "{ " + str + "}";
            for(int32_t idx = -1;;) {
                auto find = str.find_first_of("{}", idx + 1);
                if(find == std::string::npos)
                    break;
                idx = find;
                
                braces.emplace_back(brace{str[find], find});
                if(idx != -1 && braces[braces.size() - 2].type == '{' && braces[braces.size() - 1].type == '}') {
                    auto [brace_left, brace_right] = nstd::var(braces[braces.size() - 2], braces[braces.size() - 1]);
                    auto level_string = str.substr(brace_left.idx + 1, brace_right.idx - brace_left.idx - 1);
                    auto level_idx = braces.size();
                    levels[level_idx].emplace_back(level_string);

                    braces.pop_back();
                    braces.pop_back();
                }
            }
        };

        auto evaluate_level = [&](const std::size_t idx) {
            const std::size_t parent_idx = idx - 1;
            const std::vector<std::string> potential_parents = levels[parent_idx];
            std::string parent;

            for(const std::string& i : potential_parents) // parent (-1)
                for(const std::string& j : levels[idx]) // current ()
                    if(i.contains(j))
                        families[idx].emplace_back(family{i, j, ""});
        };

        auto evaluate_childfolder = [&](const std::size_t idx){
            for(auto& fam : families[idx]) {
                auto [parent, child, folder] = nstd::var(fam.parent, fam.child, fam.child_folder);
                auto child_idx = parent.find(child); // ..., f: {file.txt}
                auto semicolon_idx = parent.rfind(':', child_idx); // :
                auto comma_idx = parent.rfind(',', semicolon_idx); // ,

                std::string folder_name;
                if(comma_idx != std::string::npos)
                    folder_name = parent.substr(comma_idx + 2, semicolon_idx - comma_idx - 2);
                else
                    folder_name = parent.substr(0, semicolon_idx);
                folder = folder_name;
            }
        };
        
        auto evaluate_childfolder_order = [&](const std::size_t idx){
            const auto min = (*(std::min_element(families.begin(), families.end(), [](auto& l, auto & r) { return l.first < r.first; }))).first;
            const auto max = (*(std::max_element(families.begin(), families.end(), [](auto& l, auto & r) { return l.first < r.first; }))).first;
            for(auto& fam : families[idx]) {
                auto [parent, child, folder] = nstd::var(fam.parent, fam.child, fam.child_folder);
                std::string folder_name = "";

                for(std::size_t i = min; i <= max; ++i) {
                    if(i >= idx)
                        break;
                    folder_name = "";
                    for(auto& check_fam : families[i]) {
                        auto [check_parent, check_child, check_folder] = nstd::var(check_fam.parent, check_fam.child, check_fam.child_folder);
                        if(check_child.contains(folder + ":"))
                            folder_name += check_folder + "/";
                    }
                }
                folder = folder_name + folder;
            }
        };

        std::vector<std::string> paths;
        auto generate_paths = [&] (const std::size_t idx) {
            for(auto& fam : families[idx]) {
                auto [parent, child, folder] = nstd::var(fam.parent, fam.child, fam.child_folder);
                auto child_string = child;
                if(auto found = child.find(":"); found != std::string::npos)
                    child_string = child.substr(0, child.find(":") + 1);
                auto parts = nstd::split(child_string, ',');
                
                if(parts.empty())
                    continue;
                if(parts.back().contains(":"))
                    parts.pop_back();
                for(auto& e : parts) {
                    if(e.find('.') == std::string::npos)
                        e += ".txt";
                    paths.emplace_back(folder + "/" + e);
                }
            }
        };  

        auto fix_paths = [&]{
            for(auto& e : paths)
                e = nstd::replace_all(e, "/ ", "/");
        };


        auto log_levels = [&]{
            for(const auto &[idx, level] : levels) {
                for (const auto& e : level) {
                    std::cout << idx << ": " << e << "\n";
                }
                std::cout << "\n";
            }
        };

        auto log_families = [&]{
            for(const auto& [i, _families] : families) {
                std::cout << "[" << i << "]:\n";
                for(const auto & _family : _families) {
                    std::cout << "parent==" << _family.parent << "\n";
                    std::cout << "child==" << _family.child << "\n";
                    std::cout << "folder==" << _family.child_folder << "\n\n";
                }
                std::cout << "\n\n";
            }
        };

        auto build = [&] {
            parse();
            auto evaluate = [&](const std::size_t idx) {
                evaluate_level(idx);
                evaluate_childfolder(idx);
                evaluate_childfolder_order(idx);
                generate_paths(idx);
            };
            evaluate(3);
            
            std::size_t count = 0;
            for(const auto& e : families[3])
                if(auto size = nstd::count(e.child, '{'); size > count)
                    count = size;
                    
            for(std::size_t i = 4; i < 4 + count; ++i)
                evaluate(i);
            fix_paths();
        };


        auto log_paths = [&] {
            for(const auto& e : paths)
                std::cout << e << "\n";
        };


        build();

        return paths;
    }
}