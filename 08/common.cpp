#include <algorithm>
#include <sstream>
#include "common.h"

auto line::get_values() -> std::array<int, 4> {
    std::vector<std::string> vec;
    for(auto& p : patterns) vec.emplace_back(p);

    return {
            (int)(std::find_if(vec.begin(), vec.end(), [&](const auto& item){ return item == values[0]; }) - vec.begin()),
            (int)(std::find_if(vec.begin(), vec.end(), [&](const auto& item){ return item == values[1]; }) - vec.begin()),
            (int)(std::find_if(vec.begin(), vec.end(), [&](const auto& item){ return item == values[2]; }) - vec.begin()),
            (int)(std::find_if(vec.begin(), vec.end(), [&](const auto& item){ return item == values[3]; }) - vec.begin()),
    };
}

line::line(const std::string& str) {
    std::stringstream s(str);
    std::string buf;
    int i = 0, j = 0;
    bool in_values = false;

    while(!s.eof()) {
        s >> buf;

        if(buf == "|") in_values = !in_values;
        else {
            if(!in_values) {
                if(i >= 10) throw std::runtime_error("too many patterns");
                patterns[i++] = buf;
            } else {
                if(j >= 4) throw std::runtime_error("too many values");
                values[j++] = buf;
            }
        }
    }
}
