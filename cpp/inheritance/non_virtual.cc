// What if we redefine non-virtual function in derived class?

#include <iostream>

class Base {
public:
    void mf1() {
        std::cout << "Base::mf1()" << std::endl;
    }

    virtual void mf2() {
        std::cout << "Base::mf2()" << std::endl;
    }
};

class Derived : public Base {
public:
    void mf1() {
        std::cout << "Derived::mf1()" << std::endl;
    }

    virtual void mf2() {
        std::cout << "Derived::mf2()" << std::endl;
    }
};

int main() {
    Derived d;
    Base* p1 = &d;
    Derived* p2 = &d;
    p1->mf1();
    p2->mf1();
    std::cout << "------------------" << std::endl;
    p1->mf2();
    p2->mf2();
    return 0;
}