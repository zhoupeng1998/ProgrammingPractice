#include <string.h>

#include "string.h"

namespace ZP {

String::String()
: _size(0), _capacity(10), _buf(new char[11]) {
    _buf[0] = '\0';
}

String::String(const char* str)
: _size(0), _capacity(10), _buf(nullptr) {
    int len = strlen(str);
    while (_size + len >= _capacity) {
        _capacity *= 2;
    }
    _buf = new char[_capacity + 1];
    strcpy(_buf, str);
    _size = len;
}

String::String(const String& str)
: _size(str._size), _capacity(str._capacity), _buf(new char[_capacity]) {
    strcpy(_buf, str._buf);
}

String::~String() {
    if (_buf) {
        delete [] _buf;
    }
}

String& String::operator=(const char* str) {
    int capacity = _capacity;
    int len = strlen(str);
    while (len >= capacity) {
        capacity *= 2;
    }
    if (capacity > _capacity) {
        _capacity = capacity;
        delete [] _buf;
    }
    _buf = new char[_capacity + 1];
    strcpy(_buf, str);
    _size = len;
    return *this;
}

String& String::operator=(const String& str) {
    if (_capacity < str._capacity) {
        _capacity = str._capacity;
        delete [] _buf;
        _buf = new char[_capacity + 1];
    }
    strcpy(_buf, str._buf);
    _size = str._size;
    return *this;
}

void String::append(const char* str) {
    int len = strlen(str);
    int capacity = _capacity;
    char* temp = nullptr;
    while (_size + len >= capacity) {
        capacity *= 2;
    }
    if (capacity > _capacity) {
        char* temp = _buf;
        _buf = new char[capacity + 1];
        _capacity = capacity;
        strcpy(_buf, temp);
        _buf = temp;
    }
    char* ptr = _buf + _size;
    strcpy(ptr, str);
    _size += len;
    if (temp) {
        delete [] temp;
    }
}

String& String::operator+=(const char* str) {
    append(str);
    return *this;
}

String& String::operator+=(const String& str) {
    const char* ptr = str._buf;
    append(ptr);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    if (str._buf != nullptr) {
        os << str._buf;
    }
    return os;
}

}