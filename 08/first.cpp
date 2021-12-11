#include "common.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    if(argc < 2 ){
        std::cerr << "usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    std::string str;
    input.seekg(0, std::ios::end);
    str.resize(input.tellg());
    input.seekg(0);
    input.read(str.data(), (long)str.size());
    input.close();

    std::vector<line> lines;
    while(!str.empty()) {
        auto sub = str.substr(0, str.find('\n'));
        str = str.substr(str.find('\n')+1);
        lines.emplace_back(sub);
    }

    long count = 0;

    for(auto& l : lines) {
        for (auto &v : l.values) {
            switch (v.size()) {
                case 2:
                case 4:
                case 3:
                case 7:
                    count++;
                    break;
            }
        }
    }

    std::cout << count << std::endl;
}
