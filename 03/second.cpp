#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

int main() {
    std::ifstream input("input");
    std::string str;

    std::vector<std::string> vec;

    input >> str;
    do {
        vec.emplace_back(str);
        input >> str;
    } while(not input.eof());

    enum { zero_most_common, one_most_common, equal } most_common;

    auto len = vec[0].length();

    std::vector<std::string> oxy_vals, co2_vals;

    {
        int z = 0, o = 0;

        for (auto& s : vec) {
            if(s[0] == '1') o++;
            else if(s[0] == '0') z++;
        }

        if(o > z) most_common = one_most_common;
        else if(z > o) most_common = zero_most_common;
        else most_common = equal;

        for(auto& s : vec) {
            if(s[0] == '1' && (most_common == one_most_common || most_common == equal) ||
               s[0] == '0' && (most_common == zero_most_common))
                oxy_vals.emplace_back(s);

            if(s[0] == '1' && (most_common == zero_most_common) ||
               s[0] == '0' && (most_common == one_most_common || most_common == equal))
                co2_vals.emplace_back(s);
        }
    }

    for (int i = 1; i < len; ++i) {
        int z = 0, o = 0;


        if(oxy_vals.size() > 1) {
            for (auto& s : oxy_vals) {
                if(s[i] == '1') o++;
                else if(s[i] == '0') z++;
            }

            if(o > z) most_common = one_most_common;
            else if(z > o) most_common = zero_most_common;
            else most_common = equal;

            for (int j = (int)oxy_vals.size() - 1; j >= 0; --j) {
                auto s = oxy_vals[j];
                if(s[i] == '1' && (most_common == zero_most_common) ||
                   s[i] == '0' && (most_common == one_most_common || most_common == equal))
                    oxy_vals.erase(oxy_vals.begin() + j);
                if(oxy_vals.size() <= 1) break;
            }
        }

        if(co2_vals.size() > 1) {
            for (auto& s : co2_vals) {
                if(s[i] == '1') o++;
                else if(s[i] == '0') z++;
            }

            if(o > z) most_common = one_most_common;
            else if(z > o) most_common = zero_most_common;
            else most_common = equal;

            for (int j = (int)co2_vals.size() - 1; j >= 0; --j) {
                auto s = co2_vals[j];
                if(s[i] == '1' && (most_common == one_most_common || most_common == equal) ||
                   s[i] == '0' && (most_common == zero_most_common))
                    co2_vals.erase(co2_vals.begin() + j);
                if(co2_vals.size() <= 1) break;
            }
        }
    }

    auto a = strtol(oxy_vals[0].c_str(), nullptr, 2);
    auto b = strtol(co2_vals[0].c_str(), nullptr, 2);
    std::cout << oxy_vals[0] << " * " << co2_vals[0] << " = " << (a * b) << std::endl;
}
