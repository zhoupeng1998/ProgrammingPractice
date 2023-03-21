// this examples shows how initializtion member variables in objects works

#include <iostream>

class ClassA {
    int num;

public:
    ClassA(): num(0) {
        std::cout << "Default constructor called!!" << std::endl;
    }

    ClassA(int n): num(n) {
        std::cout << "Arg constructor called!!" << std::endl;
    }

    ClassA(const ClassA& obj): num(obj.num) {
        std::cout << "Copy constructor called!" << std::endl;
    }
};

class ClassB {
    ClassA mem1;
    ClassA mem2;

public:

    // only explicitly initialize mem2 here
    // it calls mem1's default constructor first, then mem2's arg constructor
    ClassB(int mem): mem2(mem) {
        std::cout << "B's constructor(A) called!" << std::endl;
    }

    ClassB(const ClassA& mem): mem1(mem) {
        std::cout << "B's constructor(A) called!" << std::endl;
    }

};

int main() {
    ClassB b(5);
    return 0;
}