#include <iostream>

// a template function specifying array size
template<int x, int y>
void get(int arr[x][y], int i, int j) {
    std::cout << arr[i][j]++ << std::endl;
}

int main() {
    int arr[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            arr[i][j] = i * 5 + j;
        }
    }
    get<5, 5>(arr, 3, 4);
    std::cout << arr[3][4] << std::endl;
}