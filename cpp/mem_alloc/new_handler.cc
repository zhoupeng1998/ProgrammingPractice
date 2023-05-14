#include <iostream>
#include <new>

class Widget {
public:
    static std::new_handler set_new_handler(std::new_handler p) noexcept;
    static void* operator new(std::size_t size) noexcept(std::is_nothrow_constructible<std::bad_alloc>::value);
};

std::new_handler Widget::set_new_handler(std::new_handler p) noexcept {
    return std::set_new_handler(p);
}

void* Widget::operator new(std::size_t size) noexcept(std::is_nothrow_constructible<std::bad_alloc>::value) {
    return ::operator new(size);
}

void out_of_memory() {
    std::cerr << "Unable to satisfy request for memory (customized handler called)\n";
    std::abort();
}

int main() {
    // test new_handler
    Widget::set_new_handler(out_of_memory);
    // try alloc memory
    Widget* pw1;

    try
    {
        pw1 = static_cast<Widget*>(::operator new(1000000000000));
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "Bad alloc: " << e.what() << '\n';
    }
    
    

    delete pw1;
    return 0;
}