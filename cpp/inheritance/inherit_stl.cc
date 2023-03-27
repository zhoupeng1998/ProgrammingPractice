// this example shows why not to use inheritance with STL containers

#include <iostream>
#include <vector>

class MyVector: public std::vector<int> {
    int* extraArray;

public:

    MyVector(int n): std::vector<int>(n), extraArray(new int[10]) {
        std::cout << "Arg constructor called!!" << std::endl;
    }

    ~MyVector() {
        std::cout << "Destructor called!" << std::endl;
        delete[] extraArray;
    }
};

int main() {
    // will produce memory leak! the destructor of MyVector will not be called
    // because the destructor of std::vector is not virtual
    // use valgrind to see the leak
    std::vector<int>* v = new MyVector(10);
    delete v;
    return 0;
}