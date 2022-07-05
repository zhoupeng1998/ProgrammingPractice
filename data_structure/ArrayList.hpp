//
//  ArrayList.hpp
//  proj0
//
//  Created by Peng Zhou on 2019/8/27.
//  Copyright © 2019 ZP. All rights reserved.
//

#ifndef ArrayList_hpp
#define ArrayList_hpp

#include <iostream>

namespace DSZP {
    class ArrayList {
        int* buf;
        int size;
        int capacity;
        //void copy (ListNode* ln);
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

#endif /* ArrayList_hpp */
