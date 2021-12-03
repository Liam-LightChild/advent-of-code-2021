#include <fstream>
#include <iostream>

int main() {
    std::ifstream input("input");
    long d = 0, h = 0;

    std::string c, p;
    do {
        input >> c;
        input >> p;
        if(input.eof()) break;

        if(c == "forward") {
            h += std::strtol(p.c_str(), nullptr, 0);
        } else if(c == "down") {
            d += std::strtol(p.c_str(), nullptr, 0);
        } else if(c == "up") {
            d -= std::strtol(p.c_str(), nullptr, 0);
        } else throw 0;
    } while(not input.eof());

    std::cout << (d * h) << std::endl;
}
