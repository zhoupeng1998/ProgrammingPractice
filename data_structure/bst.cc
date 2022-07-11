#include <iostream>
#include "bst.h"

namespace ZP {

BinarySearchTree::BinarySearchTree () :
size(0), head(nullptr) {
}

BinarySearchTree::BinarySearchTree (const BinarySearchTree& tree) :
size(tree.size), head(copy(tree.head)) {
}

BinarySearchTree BinarySearchTree::operator = (const BinarySearchTree &tree) {
    removeAll(head);
    size = tree.size;
    head = copy(tree.head);
    return *this;
}

TreeNode* BinarySearchTree::copy (TreeNode *src) {
    if (src) {
        TreeNode* node = new TreeNode();
        node->info = src->info;
        node->left = copy(src->left);
        node->right = copy(src->right);
        return node;
    } else {
        return nullptr;
    }
}

int BinarySearchTree::getSize () {
    return size;
}

void BinarySearchTree::add (int i) {
    if (addNode(i, head)) {
        ++size;
    }
}

TreeNode* BinarySearchTree::addNode (int i, TreeNode*& tn) {
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

bool BinarySearchTree::contains (int i) {
    return findNode(i, head);
}

bool BinarySearchTree::findNode (int i, TreeNode *tn) {
    if (!tn) {
        return false;
    } else if (tn->info == i) {
        return true;
    } else {
        return findNode(i, tn->left) || findNode(i, tn->right);
    }
}

void BinarySearchTree::traversalPreorder () {
    preorder(head);
}

void BinarySearchTree::preorder (TreeNode* tn) {
    if (tn) {
        std::cout << tn->info << " ";
        preorder(tn->left);
        preorder(tn->right);
    }
}

void BinarySearchTree::traversalInorder () {
    inorder(head);
}

void BinarySearchTree::inorder (TreeNode* tn) {
    if (tn) {
        inorder(tn->left);
        std::cout << tn->info << " ";
        inorder(tn->right);
    }
}

void BinarySearchTree::traversalPostorder () {
    postorder(head);
}

void BinarySearchTree::postorder (TreeNode *tn) {
    if (tn) {
        postorder(tn->left);
        postorder(tn->right);
        std::cout << tn->info << " ";
    }
}

void BinarySearchTree::removeAll (TreeNode *tn) {
    if (tn) {
        removeAll(tn->left);
        removeAll(tn->right);
        delete tn;
    }
}

BinarySearchTree::~BinarySearchTree() {
    removeAll(head);
}
    
}
