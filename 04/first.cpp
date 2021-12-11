#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>

struct board {
    uint16_t values[5][5];
    bool matched[5][5];
};

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::vector<board> boards;
    std::ifstream input(argv[1]);

    std::string numbers;
    input >> numbers;

    std::string buffer;

    while(true) {
        board b = {};

        for (int j = 0; j < 5; ++j) {
            for (int i = 0; i < 5; ++i) {
                input >> buffer;
                b.values[i][j] = std::strtol(buffer.c_str(), nullptr, 0);
                b.matched[i][j] = false;
            }
        }

        if(input.eof()) break;
    }
}
