#include <iostream>
#include <memory>

#include "person.h"

int main(void) {
    std::unique_ptr<Person> p = Person::create("John", 20);
    std::cout << p->name() << " is " << p->age() << " years old" << std::endl;
    return 0;
}