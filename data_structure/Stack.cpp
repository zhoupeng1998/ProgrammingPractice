//
//  Stack.cpp
//  proj0
//
//  Created by Peng Zhou on 2019/8/24.
//  Copyright © 2019 ZP. All rights reserved.
//

#include "Stack.hpp"

DSZP::Stack::Stack() :
    capacity(10), size(0), buf(new int[11]), cur(buf) {
}

DSZP::Stack::Stack(const DSZP::Stack& s) :
    capacity(s.capacity), size(s.size), buf(new int[s.capacity+1]), cur(buf) {
        for (int i = 1; i <= size; ++i) {
            buf[i] = s.buf[i];
            ++cur;
        }
}

DSZP::Stack DSZP::Stack::operator = (const Stack &s) {
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

void DSZP::Stack::expand() {
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

bool DSZP::Stack::empty() const {
    return size == 0;
}

int DSZP::Stack::getSize() {
    return size;
}

void DSZP::Stack::push(int i) {
    size++;
    if (size > capacity) {
        expand();
    }
    *++cur = i;
}

void DSZP::Stack::pop() {
    if (!empty()) {
        --cur;
        --size;
    }
}

int& DSZP::Stack::top() {
    if (empty()) {
        throw "Stack Empty";
    }
    return *cur;
}

DSZP::Stack::~Stack() {
    delete [] buf;
}
