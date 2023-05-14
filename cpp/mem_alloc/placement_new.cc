#include <iostream>
#include <new>
#include <memory>

class MyClass {
public:
    MyClass(int arg1, double arg2) : m_data1(arg1), m_data2(arg2) {
        std::cout << "MyClass constructor" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor" << std::endl;
    }

    // Placement new
    static void* operator new(size_t size, void* ptr) {
        std::cout << "Placement new" << std::endl;
        return ::operator new(size, ptr);
    }

    // Placement delete
    static void operator delete(void* ptr, void* place) {
        std::cout << "Placement delete" << std::endl;
        ::operator delete(ptr, place);
    }

    // Regular new and delete
    static void* operator new(size_t size) {
        std::cout << "Regular new" << std::endl;
        return ::operator new(size);
    }

    static void operator delete(void* ptr) {
        std::cout << "Regular delete" << std::endl;
        ::operator delete(ptr);
    }

private:
    int m_data1;
    double m_data2;
};

int main() {
    void* memory = ::operator new(sizeof(MyClass));
    MyClass* obj = new (memory) MyClass(1, 2.0);

    // ...

    obj->~MyClass();
    // Why is placement delete not called here?
    ::operator delete(obj, memory);

    return 0;
}
