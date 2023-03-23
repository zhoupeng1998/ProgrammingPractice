#include <thread>
#include <iostream>

void thread_function(int i) {
    for (int j = 0; j < 100; ++j) {
        std::cout << "In thread: " << i << std::endl;
    }
}

class scoped_thread {
public:
    // Constructor: takes ownership of the thread object
    explicit scoped_thread(std::thread&& t) : t_(std::move(t)) {}

    // Destructor: joins the thread if it is joinable
    ~scoped_thread() {
        if (t_.joinable()) {
            t_.join();
        }
    }

    // Copy and move constructors/assignment operators are deleted to prevent copying or moving of the owned thread
    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;
    //scoped_thread(scoped_thread&&) = delete;
    //scoped_thread& operator=(scoped_thread&&) = delete;

private:
    std::thread t_;
};

int main() {
    // Create a scoped_thread object that owns an std::thread object
    scoped_thread t(std::thread(thread_function, 1));
    std::thread t2(thread_function, 2);
    scoped_thread t3(std::move(t2));

    return 0;
}
