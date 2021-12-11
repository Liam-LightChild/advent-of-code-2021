#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

int main() {
    std::ifstream input("input");
    std::vector<int> zero, one;

    std::string str;
    input >> str;
    zero.resize(str.length(), 0);
    one.resize(str.length(), 0);

    do {
        for (int i = 0; i < str.length(); ++i) {
            auto c = str[i];
            if(c == '0') zero[i] += 1;
            else if(c == '1') one[i] += 1;
            else abort();
        }

        input >> str;
    } while(!input.eof());

    long g = 0, e = 0;

    for (int i = 0; i < zero.size(); ++i) {
        g <<= 1;
        e <<= 1;
        if(one[i] > zero[i]) g |= 1;
        else e |= 1;
    }

    std::cout << "G: " << g << ", E: " << e << std::endl;
    std::cout << "Result: " << (g * e) << std::endl;
}