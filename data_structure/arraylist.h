#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <iostream>

namespace ZP {

class ArrayList {
    int* buf;
    int size;
    int capacity;
    void expand ();
public:
    ArrayList ();
    ArrayList (const ArrayList& al);
    ArrayList operator = (const ArrayList& al);
    int getSize ();
    void addFirst (int val);
    void addLast (int val);
    int removeFirst ();
    int removeLast ();
    void insert (int pos, int val);
    int remove (int pos);
    int& operator [] (int pos);
    void reverse ();
    friend std::ostream& operator << (std::ostream& out, const ArrayList& al);
    ~ArrayList() ;
};

}

#endif
