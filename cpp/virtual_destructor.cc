// this examples shows what happens with virtual destructor

#include <iostream>

class ClassA {
    int a;

public:
    ClassA(): a(0) {
    }

    ClassA(int n): a(n) {
    }

    // only if base class destructor declared virtual, derived class destructor will be called
    // when deleting a base class pointer pointing to a derived class object
    // This prevents memory leak
    virtual ~ClassA() {
        std::cout << "Base class destructor called" << std::endl;
    }
};

class ClassB: public ClassA {
    int b;

public:
    ClassB(): ClassA(), b(0) {
    }

    ClassB(int i, int j): ClassA(i), b(j) {
    }

    ~ClassB() {
        std::cout << "Derived class destructor called" << std::endl;
    }
};

int main() {
    ClassA* obj = new ClassB(1, 2);
    delete obj;

    return 0;
}

// Note: std::string, std::vector, std::unordered_map, etc. have non-virtual destructors
// bad idea to use them as base class (From Effective C++)

// Making a class without virtual functions abstract: add pure virtual destructor
// (must add definition because it will be called)