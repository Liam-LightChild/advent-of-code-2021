#include <fstream>
#include <iostream>

int main() {
    std::ifstream input("input.txt");
    std::string str;
    input >> str;
    long prev = std::strtol(str.c_str(), nullptr, 0);
    long result = 0;

    do {
        input >> str;
        long val = std::strtol(str.c_str(), nullptr, 0);
        if(val > prev) result++;
        prev = val;
    } while(!input.eof());

    std::cout << result << std::endl;
}
