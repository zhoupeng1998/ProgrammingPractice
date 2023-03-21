#include <iostream>
#include <thread>

void hello() {
    std::cout << "hello concurrent world" << std::endl;
}

int main() {
    std::thread t(hello);
    t.join();
    // t.detach();
    // assert(!t.joinable());

    return 0;
}