#include "avl_tree.h"

namespace ZP {

AVLTree::AVLTree () :
BinarySearchTree() {
}

AVLTree::AVLTree (const AVLTree& tree) :
BinarySearchTree(tree) {
}

AVLTree AVLTree::operator = (const AVLTree &tree) {
    removeAll(head);
    size = tree.size;
    head = copy(tree.head);
    return *this;
}
/*
void AVLTree::add (int i) {
    BinarySearchTree::add(i);
}
*/

TreeNode* AVLTree::addNode (int i, TreeNode *&tn) {
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

int AVLTree::getTreeHeight (TreeNode* tn) {
    if (!tn) {
        return -1;
    }
    int leftHeight = getTreeHeight(tn->left), rightHeight = getTreeHeight(tn->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

TreeNode* AVLTree::rotateLL (TreeNode *tn) {
    TreeNode* temp = tn->left;
    tn->left = temp->right;
    temp->right = tn;
    return temp;
}

TreeNode* AVLTree::rotateRR (TreeNode *tn) {
    TreeNode* temp = tn->right;
    tn->right = temp->left;
    temp->left = tn;
    return temp;
}

TreeNode* AVLTree::rotateLR (TreeNode *tn) {
    tn->left = rotateRR(tn->left);
    return rotateLL(tn);
}

TreeNode* AVLTree::rotateRL (TreeNode *tn) {
    tn->right = rotateLL(tn->right);
    return rotateRR(tn);
}

}
