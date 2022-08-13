#include <iostream>

#include "binary_min_heap.h"

namespace ZP {

BinaryMinHeap::BinaryMinHeap() {}

BinaryMinHeap::BinaryMinHeap(const BinaryMinHeap& heap)
: _arr(heap._arr) {}

BinaryMinHeap& BinaryMinHeap::operator=(const BinaryMinHeap& heap) {
    _arr = heap._arr;
    return *this;
}

void BinaryMinHeap::push(int num) {
    int pos = _arr.size() + 1;
    _arr.push_back(num);
    int parent = pos / 2;
    while (pos != 1 && _arr[parent - 1] > _arr[pos - 1]) {
        std::swap(_arr[parent - 1], _arr[pos - 1]);
        pos = parent;
        parent = pos / 2;
    }
}

void BinaryMinHeap::pop() {
    std::swap(_arr[0], _arr[_arr.size() - 1]);
    _arr.pop_back();
    int pos = 1;
    while (pos <= _arr.size()) {
        int left = pos * 2;
        int right = pos * 2 + 1;
        if (right <= _arr.size()) {
            if (_arr[pos - 1] < std::min(_arr[left - 1], _arr[right - 1])) {
                break;
            }
            if (_arr[left - 1] < _arr[right - 1]) {
                std::swap(_arr[pos - 1], _arr[left - 1]);
                pos = left;
            } else {
                std::swap(_arr[pos - 1], _arr[right - 1]);
                pos = right;
            }
        } else {
            if (left <= _arr.size() && _arr[pos - 1] > _arr[left - 1]) {
                std::swap(_arr[pos - 1], _arr[left - 1]);
            }
            break;
        }
    }
}

}