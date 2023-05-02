#include <iostream>

template <typename T>
class GoodClass {
    int _size;
public:
    GoodClass(int size = 10) 
    : _size(size) {
    }

    int size() const {
        return _size;
    }

    void normalize() {
        std::cout << "normalized" << std::endl;
    }
};

template <typename T>
class BadClass {
    int _size;
public:
    BadClass(int size = 10) 
    : _size(size) {
    }

    void normalize() {
        std::cout << "normalized" << std::endl;
    }
};

template <typename T>
void doProcessing(T& obj) {
    std::cout << "size: " << obj.size() << std::endl;
    obj.normalize();
}

int main() {
    GoodClass<int> good;
    //BadClass<int> bad; // does not compile

    doProcessing(good);
    //doProcessing(bad);

    return 0;
}