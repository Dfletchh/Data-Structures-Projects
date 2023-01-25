#include "avl.h"

int main()
{
  AVLTree avl;

  //Build initial AVL tree
  avl.insert(50);
  avl.insert(25);
  avl.insert(75);
  avl.insert(13);
  avl.insert(38);
  avl.insert(88);
  avl.insert(31);
  cout << "Initial AVL tree:\n" << avl << endl;
  cout << "Pre-order:  ";
  avl.printPreorder();
  cout << endl << "Levelwise:  ";
  avl.printLevelorder();
  cout << endl;

  // Test left rotation
  avl.search(88)->rotateLeft();
  cout << "After rotating 88 left:\n" << avl << endl;
  
  //* Test right rotation
  avl.search(75)->rotateRight();
  cout << "After rotating 88 back:\n" << avl << endl;

  //More rotation tests
  avl.search(38)->rotateLeft();
  cout << "After rotating 38 left:\n" << avl << endl;
  avl.search(25)->rotateRight();
  cout << "After rotating 38 back:\n" << avl << endl;

  auto temp = avl.search(25);
  avl.search(25)->rotateRight();
  cout << "After rotating 25 right:\n" << temp << endl;
  avl.search(50)->rotateLeft();
  cout << "After rotating 25 back:\n" << avl << endl;
  
  //* Test insert and rebalancing
  AVLTree squares;
  for (int i = 1; i <= 15; i++)
  {
    squares.insert(i*i);
    squares.checkHeight();
    cout << "Adding " << i*i << ":  " << squares << endl;
  }
  //*/

  return 0;
}