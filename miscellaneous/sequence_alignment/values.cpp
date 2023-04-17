#include "values.h"

std::unordered_map<char, std::unordered_map<char, int>> alpha;

void initAlpha() {
    alpha['A']['A'] = 0;
    alpha['A']['C'] = 110;
    alpha['A']['G'] = 48;
    alpha['A']['T'] = 94;

    alpha['C']['A'] = 110;
    alpha['C']['C'] = 0;
    alpha['C']['G'] = 118;
    alpha['C']['T'] = 48;

    alpha['G']['A'] = 48;
    alpha['G']['C'] = 118;
    alpha['G']['G'] = 0;
    alpha['G']['T'] = 110;

    alpha['T']['A'] = 94;
    alpha['T']['C'] = 48;
    alpha['T']['G'] = 110;
    alpha['T']['T'] = 0; 
}