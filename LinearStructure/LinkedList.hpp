//
//  LinkedList.hpp
//  proj0
//
//  Created by Peng Zhou on 2019/8/25.
//  Copyright © 2019 ZP. All rights reserved.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <iostream>


namespace DSZP {
    struct ListNode {
        int info;
        ListNode* next;
    };
    class LinkedList {
        ListNode* head;
        int size;
        void copy (ListNode* ln);
    public:
        LinkedList ();
        LinkedList (const LinkedList& ll);
        LinkedList operator = (const LinkedList& ll);
        int getSize ();
        void addFirst (int val);
        void addLast (int val);
        int removeFirst ();
        int removeLast ();
        void insert (int pos, int val);
        int remove (int pos);
        int& operator [] (int pos);
        void reverse ();
        friend std::ostream& operator << (std::ostream& out, const LinkedList& ll);
        ~LinkedList() ;
    };
}


#endif /* LinkedList_hpp */
