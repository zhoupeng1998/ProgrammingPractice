//
//  AVLTree.cpp
//  proj0
//
//  Created by Peng Zhou on 2019/9/6.
//  Copyright © 2019 ZP. All rights reserved.
//

#include "AVLTree.hpp"

DSZP::AVLTree::AVLTree () :
BinarySearchTree() {
}

DSZP::AVLTree::AVLTree (const AVLTree& tree) :
BinarySearchTree(tree) {
}

DSZP::AVLTree DSZP::AVLTree::operator = (const AVLTree &tree) {
    removeAll(head);
    size = tree.size;
    head = copy(tree.head);
    return *this;
}
/*
void DSZP::AVLTree::add (int i) {
    DSZP::BinarySearchTree::add(i);
}
*/

DSZP::TreeNode* DSZP::AVLTree::addNode (int i, TreeNode *&tn) {
    if (!tn) {
        tn = new TreeNode();
        tn->info = i;
        tn->left = nullptr;
        tn->right = nullptr;
        // tn->height = 0;
    } else if (i < tn->info) {
        addNode(i, tn->left);
        if (getTreeHeight(tn->left) - getTreeHeight(tn->right) >= 2) {
            if (i < tn->left->info) {
                tn = rotateLL(tn);
            } else {
                tn = rotateLR(tn);
            }
        }
    } else if (i > tn->info) {
        addNode(i, tn->right);
        if (getTreeHeight(tn->right) - getTreeHeight(tn->left) >= 2) {
            if (i > tn->right->info) {
                tn = rotateRR(tn);
            } else {
                tn = rotateRL(tn);
            }
        }
    } else {
        return nullptr;
    }
    return tn;
}

int DSZP::AVLTree::getTreeHeight (TreeNode* tn) {
    if (!tn) {
        return -1;
    }
    int leftHeight = getTreeHeight(tn->left), rightHeight = getTreeHeight(tn->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

DSZP::TreeNode* DSZP::AVLTree::rotateLL (TreeNode *tn) {
    TreeNode* temp = tn->left;
    tn->left = temp->right;
    temp->right = tn;
    return temp;
}

DSZP::TreeNode* DSZP::AVLTree::rotateRR (TreeNode *tn) {
    TreeNode* temp = tn->right;
    tn->right = temp->left;
    temp->left = tn;
    return temp;
}

DSZP::TreeNode* DSZP::AVLTree::rotateLR (TreeNode *tn) {
    tn->left = rotateRR(tn->left);
    return rotateLL(tn);
}

DSZP::TreeNode* DSZP::AVLTree::rotateRL (TreeNode *tn) {
    tn->right = rotateLL(tn->right);
    return rotateRR(tn);
}
