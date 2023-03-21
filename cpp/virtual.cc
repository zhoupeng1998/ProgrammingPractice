// this shows some virtual function examples

#include <iostream>

class ClassA {
public:
    // not virtual!
    void myFunc() {
        std::cout << "Class A func" << std::endl;
    }
};

class ClassB : public ClassA {
public:
    virtual void myFunc() {
        std::cout << "Class B func" << std::endl;
    }
};

class ClassC : public ClassB {
public:
    void myFunc() {
        std::cout << "Class C func" << std::endl;
    }
};

int main() {
    ClassA* p1 = new ClassB();
    ClassB* p2 = new ClassC();
    ClassA* p3 = new ClassC();
    p1->myFunc();
    p2->myFunc(); // Calling C's function
    p3->myFunc(); // Calling A's function because in A it's non virtual
    return 0;
}