#include <fstream>
#include <iostream>

int main() {
    std::ifstream input("input");
    long d = 0, h = 0, aim = 0;

    std::string c, p;
    do {
        input >> c;
        input >> p;
        if(input.eof()) break;

        if(c == "forward") {
            auto v = std::strtol(p.c_str(), nullptr, 0);
            h += v;
            d += aim * v;
        } else if(c == "down") {
            aim += std::strtol(p.c_str(), nullptr, 0);
        } else if(c == "up") {
            aim -= std::strtol(p.c_str(), nullptr, 0);
        } else throw 0;
    } while(not input.eof());

    std::cout << (d * h) << std::endl;
}
