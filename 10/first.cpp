#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

struct mapping {
    char open, close;
    long points;
};

const mapping mappings[] {
        {'(', ')', 3},
        {'[', ']', 57},
        {'{', '}', 1197},
        {'<', '>', 25137}
};

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    std::string buf;

    std::vector<long> points;

    while(true) {
        input >> buf;
        if(input.eof()) break;

        std::stack<const mapping*> stack;

        for(auto& c : buf) {
            auto orig = stack.empty() ? nullptr : stack.top();
            bool changed = false;

            for(auto& m : mappings) {
                if(c == m.open) {
                    stack.push(&m);
                    changed = true;
                }
            }

            if(changed)
                continue;

            if (c != stack.top()->close)
                for (auto &m: mappings)
                    if (m.close == c)
                        points.emplace_back(m.points);
            stack.pop();
        }
    }

    long total = 0;

    for(auto& p : points) {
        total += p;
        std::cout << (total-p) << " + " << p << " = " << total << std::endl;
    }

    std::cout << total << std::endl;
}