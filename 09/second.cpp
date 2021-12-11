#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>


struct pos {
    int x, y;

    pos(int x, int y) : x(x), y(y) {}

    bool operator==(const pos &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const pos &rhs) const {
        return !(rhs == *this);
    }
};

void process_match(std::vector<pos> &basin, uint8_t **array, pos pos, int sx, int sy);

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

    std::list<pos> matches;

    for (int j = 0; j < sy; ++j) {
        for (int i = 0; i < s; ++i) {
            auto value = array[j][i];

            if(j > 0 && value >= array[j-1][i]) continue;
            if(j < sy-1 && value >= array[j+1][i]) continue;
            if(i > 0 && value >= array[j][i-1]) continue;
            if(i < s-1 && value >= array[j][i+1]) continue;

            matches.emplace_back(i, j);
        }
    }

    std::vector<size_t> basins;
    for(auto& match : matches) {
        std::vector<pos> basin {};
        process_match(basin, array, match, s, sy);
        basins.emplace_back(basin.size());
    }

    std::sort(basins.begin(), basins.end());
    std::reverse(basins.begin(), basins.end());
    std::cout << "result: " << (basins[0] * basins[1] * basins[2]) << std::endl;

    input.close();
}

void process_match(std::vector<pos> &basin, uint8_t **array, pos pos, int s, int sy) {
    auto [i, j] = pos;
    if(array[j][i] != 9) {
        basin.emplace_back(pos);
        if(j > 0 && array[j-1][i] != 9 && std::find(basin.begin(), basin.end(), ::pos {i, j-1}) == basin.end())
            process_match(basin, array, ::pos {i, j-1}, s, sy);
        if(j < sy-1 && array[j+1][i] != 9 && std::find(basin.begin(), basin.end(), ::pos {i, j+1}) == basin.end())
            process_match(basin, array, ::pos {i, j+1}, s, sy);
        if(i > 0 && array[j][i-1] != 9 && std::find(basin.begin(), basin.end(), ::pos {i-1, j}) == basin.end())
            process_match(basin, array, ::pos {i-1, j}, s, sy);
        if(i < s-1 && array[j][i+1] != 9 && std::find(basin.begin(), basin.end(), ::pos {i+1, j}) == basin.end())
            process_match(basin, array, ::pos {i+1, j}, s, sy);
    }
}
