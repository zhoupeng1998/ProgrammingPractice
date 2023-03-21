// this example shows how objects calls const member functions

#include <iostream>

class MyClass {
    int myVar;

public:
    MyClass(): myVar(5) {}

    int myFunc() const {
        //myVar++; // must be read-only
        return myVar * myVar;
    }

    int myFunc() {
        return myVar;
    }
};

int main() {
    MyClass a;
    const MyClass b;
    std::cout << a.myFunc() << std::endl;
    std::cout << b.myFunc() << std::endl; // const object must have const member function!!!
    return 0;
}