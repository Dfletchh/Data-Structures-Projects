#include <iostream>
using namespace std;

#include "bst.h"

int main()
{
  BST bst;

  //Test insert
  cout << bst << endl;
  bst.insert(50);
  cout << bst << endl;
  bst.insert(75);
  cout << bst << endl;
  bst.insert(25);
  cout << bst << endl;
  bst.insert(38);
  cout << bst << endl;
  bst.insert(31);
  cout << bst << endl;
  bst.insert(13);
  cout << bst << endl;

  //* Test contains
  cout << "bst does " << (bst.contains(50)? "":"not ") << "contain 50" << endl;
  cout << "bst does " << (bst.contains(31)? "":"not ") << "contain 31" << endl;
  cout << "bst does " << (bst.contains(100)? "":"not ") << "contain 100" << endl;
  cout << "bst does " << (bst.contains(30)? "":"not ") << "contain 30" << endl;

  //* Test traversals
  bst.printPreorder();
  cout << endl;
  bst.printInorder();
  cout << endl;
  bst.printPostorder();
  cout << endl;
  //bst.printLevelorder();
  //cout << endl;

  /* Test removal
  bst.remove(38); //1 child (left)
  cout << bst << endl;
  bst.remove(25); //2 children
  cout << bst << endl;
  bst.remove(75); //leaf
  cout << bst << endl;
  bst.remove(13); //1 child (right)
  cout << bst << endl;
  bst.remove(50); //root, 1 child (left)
  cout << bst << endl;
  bst.remove(31); //root, leaf
  cout << bst << endl;
  //*/

  return 0;
}