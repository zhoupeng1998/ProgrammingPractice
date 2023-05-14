#include <iostream>
#include <memory>

class Widget {
public:
    // operator new and delete functions automatically treated as static
    void* operator new(std::size_t size) noexcept(std::is_nothrow_constructible<std::bad_alloc>::value);
    void operator delete(void* pMemory) noexcept;
};

void* Widget::operator new(std::size_t size) noexcept(std::is_nothrow_constructible<std::bad_alloc>::value) {
    void* ptr = std::malloc(size);
    std::cout << "Allocated " << size << " bytes" << std::endl;
    return ptr;
}

void Widget::operator delete(void* pMemory) noexcept {
    std::cout << "Deallocated memory" << std::endl;
    std::free(pMemory);
}

int main() {
    // test new_handler
    Widget w;
    Widget* pw1 = new Widget;
    Widget* pw2 = static_cast<Widget*>(Widget::operator new(100));
    
    delete pw1;
    delete pw2;
    return 0;
}