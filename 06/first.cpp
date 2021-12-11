#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream input("input");
    long values[9];

    for (long & value : values) {
        value = 0;
    }

    {
        std::string s, b;
        input >> s;

        for (auto &c: s) {
            if (c == ',') {
                values[std::strtol(b.c_str(), nullptr, 0)]++;
                b.clear();
            } else b.append(&c, 1);
        }

        values[std::strtol(b.c_str(), nullptr, 0)]++;
    }

    for (int i = 0; i < 80; ++i) {
        auto to_create = values[0];

        for (int j = 0; j < 8; ++j) {
            values[j] = values[j+1];
        }

        values[6] += to_create;
        values[8] = to_create;
    }

    long sum = 0;
    for (auto& v : values) {
        sum += v;
    }

    std::cout << "total: " << sum << std::endl;
}
