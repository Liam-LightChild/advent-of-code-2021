#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>

struct mapping {
    char open, close;
    long points;
};

const mapping mappings[] {
        {'(', ')', 1},
        {'[', ']', 2},
        {'{', '}', 3},
        {'<', '>', 4}
};

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    std::string buf;

    std::vector<long> scores;

    while(true) {
        input >> buf;
        if(input.eof()) break;

        std::stack<const mapping*> stack;
        bool keep = true;

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

            if (c != stack.top()->close) {
                keep = false;
                break;
            } else stack.pop();
        }

        if(!keep || stack.empty()) continue;

        scores.emplace_back(0);
        while(!stack.empty()) {
            scores.back() *= 5;
            scores.back() += stack.top()->points;
            stack.pop();
        }
    }

    std::sort(scores.begin(), scores.end());
    auto index = (int) std::floor((double)scores.size() / 2.0);
    std::cout << scores[index] << std::endl;
}