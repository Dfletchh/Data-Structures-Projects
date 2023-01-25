#ifndef __BST_H
#define __BST_H

#include <iostream>
using namespace std;

class BST;
class BSTNode;
class AVLTree;

class BSTNode
{
  friend BST;
  friend AVLTree;
  friend ostream& operator<<(ostream&, const BSTNode*);
protected:
  int data;
  BSTNode* left;
  BSTNode* right;
  BSTNode* parent;
public:
  BSTNode (int x) { data = x; left = right = parent = nullptr; }
  virtual void insert(int x);
  virtual BSTNode* remove();
  BSTNode* search(int x);
  BSTNode* findMin();
  BSTNode* findMax();
  bool isLeftChild() const;
  bool isRightChild() const;
  void printPreorder() const;
  void printInorder() const;
  void printPostorder() const;
  virtual ~BSTNode();
};

class BST
{
friend ostream& operator<<(ostream&, const BST&);
protected:
  BSTNode* root;
  int size;
public:
  BST() { root = nullptr; size = 0; }
  int getSize() const { return size; }
  virtual void insert(int x);
  virtual void remove(int x);
  bool contains(int x) const;
  void printPreorder() const;
  void printInorder() const;
  void printPostorder() const;
  void printLevelorder() const;
  virtual ~BST();
};

ostream& operator<<(ostream&, const BST&);
ostream& operator<<(ostream&, const BSTNode*);

#endif //__BST_H