#include <iostream>

#include "shared.h"

int main() {
    std::cout << "Calling from A: ";
    call_shared();
    return 0;
}