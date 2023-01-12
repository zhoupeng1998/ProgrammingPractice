#include <iostream>

#include "shared.h"

int main() {
    std::cout << "Calling from B: ";
    call_shared();
    return 0;
}