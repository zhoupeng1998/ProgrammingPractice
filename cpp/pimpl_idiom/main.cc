#include <iostream>

#include "person_impl.h"
#include "person.h"

int main() {
    Person p("John", 20);
    std::cout << p.name() << " is " << p.age() << " years old" << std::endl;
    return 0;
}