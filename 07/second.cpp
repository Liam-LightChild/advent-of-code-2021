#include <fstream>
#include <vector>
#include <iostream>

int main() {
    std::ifstream input("input");
    std::vector<short> values;

    std::string str, buf;
    input >> str;

    while(true) {
        auto comma = str.find(',');
        if(comma != std::string::npos) {
            values.emplace_back(std::strtol(str.substr(0, comma).c_str(), nullptr, 0));
            str = str.substr(comma+1);
        } else {
            values.emplace_back(std::strtol(str.c_str(), nullptr, 0));
            break;
        }
    }

    std::vector<long> fuels(10000);

    for (int i = 0; i < 10000; ++i) {
        long diff = 0;

        for(auto v : values) {
            int d = std::abs(i - v);
            for (long j = 1; j <= d; ++j) diff += j;
        }

        fuels[i] = diff;
    }

    long lowest = INT32_MAX;
    for(auto v : fuels) if(v < lowest) lowest = v;

    std::cout << lowest << std::endl;
}
