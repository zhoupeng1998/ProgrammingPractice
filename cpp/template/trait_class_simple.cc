#include <iostream>

// simpler explanation for trait class

template <typename T>
struct Traits {
    static constexpr bool isInteger = false;
};

template <>
struct Traits<int> {
    static constexpr bool isInteger = true;
};

template <typename T>
void processValue(const T& value) {
    if (Traits<T>::isInteger) {
        std::cout << "Integer type" << std::endl;
        // Perform integer-specific operations
    } else {
        std::cout << "Non-integer type" << std::endl;
        // Perform operations for non-integer types
    }
}

int main() {
    processValue(5);
    processValue(5.0);
    return 0;
}