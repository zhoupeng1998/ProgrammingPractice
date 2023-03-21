#include <iostream>
#include <thread>

void f(int i, const std::string& s) {
    std::cout << i << " " << s << std::endl;
}

void oops(int param) {
    char buf[1024];
    sprintf(buf, "%i", param);
    std::thread t(f, 3, buf); // dangling pointer (may be freed)
    t.detach();
}

void not_oops(int param) {
    char buf[1024];
    sprintf(buf, "%i", param);
    std::thread t(f, 3, std::string(buf));
    t.detach();
}