#include <thread>

class ThreadGuard {
    std::thread& t;

public:
    explicit ThreadGuard(std::thread& t_)
        :t(t_) {}
    
    ~ThreadGuard() {
        if (t.joinable()) {
            t.join();
        }
    }

    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

