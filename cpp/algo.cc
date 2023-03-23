#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

int main() {
    std::cout << std::boolalpha;
    std::vector<int> vec{1, 2, 3, 4, 5};

    auto it1 = vec.begin();
    ++it1;
    auto it2 = vec.begin();
    std::advance(it2, 3); // it2 now points to the 4th element
    std::cout << *it1 << " " << *it2 << '\n';
    std::cout << std::accumulate(it1, it2, 0) << '\n'; // 2 + 3
    std::cout << std::accumulate(it1, it2, std::distance(it1, it2)) << '\n';
    return 0;
}