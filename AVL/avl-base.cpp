#include "avl.h"

#include <queue>
using namespace std;

/*Rotate this node (*) left
    G             G
    |             |
    P             *
   / \           / \
  X   *  ===>   P   Z
     / \       / \  
    Y   Z     X   Y
//*/
void AVLNode::rotateLeft()
{
  ((AVLNode *) parent)->right = left;

  if(left != nullptr)
  {
    ((AVLNode*) left)->parent = parent;
  }

  left = parent;
  parent = ((AVLNode * ) parent)->parent;

  if(left->isLeftChild())
    ((AVLNode*) parent)->left = this;
  else if (left->isRightChild())
    ((AVLNode*)parent)->right = this;

  ((AVLNode *) left)->parent = this;
}

/*Rotate this node (*) right
    G           G
    |           |
    P           *
   / \         / \
  *   Z  ===> X   P
 / \             / \ 
X   Y           Y   Z
//*/
void AVLNode::rotateRight()
{
}

//Add x to the AVL tree rooted here
//If adding as child:
// Adjust balance
// If balance != 0 and parent != null, fix parent balance
void AVLTree::insert(int x)
{
  if (size == 0)
    root = new AVLNode(x);
  else
    root->insert(x);
  size++;
  if(root->parent != nullptr)
    root = root->parent;
}

//Recursive insertion function
//Inserts an AVLNode with x below this node
void AVLNode::insert(int x)
{
  if (x < data)
  {
    if (left != nullptr)
      left->insert(x);
    else
    {
      left = new AVLNode(x);
      ((AVLNode*)left)->parent = this;
      this->fixBalanceInsert((AVLNode *) left, nullptr);
    }
  }
  else
  {
    if (right != nullptr)
      right->insert(x);
    else
    {
      right = new AVLNode(x);
      ((AVLNode*)right)->parent = this;
      this->fixBalanceInsert((AVLNode *) right, nullptr);
    }
  }
}

//Fix the balance of this node after inserting (from prev)
//Adjust balance left or right
// Left-left:  rotate prev right, this & prev balance = 0
// Right-right:  rotate prev left, this & prev balance = 0
// Left-right:  rotate child left, then right
//   this & child balance = 0, prev = -1
// Right-left:  rotate child right, then left
//   this & child balance = 0, prev = 1
//If balance != 0 and parent not null, fix parent
void AVLNode::fixBalanceInsert(AVLNode* child, AVLNode* grandchild)
{
  if(child == this->left)
  {
    balance--;
  }
  else{
    balance++;
  }

  if(balance == 0)
  {
    return;
  }
  else if(balance == 1 || balance == -1)
  {
    if(parent != nullptr)
    {
      ((AVLNode *) parent)->fixBalanceInsert(this, child);
    }
  }
  else if(balance == 2 || balance == -2)
  {
    if(left == child && child->left == grandchild)
    {
      child->rotateRight();
      balance = child->balance = 0;
    }
    else if(right == child && child->right == grandchild)
    { 
      child->rotateLeft();
      balance = child->balance = 0;
    }
    else if(child == left && child->right == grandchild)
    {
      grandchild->rotateLeft();
      grandchild->rotateRight();
      balance = child->balance = grandchild->balance = 0;
    }
    else //right == child && child->left == grandchild
    {
      grandchild->rotateRight();
      grandchild->rotateLeft();
      balance = child->balance = grandchild->balance = 0;
    }
  }
}

//Fix the balance of this node after removing (from prev)
void AVLNode::fixBalanceRemove(AVLNode* prev)
{

}


//Function to remove a value from the AVLTree
void AVLTree::remove(int x)
{
  if (root == nullptr)
    return; //empty AVLTree
  
  AVLNode* victim = ((AVLNode*)left)->search(x);
  if (victim == nullptr)
    return; //doesn't contain x
  
  if (victim == root) //update root if deleting
    root = victim->remove(); 
  else
    victim->remove();
}

//Function to remove this node from its AVLTree
AVLNode* AVLNode::remove()
{
  int numChildren = (left != nullptr) + (right != nullptr);
  if (numChildren == 0)
  {
    if (isLeftChild())
      ((AVLNode*)parent)->left = nullptr;
    else if (isRightChild())
      ((AVLNode*)parent)->right = nullptr;
    //don't dereference parent if root

    delete this;
    return nullptr; //root = nullptr if deleting root
  }
  else if (numChildren == 1)
  {
    AVLNode* child;
    if (left != nullptr)
      child = (AVLNode*) left;
    else
      child = (AVLNode*) right;
    
    //Point child to parent
    child->parent = parent;

    //Point parent to child
    if (isLeftChild())
      ((AVLNode*)parent)->left = child;
    else if (isRightChild())
      ((AVLNode*)parent)->right = child;
    
    left = right = nullptr; //important so we don't delete child
    delete this;
    return child; //root = child if deleting root
  }
  else //2 children
  {
    AVLNode* swap = (AVLNode*) left->findMax();
    data = swap->data;
    swap->remove(); //recursively delete other node
    return this; //root pointer doesn't move
  }
}

//Calculate the height of this node
//Also, check that balance = height(right) - height(left)
int AVLNode::height() const
{
  int lht = 0, rht = 0;
  if (left != nullptr)
    lht = ((AVLNode*)left)->height();
  if (right != nullptr)
    rht = ((AVLNode*)right)->height();
  if (balance != rht - lht)
    cout << "Node " << data << ":  " << balance << " != " << rht << " - " << lht << '\n';
  if (lht > rht)
    return 1 + lht;
  else
    return 1 + rht;
}

//Validate balance in every node of the tree
void AVLTree::checkHeight() const
{
  if (root != nullptr)
    ((AVLNode*)root)->height();
}

AVLNode* AVLNode::search(int x)
{
  return (AVLNode*) BSTNode::search(x);
}

ostream& operator<<(ostream& out, const AVLTree& t)
{
  return out << (const AVLNode*) t.root;
}

ostream& operator<<(ostream& out, const AVLNode* n)
{
  out << '(';
  if (n != nullptr)
    out << n->data << ":" << (n->balance == 0? "0" : n->balance < 0? "-" : "+") << " L=" << (const AVLNode*) n->left << " R=" << (const AVLNode*) n->right;
  return out << ')';
}