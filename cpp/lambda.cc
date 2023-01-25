#include <iostream>
#include <functional>

class A {
    int data;
public:
    A(int d) :data(d) {
        std::cout << "Constructor called! " << data << std::endl;
    }

    A(const A& a) :data(a.data) {
        std::cout << "Copy constructor called! " << data << std::endl;
    }

    int getData() {
        return data;
    }

    int getData() const {
        return data;
    }    
};

int main() {
    A a(1);
    A b(2);
    std::function<void(int)> lambda1 = [=](int param) {
        std::cout << "called lambda 1 " << a.getData() + b.getData() + param << std::endl;
    };
    // NOTE: copied a and b object after lambda 1 defined
    lambda1(0);
    auto lambda2 = [=](int param) {
        std::cout << "called lambda 2 " << a.getData() + param << std::endl;
    };
    // NOTE: copied a object after lambda 2 defined
    //lambda2(0);
    auto lambda3 = [a, &b](int param) {
        std::cout << "called lambda 3 " << a.getData() + param << std::endl;
    };
    // NOTE: copied a object after lambda 3 defined
    lambda3(0);

    return 0;
}