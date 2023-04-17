#include <string>
#include <vector>

#include "values.h"
#include "generator.h"
#include "basic.h"

int main(void) {
    initAlpha();
    std::vector<std::string> strs = genString();
    std::string s0 = strs[0];
    std::string s1 = strs[1];
    auto ret = alignmentBasic(s0, s1, 0, strs[0].size() - 1, 0, strs[1].size() - 1);
    return 0;
}

//
//ACACTGACTACTGACTGGTGACTACTGACTGG
//ACACTGACTACTGACTGGTGACTACTGACTGG
//
//TATTATACGCTATTATACGCGACGCGGACGCG