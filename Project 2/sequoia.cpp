/*
 * Author: Dean Fletcher
 * 
 * Purpose: In this project, you will develop code for a binary search tree variant called a 
 *          Sequoia. Specifically, you will mplement member functions for Sequoia and 
 *          SequoiaNode class. Just like a BST, Sequoia is the main class and represents
 *          the tree as a whole, while SequoiaNode represents a single node in the tree.
 * 
 *          Just like their real world counterparts, Sequoias are very tall trees. Specifically, every
 *          node in a Sequoia must be a tall node, where a tall node satisfies one of the following:
 *              1) The left subtree has at least double the height of the right subtree
 *              2) The right subtree has at least double the height of the left subtree
*/
#include "sequoia.h"

// Modified remove func from Canvas AVL tree // 
void Sequoia::insert(int x) {
    if (root != nullptr)
      root->insert(x);
    else
      root = new SequoiaNode(x);
    size++;
    updateRoot();
    updateHeight();
}
void SequoiaNode::insert(int x) {
    if (x < value)  {
        if (left != nullptr)    // Traverse left
            left->insert(x);
        else {
            left = new SequoiaNode(x);
            left->parent = this;
        }
    } else {
        if (right != nullptr)   // Traverse right
            right->insert(x);
        else {
            right = new SequoiaNode(x);
            right->parent = this;
        }
    }
    updateHeight();
}

// Modified remove func from Canvas AVL tree // 
void Sequoia::remove(int x) {
    if (root == nullptr)
      return;               // Empty Sequoia
    
    SequoiaNode* victim = root->search(x);
    if (victim == nullptr)
      return;               // Doesn't contain x
    
    if (victim == root)     // Update root if deleting
      root = victim->remove(); 
    else
      victim->remove();

    updateRoot();
    updateHeight();
}
SequoiaNode* SequoiaNode::remove() {
    int numChildren = (left != nullptr) + (right != nullptr);

    // Separate cases based on # of children //
    if (numChildren == 0) {
        if (isLeftChild())
            parent->left = nullptr;
        else if (isRightChild())
            parent->right = nullptr;
        // doesn't dereference parent if root

        parent->updateHeight();
        delete this;          
        return nullptr;           // this tree has no root
    } else if (numChildren == 1) {
        SequoiaNode* child;
        if (left != nullptr)
            child = left;
        else
            child = right;
        
        child->parent = parent;   // Point child to parent

        if (isLeftChild())        // Point parent to child
            parent->left = child;
        else if (isRightChild())
            parent->right = child;
        
        left = right = nullptr;   // Important so we don't delete child
        delete this;    
        child->updateHeight();       
        return child;             // child is now root
    } else {                      // else 2 children
        SequoiaNode* swap = left->findMax();
        value = swap->value;
        swap->remove();           // recursively delete other node
        this->updateHeight();           
        return this;              // still the root of the subtree
    }
}
// Rotates appropriate child to fix the balance //
void Sequoia::fixBalance(int rht, int lht) {
    if (rht != 0 || lht != 0) {
        if (lht < rht) {                        // right tree tall
            root->left->rotateRight();          // rotate left child to the right
        } else {                                // left tree tall
            root->right->rotateLeft();          // rotate right child to the left
        }
        root->parent->height = root->height+1;  // fix height of rotated child
    }
    return;
}
void SequoiaNode::fixBalance(int rht, int lht) {
    if (rht != 0 || lht != 0) {
        if (lht < rht) {            // right tree tall
            left->rotateRight();    // rotate left child to the right
        } else {                    // left tree tall
            right->rotateLeft();    // rotate right child to the left
        }
        parent->height = height+1;  // fix height of rotated child
    }
    return;
}

// Scales the sequoia and checks if need to fix balance //
void Sequoia::updateHeight() {
    int lht=0, rht=0;             // get heights
    if (root->left != nullptr)
        lht = root->left->height;
    if (root->right != nullptr)
        rht = root->right->height;

    // Examine the height of children to recalculate height //
    if (rht > lht) {              // Right is taller
        root->height = (rht + 1);
    }
    else if (lht > rht) {         // Left is taller
        root->height = (lht + 1);
    }
    if (!(lht >= 2*rht || rht >= 2*lht)) {
        fixBalance(rht, lht);
    }
    return;
}
void SequoiaNode::updateHeight() {
    int lht=0, rht=0;           // get heights
    if (left != nullptr)
        lht = left->height;
    if (right != nullptr)
        rht = right->height;

    // Examine the height of children to recalculate height //
    if (rht > lht) {            // Right is taller
        height = (rht + 1);
    }
    else if (lht > rht) {       // Left is taller
        height = (lht + 1);
    }
    else if (rht == lht && rht != 0) {  // Corrects height if node deleted
      height = rht+1;
    }
    else if (rht == 0 && lht == 0 && height != 1) { // Corrects height if node deleted
      height = 1; 
      parent->updateHeight();
    }
    if (!(lht >= 2*rht || rht >= 2*lht)) {            // Is tree tall
        fixBalance(rht, lht);
    }
    if (parent != nullptr)      // Move on up
        parent->updateHeight();

    return;
}

// Updates root if it is rotated //
void Sequoia::updateRoot() {   
   while (root->parent != nullptr)
     root = root->parent; }
// Utility funcs from Canvas for working with AVL trees //
SequoiaNode* SequoiaNode::search(int x) {
    if (x == value)       // base case returns a matching value w/ recursion
        return this;
    else if (x < value) {
        if (left != nullptr) {
            return left->search(x);
        } else
            return nullptr;
    } else  {
        if (right != nullptr) {
            return right->search(x);
        } else
            return nullptr;
    }
}
bool SequoiaNode::isLeftChild() const {
    return parent != nullptr && parent->left == this;
}
bool SequoiaNode::isRightChild() const {
    return parent != nullptr && parent->right == this;
}
SequoiaNode* SequoiaNode::findMax() {
    if (right == nullptr)
      return this;
    else
      return right->findMax();
}
void SequoiaNode::rotateLeft() {
    parent->right = left;     // parent->right = pivot->left
    
    if (left != nullptr) {    // left->parent = pivot->parent
      left->parent = parent;
    }
    left = parent;            // pivot->left = pivot->parent
    
    parent = parent->parent;  // pivot->parent = pivot->grandparent
    
    if (left->isLeftChild()) {// grandparent->child = pivot
      parent->left = this;
    }
    else if (left->isRightChild()) {
      parent->right = this;
    }
    left->parent = this;      // grandparent->child = pivot
}
void SequoiaNode::rotateRight() {
    parent->left = right;
    if (right != nullptr) {
      right->parent = parent;
    }
    right = parent;
    parent = parent->parent;

    if (right->isLeftChild()) {
      parent->left = this;
    }
    else if (right->isRightChild()) {
      parent->right = this;
    }
    right->parent = this;
}