//
//  BinarySearchTree.cpp
//  proj0
//
//  Created by Peng Zhou on 2019/9/1.
//  Copyright © 2019 ZP. All rights reserved.
//

#include <iostream>
#include "BinarySearchTree.hpp"

DSZP::BinarySearchTree::BinarySearchTree () :
size(0), head(nullptr) {
}

DSZP::BinarySearchTree::BinarySearchTree (const BinarySearchTree& tree) :
size(tree.size), head(copy(tree.head)) {
}

DSZP::BinarySearchTree DSZP::BinarySearchTree::operator = (const BinarySearchTree &tree) {
    removeAll(head);
    size = tree.size;
    head = copy(tree.head);
    return *this;
}

DSZP::TreeNode* DSZP::BinarySearchTree::copy (TreeNode *src) {
    if (src) {
        DSZP::TreeNode* node = new DSZP::TreeNode();
        node->info = src->info;
        node->left = copy(src->left);
        node->right = copy(src->right);
        return node;
    } else {
        return nullptr;
    }
}

int DSZP::BinarySearchTree::getSize () {
    return size;
}

void DSZP::BinarySearchTree::add (int i) {
    if (addNode(i, head)) {
        ++size;
    }
}

DSZP::TreeNode* DSZP::BinarySearchTree::addNode (int i, TreeNode*& tn) {
    if (!tn) {
        tn = new TreeNode();
        tn->info = i;
        tn->left = nullptr;
        tn->right = nullptr;
        return tn;
    } else if (i < tn->info) {
        return addNode(i, tn->left);
    } else if (i > tn->info) {
        return addNode(i, tn->right);
    }
    return nullptr;
}

bool DSZP::BinarySearchTree::contains (int i) {
    return findNode(i, head);
}

bool DSZP::BinarySearchTree::findNode (int i, TreeNode *tn) {
    if (!tn) {
        return false;
    } else if (tn->info == i) {
        return true;
    } else {
        return findNode(i, tn->left) || findNode(i, tn->right);
    }
}

void DSZP::BinarySearchTree::traversalPreorder () {
    preorder(head);
}

void DSZP::BinarySearchTree::preorder (TreeNode* tn) {
    if (tn) {
        std::cout << tn->info << " ";
        preorder(tn->left);
        preorder(tn->right);
    }
}

void DSZP::BinarySearchTree::traversalInorder () {
    inorder(head);
}

void DSZP::BinarySearchTree::inorder (TreeNode* tn) {
    if (tn) {
        inorder(tn->left);
        std::cout << tn->info << " ";
        inorder(tn->right);
    }
}

void DSZP::BinarySearchTree::traversalPostorder () {
    postorder(head);
}

void DSZP::BinarySearchTree::postorder (TreeNode *tn) {
    if (tn) {
        postorder(tn->left);
        postorder(tn->right);
        std::cout << tn->info << " ";
    }
}

void DSZP::BinarySearchTree::removeAll (TreeNode *tn) {
    if (tn) {
        removeAll(tn->left);
        removeAll(tn->right);
        delete tn;
    }
}

DSZP::BinarySearchTree::~BinarySearchTree() {
    removeAll(head);
}
    
