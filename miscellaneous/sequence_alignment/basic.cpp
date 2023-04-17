#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "values.h"
#include "basic.h"

std::vector<std::vector<int>> alignmentBasic(std::string& X, std::string& Y, int xbegin, int xend, int ybegin, int yend) {
    std::vector<std::vector<int>> result;
    std::vector<std::vector<int>> dp(yend - ybegin + 2, std::vector<int>(xend - xbegin + 2));
    for (int i = 1; i < dp.size(); i++) {
        dp[i][0] = i * delta;
    }
    for (int j = 1; j < dp[0].size(); j++) {
        dp[0][j] = j * delta;
    }
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 1; j < dp[i].size(); j++) {
            dp[i][j] = std::min(alpha[X[i + xbegin - 1]][Y[j + ybegin - 1]] + dp[i - 1][j - 1], std::min(dp[i - 1][j], dp[i][j - 1]) + delta);
        }
    }
    return result;
}