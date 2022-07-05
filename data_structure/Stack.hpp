//
//  Stack.hpp
//  proj0
//
//  Created by Peng Zhou on 2019/8/24.
//  Copyright © 2019 ZP. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>

namespace DSZP {
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

#endif /* Stack_hpp */
