#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "bst.h"

namespace ZP {

class AVLTree : public BinarySearchTree {
public:
    AVLTree ();
    AVLTree (const AVLTree& tree);
    AVLTree operator = (const AVLTree& tree);
protected:
    TreeNode* addNode (int i, TreeNode*& tn);
private:
    static int getTreeHeight (TreeNode* tn);
    static TreeNode* rotateLL (TreeNode* tn);
    static TreeNode* rotateRR (TreeNode* tn);
    static TreeNode* rotateLR (TreeNode* tn);
    static TreeNode* rotateRL (TreeNode* tn);
};

}

#endif
