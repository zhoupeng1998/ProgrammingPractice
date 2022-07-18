#include "stack.h"

namespace ZP {

Stack::Stack() :
    capacity(10), size(0), buf(new int[11]), cur(buf) {
}

Stack::Stack(const Stack& s) :
    capacity(s.capacity), size(s.size), buf(new int[s.capacity+1]), cur(buf) {
        for (int i = 1; i <= size; ++i) {
            buf[i] = s.buf[i];
            ++cur;
        }
}

Stack Stack::operator = (const Stack &s) {
    delete [] buf;
    capacity = s.capacity;
    size = s.size;
    buf = new int[capacity+1];
    cur = buf;
    for (int i = 1; i <= size; ++i) {
        buf[i] = s.buf[i];
        ++cur;
    }
    return *this;
}

void Stack::expand() {
    capacity *= 2;
    int* newbuf = new int[capacity+1];
    cur = newbuf;
    for (int i = 1; i < size; ++i) {
        newbuf[i] = buf[i];
        ++cur;
    }
    delete [] buf;
    buf = newbuf;
}

bool Stack::empty() const {
    return size == 0;
}

int Stack::getSize() {
    return size;
}

void Stack::push(int i) {
    size++;
    if (size > capacity) {
        expand();
    }
    *++cur = i;
}

void Stack::pop() {
    if (!empty()) {
        --cur;
        --size;
    }
}

int& Stack::top() {
    if (empty()) {
        throw "Stack Empty";
    }
    return *cur;
}

Stack::~Stack() {
    delete [] buf;
}

}