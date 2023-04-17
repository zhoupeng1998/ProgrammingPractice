#ifndef __VALUES_H__
#define __VALUES_H__

#include <unordered_map>

const int delta = 30;
extern std::unordered_map<char, std::unordered_map<char, int>> alpha;

void initAlpha();

#endif