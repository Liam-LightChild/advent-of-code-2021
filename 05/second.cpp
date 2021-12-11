#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>

struct point {
    int x, y;
};

struct line {
    point a, b;
};

#define STRING_BUF_COUNT 3
#define NUMBER_COUNT 4
#define NUMBER_SEP ','

std::vector<line> lines;
std::string strings[STRING_BUF_COUNT]; // [0] and [1] for points; [2] is for that damn arrow
std::string number_strings[NUMBER_COUNT]; // [0] = x1; [1] = y1; [2] = x2; [3] = y2
int numbers[NUMBER_COUNT]; // same as above
std::unordered_map<int, std::unordered_map<int, int>> map;

line* create_line(std::ifstream &input) {
    input >> strings[0] >> strings[2] >> strings[1];
    if(input.eof()) return nullptr;

    size_t sep_loc[2] = {
            strings[0].find(NUMBER_SEP),
            strings[1].find(NUMBER_SEP)
    };

    number_strings[0] = strings[0].substr(0, sep_loc[0]);
    number_strings[1] = strings[0].substr(sep_loc[0]+1);
    number_strings[2] = strings[1].substr(0, sep_loc[1]);
    number_strings[3] = strings[1].substr(sep_loc[1]+1);

    for (int i = 0; i < NUMBER_COUNT; ++i) {
        numbers[i] = static_cast<typeof(*numbers)>(std::strtol(number_strings[i].c_str(), nullptr, 0));
    }

    line l {
        .a = point { numbers[0], numbers[1] },
        .b = point { numbers[2], numbers[3] }
    };

    lines.emplace_back(l);

    return &*(lines.end()-1);
}

void draw_line_h(const line& l) {
    if(l.a.x > l.b.x) {
        for (int i = l.b.x; i <= l.a.x; ++i) {
            map[l.a.y][i]++;
        }
    } else if(l.a.x < l.b.x) {
        for (int i = l.a.x; i <= l.b.x; ++i) {
            map[l.a.y][i]++;
        }
    } else {
        map[l.a.y][l.a.x]++;
    }
}

void draw_line_v(const line& l) {
    if(l.a.y > l.b.y) {
        for (int i = l.b.y; i <= l.a.y; ++i) {
            map[i][l.a.x]++;
        }
    } else if(l.a.y < l.b.y) {
        for (int i = l.a.y; i <= l.b.y; ++i) {
            map[i][l.a.x]++;
        }
    } else {
        map[l.a.y][l.a.x]++;
    }
}

/*
 * Very janky loop time.
 */
void draw_line_d(const line& l) {
    if(l.a.x > l.b.x && l.a.y > l.b.y) {
        for(int i = l.a.x, j = l.a.y; i >= l.b.x && j >= l.b.y;) {
            map[j][i]++;
            i--; j--;
        }
    } else if(l.a.x > l.b.x && l.a.y < l.b.y) {
        for(int i = l.a.x, j = l.a.y; i >= l.b.x && j <= l.b.y;) {
            map[j][i]++;
            i--; j++;
        }
    } else if(l.a.x < l.b.x && l.a.y > l.b.y) {
        for(int i = l.a.x, j = l.a.y; i <= l.b.x && j >= l.b.y;) {
            map[j][i]++;
            i++; j--;
        }
    } else if(l.a.x < l.b.x && l.a.y < l.b.y) {
        for(int i = l.a.x, j = l.a.y; i <= l.b.x && j <= l.b.y;) {
            map[j][i]++;
            i++; j++;
        }
    } else {
        map[l.a.y][l.a.x]++;
    }
}

void draw_line(const line& l) {
    if(l.a.x == l.b.x) draw_line_v(l);
    else if(l.a.y == l.b.y) draw_line_h(l);
    else draw_line_d(l);
}

int count_map(int comparison = 2) {
    int return_value = 0;

    for(auto& [y, row] : map) {
        for(auto& [x, v] : row) {
            if(v >= comparison) return_value++;
        }
    }

    return return_value;
}

int main() {
    std::ifstream input("input");

    do {
        create_line(input);
    } while(!input.eof());

    for(auto& l : lines)
        draw_line(l);

    std::cout << count_map() << std::endl;
}