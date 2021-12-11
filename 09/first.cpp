#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    auto data = new char[2];
    data[1] = 0;

    uint8_t **array = nullptr;
    int x = 0, y = 0, s = 0, sy = 0;

    while(true) {
        std::string buf;
        input >> buf;
        if(input.eof()) break;
        array = static_cast<uint8_t **>(reallocarray(array, ++sy, sizeof(uint8_t *)));
        if(s == 0) array[y] = nullptr;
        else array[y] = static_cast<uint8_t *>(malloc(s * sizeof(uint8_t)));

        for(auto& c : buf) {
            if(x >= s) {
                s = x + 1;
                for (int i = 0; i < sy; ++i) {
                    array[i] = static_cast<uint8_t *>(reallocarray(array[i], s, sizeof(uint8_t)));
                }
            }

            data[0] = c;
            array[y][x] = std::strtol(data, nullptr, 0);
            x++;
        }

        y++;
        x = 0;
    }

    delete[] data;

    bool matches[sy][s];
    for (int j = 0; j < sy; ++j) {
        for (int i = 0; i < s; ++i) {
            auto value = array[j][i];

            if(j > 0 && value >= array[j-1][i]) goto noMatch;
            if(j < sy-1 && value >= array[j+1][i]) goto noMatch;
            if(i > 0 && value >= array[j][i-1]) goto noMatch;
            if(i < s-1 && value >= array[j][i+1]) goto noMatch;

            matches[j][i] = true;
            continue;

            noMatch:
            matches[j][i] = false;
        }
    }

    int sum = 0;
    for (int j = 0; j < sy; ++j) {
        if(array[j] == nullptr) continue;
        for (int i = 0; i < s; ++i) {
            if(matches[j][i]) {
                std::cout << "\u001b[1m";
                sum += 1 + array[j][i];
            } else {
                std::cout << "\u001b[0m";
            }
            std::cout << (int) array[j][i];
        }
        std::cout << std::endl;
    }
    std::cout << "\u001b[0msum: " << sum << std::endl;

    input.close();
}