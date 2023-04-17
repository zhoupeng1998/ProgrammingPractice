#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "generator.h"

std::vector<std::string> genString() {
    std::vector<std::string> strs;
    std::ifstream ifile("input.txt", std::ios::in);
    std::string buf;
    std::string current;
    while (ifile >> buf) {
        if (isalpha(buf[0])) {
            if (current.size() > 0) {
                strs.push_back(current);
            }
            current = buf;
        } else {
            int index = std::stoi(buf);
            std::string next = current.substr(0, index + 1) + current + current.substr(index + 1);
            current = next;
        }
    }
    if (current.size() > 0) {
        strs.push_back(current);
    }
    for (auto& s : strs) {
        std::cout << s << std::endl;
    }
    ifile.close();
    return strs;
}