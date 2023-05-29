#include <iostream>

class Base {
public:
    virtual void show() {
        std::cout << "Base::show()" << std::endl;
    }
};

class Derived : public Base {
private:
    void show() {
        std::cout << "Derived::show()" << std::endl;
    }
};

int main() {
    // private inheritance? Don't use Base pointer because you don't want to use Derived class as Base class.
    Base* p = new Derived();
    p->show();
    delete p;
    return 0;
}