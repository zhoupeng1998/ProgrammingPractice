//
//  AVLTree.hpp
//  proj0
//
//  Created by Peng Zhou on 2019/9/6.
//  Copyright © 2019 ZP. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include "BinarySearchTree.hpp"

namespace DSZP {
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

#endif /* AVLTree_hpp */
