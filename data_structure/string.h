#ifndef STRING_H_
#define STRING_H_

#include <iostream>

namespace ZP{

class String {

    int _size;
    int _capacity;
    char* _buf;

public:

    String();
    String(const char* str);
    String(const String& str);
    ~String();

    String& operator=(const char* str);
    String& operator=(const String& str);

    String& operator+=(const char* str);
    String& operator+=(const String& str);

    inline int size() { return _size; }
    inline int capacity() { return _capacity; }
    inline const char* c_str() { return _buf; }

    friend std::ostream& operator<<(std::ostream& os, const String& str);

private:

    void append(const char* str);

};

std::ostream& operator<<(std::ostream& os, const String& str);

}

#endif