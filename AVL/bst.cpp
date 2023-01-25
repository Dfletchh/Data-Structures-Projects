#include "bst.h"

#include <queue>
using namespace std;

//Recursive insertion function
//Inserts a BSTNode with x below this node
void BSTNode::insert(int x)
{
  if (x < data)
  {
    if (left != nullptr)
      left->insert(x);
    else
    {
      left = new BSTNode(x);
      left->parent = this;
    }
  }
  else
  {
    if (right != nullptr)
      right->insert(x);
    else
    {
      right = new BSTNode(x);
      right->parent = this;
    }
  }
}

//Insert an element into the BST
//Works recursively unless BST is empty
void BST::insert(int x)
{
  if (root != nullptr)
    root->insert(x);
  else
    root = new BSTNode(x);
  
  size++;
}

//Recursive search function
//Returns pointer to node with value x in this subtree
//Returns nullptr if not found
BSTNode* BSTNode::search(int x)
{
  if (x == data)
    return this;
  else if (x < data)
  {
    if (left != nullptr)
      return left->search(x);
    else
      return nullptr;
  }
  else
  {
    if (right != nullptr)
      return right->search(x);
    else
      return nullptr;
  }
}

//Returns whether the BST contains a given value
//Recursive unless BST is empty
bool BST::contains(int x) const
{
  if (root == nullptr || root->search(x) == nullptr)
    return false;
  else
    return true;
}

//Recursive function to print this subtree preorder
//Preorder:  self left right
void BSTNode::printPreorder() const
{
  cout << data << ' ';
  if (left != nullptr)
    left->printPreorder();
  if (right != nullptr)
    right->printPreorder();
}

//Function to print all nodes in preorder
void BST::printPreorder() const
{
  if (root != nullptr)
    root->printPreorder();
}

//Recursive function to print this subtree inorder
//Inorder:  left self right
void BSTNode::printInorder() const
{
  if (left != nullptr)
    left->printInorder();
  cout << data << ' ';
  if (right != nullptr)
    right->printInorder();
}

//Function to print all nodes in sorted order
void BST::printInorder() const
{
  if (root != nullptr)
    root->printInorder();
}

//Recursive function to print this subtree postorder
//Postorder:  left right self
void BSTNode::printPostorder() const
{
  if (left != nullptr)
    left->printPostorder();
  if (right != nullptr)
    right->printPostorder();
  cout << data << ' ';
}

//Function to print all nodes in postorder
void BST::printPostorder() const
{
  if (root != nullptr)
    root->printPostorder();  
}

//Iterative function to print BST nodes levelwise
void BST::printLevelorder() const
{

}

//BSTNode destructor
//Recursively frees all nodes in this subtree
BSTNode::~BSTNode()
{

}


//BST destructor
//Frees all BST nodes
BST::~BST()
{

}

//Function to remove this node from the BST
//Returns the root of this subtree after deletion
BSTNode* BSTNode::remove()
{
  int numChildren = (left != nullptr) + (right != nullptr);
  //Separate cases based on # of children
}

//Function to remove a value from the BST
void BST::remove(int x)
{

}

//Recursive function to find the min node below this one
BSTNode* BSTNode::findMin()
{
  if (left == nullptr)
    return this;
  else
    return left->findMin();
}

//Recursive function to find the max node below this one
BSTNode* BSTNode::findMax()
{
  if (right == nullptr)
    return this;
  else
    return right->findMax();
}

//Returns whether this node is a left child
//Returns false for root
bool BSTNode::isLeftChild() const
{
  return parent != nullptr && parent->left == this;
}

//Returns whether this node is a right child
//Returns false for root
bool BSTNode::isRightChild() const
{
  return parent != nullptr && parent->right == this;
}

//Recursive BST printing function
//Prints as a set of nested parentheses
ostream& operator<<(ostream& out, const BST& b)
{
  if (b.root != nullptr)
    return out << b.root;
  else
    return out << "empty";  
}

//Recursive BSTNode printing function
ostream& operator<<(ostream& out, const BSTNode* n)
{
  if (n == nullptr)
    return out;
  else
    return out << "(data=" << n->data << ", left=" << n->left << ", right=" << n->right << ')'; 
}
