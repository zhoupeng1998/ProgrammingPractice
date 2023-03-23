#include <iostream>
#include <thread>
#include <string>

// cannot pass non-const params
void f(int i, const std::string& s) {
    // sleep for 1 second to see the effect of passing by reference
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "In thread: " << i << " " << s << std::endl;
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

void oops_again(int param) {
    std::string data = std::to_string(param);
    std::thread t(f, 3, std::ref(data)); // use std::ref to pass by reference
    data += " modified";
    t.join();
    std::cout << data << std::endl;
}

int main() {
    std::cout << "hardware_concurrency: " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
    oops_again(3);
    //
    std::thread t1(f, 1, std::string("Hello"));
    std::thread t2 = std::move(t1);
    t1 = std::thread(f, 2, std::string("World"));
    std::thread t3;
    t3 = std::move(t2);
    t1 = std::move(t3); // this will call std::terminate, because t1 is already running
    std::cout << "Are we terminated?" << std::endl;
    t1.join();
    //t2.join();
    //t3.join();
    return 0;
}