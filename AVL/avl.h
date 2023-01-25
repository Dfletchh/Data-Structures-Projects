#ifndef __AVL_H
#define __AVL_H

#include "bst.h"

class AVLNode : public BSTNode
{
  friend ostream& operator<<(ostream& out, const AVLNode* n);
private:
  int balance;
public:
  AVLNode(int x) : BSTNode(x) { balance = 0; }
  void rotateLeft();
  void rotateRight();
  AVLNode* search(int x);
  void insert(int x);
  AVLNode* remove();
  void fixBalanceInsert(AVLNode*, AVLNode*);
  void fixBalanceRemove(AVLNode*);
  int height() const;
  ~AVLNode() {}
};

class AVLTree : public BST
{
  friend ostream& operator<<(ostream&, const AVLTree&);
public:
  AVLTree() {}
  AVLNode* getRoot() { return (AVLNode*) root; }
  const AVLNode* getRoot() const { return (const AVLNode*) root; }
  AVLNode* search(int x) { return ((AVLNode*) root)->search(x); }
  void checkHeight() const;
  virtual void insert(int x) override;
  virtual void remove(int x) override;
};

ostream& operator<<(ostream&, const AVLTree&);
ostream& operator<<(ostream&, const AVLNode*);

#endif