#include "arraylist.h"

namespace ZP {

ArrayList::ArrayList ():
size(0), capacity(10), buf(new int[10]) {
}

ArrayList::ArrayList (const ArrayList& al) :
size(al.size), capacity(al.capacity), buf(new int[al.size]) {
    for (int i = 0; i < size; ++i) {
        buf[i] = al.buf[i];
    }
}

void ArrayList::expand () {
    capacity *= 2;
    int* newbuf = new int[capacity];
    for (int i = 0; i < size; ++i) {
        newbuf[i] = buf[i];
    }
    delete [] buf;
    buf = newbuf;
}

ArrayList ArrayList::operator = (const ArrayList &al) {
    delete [] buf;
    size = al.size;
    capacity = al.capacity;
    for (int i = 0; i < size; ++i) {
        buf[i] = al.buf[i];
    }
    return *this;
}

int ArrayList::getSize () {
    return size;
}

void ArrayList::insert (int pos, int val) {
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

void ArrayList::addLast (int val) {
    if (size >= capacity) {
        expand();
    }
    buf[size++] = val;
}

void ArrayList::addFirst (int val) {
    if (size >= capacity) {
        expand();
    }
    insert(0, val);
}

int ArrayList::remove (int pos) {
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

int ArrayList::removeFirst() {
    return remove(0);
}

int ArrayList::removeLast() {
    if (!size) {
        throw "Empty list";
    }
    return buf[size--];
}

int& ArrayList::operator [] (int pos) {
    if (pos < 0 || pos >= size) {
        throw "Index out of bound";
    }
    return buf[pos];
}

void ArrayList::reverse () {
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

std::ostream& operator << (std::ostream& out, const ArrayList& al) {
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

ArrayList::~ArrayList () {
    delete [] buf;
}

}
