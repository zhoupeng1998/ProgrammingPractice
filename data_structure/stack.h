#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

namespace ZP {

class Stack {
    int* buf;
    int* cur;
    int size, capacity;
    void expand ();
public:
    Stack ();
    Stack (const Stack& s);
    Stack operator = (const Stack& s);
    bool empty () const;
    int getSize ();
    void push (int i);
    void pop ();
    int& top ();
    ~Stack ();
};

}

#endif
