// What if we redefine default parameter in derived class?
// virtual func use dynamic binding, but params are always static binding!

#include <iostream>
#include <string>

class Base {
public:
    enum Color { red, green, blue };

    std::string color(Color c) const {
        if (c == red) {
            return "red";
        } else if (c == green) {
            return "green";
        } else {
            return "blue";
        }
    }

    virtual void mf1(Color c = red) {
        std::cout << "Base::mf1(Color c = " << color(c) << ")" << std::endl;
    }

    virtual void mf2() {
        std::cout << "mf2(), ";
        domf();
    }

private:
    virtual void domf() {
        std::cout << "Base::domf(Color c = red)" << std::endl;
    }
};

class Derived : public Base {
public:
    virtual void mf1(Color c = green) {
        std::cout << "Derived::mf1(Color c = " << color(c) << ")" << std::endl;
    }

private:
    virtual void domf() {
        std::cout << "Derived::domf(Color c = green)" << std::endl;
    }
};

int main() {
    Base* p1 = new Base();
    Base* p2 = new Derived();
    p1->mf1();
    p2->mf1();
    std::cout << "------------------" << std::endl;
    p1->mf2();
    p2->mf2();
    delete p1;
    delete p2;
    return 0;
}