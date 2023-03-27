// This demonstrate Effective C++ item 33: "Avoid hiding inherited names"

#include <iostream>

class Base {
public:
    virtual void mf1() = 0;
    virtual void mf1(int n);
    virtual void mf2();
    void mf3();
    void mf3(double n);
};

class Derived : public Base {
public:
    // the "using" keyword must be public to make it visible to outside
    using Base::mf1;
    using Base::mf3;
    virtual void mf1();
    void mf3();
    void mf4();
};

void Base::mf1(int n) {
    std::cout << "Base::mf1(int n) " << n << std::endl;
}

void Base::mf2() {
    std::cout << "Base::mf2()" << std::endl;
}

void Base::mf3() {
    std::cout << "Base::mf3()" << std::endl;
}

void Base::mf3(double n) {
    std::cout << "Base::mf3(double n) " << n << std::endl;
}

void Derived::mf1() {
    std::cout << "Derived::mf1()" << std::endl;
}

void Derived::mf3() {
    std::cout << "Derived::mf3()" << std::endl;
}

void Derived::mf4() {
    std::cout << "Derived::mf4()" << std::endl;
}

void tryit() {

    Derived d;
    d.mf1(); //ok
    d.mf1(1); //err
    d.mf2();
    d.mf3();
    d.mf3(1); //err
}

int main() {
    tryit();
    return 0;
}