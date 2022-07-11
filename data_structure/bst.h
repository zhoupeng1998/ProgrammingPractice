#ifndef BST_H_
#define BST_H_

namespace ZP {

struct TreeNode {
    int info;
    TreeNode* left;
    TreeNode* right;
    // int height;
};

class BinarySearchTree {
protected:
    int size;
    TreeNode* head;
public:
    BinarySearchTree ();
    BinarySearchTree (const BinarySearchTree& tree);
    BinarySearchTree operator = (const BinarySearchTree& tree);
    int getSize ();
    bool contains (int i);
    virtual void add (int i);
    //void remove (int i);
    void traversalPreorder ();
    void traversalPostorder ();
    void traversalInorder ();
    virtual ~BinarySearchTree ();
protected:
    TreeNode* copy (TreeNode* src);
    virtual TreeNode* addNode (int i, TreeNode*& tn);
    bool findNode (int i, TreeNode* tn);
    void preorder (TreeNode* tn);
    void postorder (TreeNode* tn);
    void inorder (TreeNode* tn);
    void removeAll (TreeNode* tn);
};

}

#endif
