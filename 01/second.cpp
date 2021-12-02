#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream input("input.txt");
    std::string str;

    std::vector<long> values;
    while(true) {
        input >> str;
        if(input.eof()) break;
        values.emplace_back(std::strtol(str.c_str(), nullptr, 0));
    }

    std::vector<long> sums;
    for (int i = 2; i < values.size(); ++i) {
        sums.emplace_back(values[i - 2] + values[i - 1] + values[i]);
    }

    long prev = sums[0];
    long result = 0;

    std::cout << prev << " START" << std::endl;
    for (int i = 1; i < sums.size(); ++i) {
        long v = sums[i];
        std::cout << prev << " > " << v << std::endl;
        if(v > prev) result++;
        prev = v;
    }
    std::cout << prev << " END" << std::endl;

    std::cout << result << std::endl;
}
