#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

enum mark_t
{
  UNDISCOVERED,
  DISCOVERED,
  EXPLORED
};

class DigraphMatrix
{
private:
  int vertices;
  int **adjMatrix;
  bool cycle = false;

public:
  DigraphMatrix(const string &filename);
  vector<int> topologicalSort();
  void addEdge(const int, const int);
  void DFS(stack<int> &, unordered_map<int, mark_t> &, const int &);
  void initDiscovery(unordered_map<int, mark_t> &);
  void initMatrix();
};
#endif