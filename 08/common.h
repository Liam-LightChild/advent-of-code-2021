//
// Created by liam on 12/7/21.
//

#ifndef AOC2021_COMMON_H
#define AOC2021_COMMON_H

#include <string>
#include <vector>
#include <array>

struct line {
    std::string patterns[10];
    std::string values[4];

    explicit line(const std::string& str);
    auto get_values() -> std::array<int, 4>;
};

#endif //AOC2021_COMMON_H
