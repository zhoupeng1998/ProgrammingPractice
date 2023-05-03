#include <iostream>

class CompanyA {
public:
    void sendCleartext(const std::string& msg) {
        std::cout << "CompanyA: " << msg << " (clear)"<< std::endl;
    }

    void sendEncrypted(const std::string& msg) {
        std::cout << "CompanyA: " << msg << " (encrypted)" << std::endl;
    }
};

class CompanyB {
public:
    void sendCleartext(const std::string& msg) {
        std::cout << "CompanyB: " << msg << " (clear)"<< std::endl;
    }

    void sendEncrypted(const std::string& msg) {
        std::cout << "CompanyB: " << msg << " (encrypted)" << std::endl;
    }
};

template <typename Company>
class MsgSender {
public:
    void sendClear(const std::string& msg) {
        Company c;
        c.sendCleartext(msg);
    }

    void sendSecret(const std::string& msg) {
        Company c;
        c.sendEncrypted(msg);
    }
};

template <typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
    // alternative 1: using "using" keyword
    // using MsgSender<Company>::sendClear;

    void sendClearMsg(const std::string& msg) {
        std::cout << "Log before sending..." << std::endl;
        // Without "this->", the compiler will not find the name "sendClear" in the base class
        this->sendClear(msg);
        
        // alternative 2: using "MsgSender<Company>::" keyword
        // MsgSender<Company>::sendClear(msg);
        std::cout << "Log after sending..." << std::endl;
    }
};

int main() {
    MsgSender<CompanyA> msgSender;
    msgSender.sendClear("hello");

    LoggingMsgSender<CompanyA> loggingMsgSender;
    loggingMsgSender.sendClearMsg("hello");

    return 0;
}