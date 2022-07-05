//
//  LinkedList.cpp
//  proj0
//
//  Created by Peng Zhou on 2019/8/25.
//  Copyright © 2019 ZP. All rights reserved.
//

#include "LinkedList.hpp"

DSZP::LinkedList::LinkedList () :
    size(0), head(nullptr) {
}

DSZP::LinkedList::LinkedList(const LinkedList& ll) :
size(0), head(nullptr) {
    copy(ll.head);
}

DSZP::LinkedList DSZP::LinkedList::operator = (const LinkedList& ll) {
    while (head) {
        removeFirst();
    }
    head = nullptr;
    copy(ll.head);
    return *this;
}

void DSZP::LinkedList::copy (ListNode *ln) {
    if (ln) {
        copy(ln->next);
        addFirst(ln->info);
    }
}

int DSZP::LinkedList::getSize () {
    return size;
}

void DSZP::LinkedList::addFirst (int val) {
    ListNode* ln = new ListNode();
    ln->info = val;
    ln->next = head;
    head = ln;
    ++size;
}

void DSZP::LinkedList::addLast (int val) {
    if (!head) {
        addFirst(val);
    } else {
        ListNode* ln = new ListNode();
        ln->info = val;
        ln->next = nullptr;
        ListNode* temp;
        for (temp = head; temp->next; temp = temp->next) {
        }
        temp->next = ln;
        ++size;
    }
}

int DSZP::LinkedList::removeFirst () {
    if (!head) {
        throw "Empty Linked List";
    }
    int ret = head->info;
    ListNode* temp = head;
    head = head->next;
    --size;
    delete temp;
    return ret;
}

int DSZP::LinkedList::removeLast () {
    if (!head) {
        throw "Empty Linked List";
    } else if (head->next == nullptr) {
        int ret = head->info;
        delete head;
        head = nullptr;
        --size;
        return ret;
    } else {
        ListNode* temp;
        for (temp = head; temp->next->next; temp = temp->next) {
        }
        ListNode* last = temp->next;
        int ret = last->info;
        delete last;
        --size;
        temp->next = nullptr;
        return ret;
    }
}

void DSZP::LinkedList::insert (int pos, int val) {
    if (!head || pos <= 0) {
        addFirst(val);
    } else if (pos >= size) {
        addLast(val);
    } else {
        ListNode* temp1 = head;
        for (int i = 1; i < pos; ++i) {
            temp1 = temp1->next;
        }
        ListNode* temp2 = temp1->next;
        ListNode* mid = new ListNode();
        mid->info = val;
        mid->next = temp2;
        temp1->next = mid;
        ++size;
    }
}

int DSZP::LinkedList::remove (int pos) {
    if (!head) {
        throw "empty list";
    }
    if (pos <= 0) {
        return removeFirst();
    } else if (pos >= size) {
        return removeLast();
    } else {
        ListNode* temp1 = head;
        for (int i = 1; i < pos; ++i) {
            temp1 = temp1->next;
        }
        ListNode* temp2 = temp1->next;
        int ret = temp2->info;
        temp1->next = temp2->next;
        delete temp2;
        --size;
        return ret;
    }
}

std::ostream& DSZP::operator << (std::ostream& out, const LinkedList& ll) {
    if (ll.size == 0) {
        return out;
    }
    ListNode* ln;
    for (ln = ll.head; ln->next; ln = ln->next) {
        out << ln->info << ", ";
    }
    out << ln->info;
    return out;
}

void DSZP::LinkedList::reverse () {
    if (size <= 1) {
        return;
    }
    ListNode *first = nullptr, *second = head, *third = head->next;
    while (third) {
        second->next = first;
        first = second;
        second = third;
        third = third->next;
    }
    second->next = first;
    head = second;
}

int& DSZP::LinkedList::operator [] (int pos) {
    if (pos < 0 || pos >= size) {
        throw "Index out of bound";
    }
    ListNode* temp = head;
    for (int i = 0; i < pos; ++i) {
        temp = temp->next;
    }
    return temp->info;
}

DSZP::LinkedList::~LinkedList () {
    while (head) {
        removeFirst();
    }
}
