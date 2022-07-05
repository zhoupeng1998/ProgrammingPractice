//
//  ArrayList.cpp
//  proj0
//
//  Created by Peng Zhou on 2019/8/27.
//  Copyright © 2019 ZP. All rights reserved.
//

#include "ArrayList.hpp"

DSZP::ArrayList::ArrayList ():
size(0), capacity(10), buf(new int[10]) {
}

DSZP::ArrayList::ArrayList (const ArrayList& al) :
size(al.size), capacity(al.capacity), buf(new int[al.size]) {
    for (int i = 0; i < size; ++i) {
        buf[i] = al.buf[i];
    }
}

void DSZP::ArrayList::expand () {
    capacity *= 2;
    int* newbuf = new int[capacity];
    for (int i = 0; i < size; ++i) {
        newbuf[i] = buf[i];
    }
    delete [] buf;
    buf = newbuf;
}

DSZP::ArrayList DSZP::ArrayList::operator = (const ArrayList &al) {
    delete [] buf;
    size = al.size;
    capacity = al.capacity;
    for (int i = 0; i < size; ++i) {
        buf[i] = al.buf[i];
    }
    return *this;
}

int DSZP::ArrayList::getSize () {
    return size;
}

void DSZP::ArrayList::insert (int pos, int val) {
    if (pos < 0) {
        addFirst(val);
    } else if (pos >= size) {
        addLast(val);
    } else {
        if (size >= capacity) {
            expand();
        }
        for (int i = size - 1; i >= pos; --i) {
            buf[i+1] = buf[i];
        }
        buf[pos] = val;
        ++size;
    }
}

void DSZP::ArrayList::addLast (int val) {
    if (size >= capacity) {
        expand();
    }
    buf[size++] = val;
}

void DSZP::ArrayList::addFirst (int val) {
    if (size >= capacity) {
        expand();
    }
    insert(0, val);
}

int DSZP::ArrayList::remove (int pos) {
    if (!size) {
        throw "Empty list";
    }
    if (pos < 0) {
        return removeFirst();
    } else if (pos >= size) {
        return removeLast();
    } else {
        int ret = buf[pos];
        for (int i = pos; i < size; ++i) {
            buf[i] = buf[i+1];
        }
        --size;
        return ret;
    }
}

int DSZP::ArrayList::removeFirst() {
    return remove(0);
}

int DSZP::ArrayList::removeLast() {
    if (!size) {
        throw "Empty list";
    }
    return buf[size--];
}

int& DSZP::ArrayList::operator [] (int pos) {
    if (pos < 0 || pos >= size) {
        throw "Index out of bound";
    }
    return buf[pos];
}

void DSZP::ArrayList::reverse () {
    if (!size) {
        return;
    }
    int startIndex = 0, endIndex = size - 1;
    for (; startIndex < endIndex; startIndex++, endIndex--) {
        int temp = buf[startIndex];
        buf[startIndex] = buf[endIndex];
        buf[endIndex] = temp;
    }
}

std::ostream& DSZP::operator << (std::ostream& out, const ArrayList& al) {
    if (!al.size) {
        return out;
    } else {
        int i = 0;
        for (; i < al.size - 1; ++i) {
            std::cout << al.buf[i] << ", ";
        }
        std::cout << al.buf[i];
    }
    return out;
}

DSZP::ArrayList::~ArrayList () {
    delete [] buf;
}
