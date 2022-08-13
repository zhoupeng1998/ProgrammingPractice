#ifndef BINARY_MIN_HEAP_H_
#define BINARY_MIN_HEAP_H_

#include <vector>

namespace ZP {

class BinaryMinHeap {
public:
    std::vector<int> _arr;

public:
    
    BinaryMinHeap();
    BinaryMinHeap(const BinaryMinHeap& heap);

    BinaryMinHeap& operator=(const BinaryMinHeap& heap);

    inline int size() { return _arr.size(); }
    inline int top() { return _arr[0]; }
    void push(int num);
    void pop();

};

}

#endif