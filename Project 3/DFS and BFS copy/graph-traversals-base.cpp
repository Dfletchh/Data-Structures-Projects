#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
using namespace std;

#include "adjlist.h"

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

//Perform BFS on g, starting at start
//Only visits component containing start
//Prints vertices to cout, separated by commas
void printBFS(const AdjList& g, const string& start)
{

}

//Recursive DFS function
//Prints and marks this vertex then explores neighbors
//Called by printDFS (below)
void DFS(const AdjList& g, unordered_map<string, mark_t>& mark, const string& v)
{

}

//Performs DFS, starting at start
//Only visits component containing start
//Prints all vertices, separated by commas
void printDFS(const AdjList& g, const string& start)
{

}

int main()
{
  AdjList g;
  int n, m;
  string str, str1, str2;
  vector<string> N;

  //Read in graph from pandemic.txt
  ifstream in("pandemic.txt");
  if (!in.is_open())
  {
    cout << "Couldn't open pandemic.txt\n";
    return -1;
  }
  //Read n and m
  in >> n >> m;
  in.ignore(); //Ignore \n
  //Read in n vertices
  for (int i = 0; i < n; i++)
  {
    getline(in, str);
    g.addVertex(str);
  }
  //Read m edges
  for (int i = 0; i < m; i++)
  {
    getline(in, str);
    istringstream iss(str);
    getline(iss, str1, ',');
    iss.ignore(); //Ignore ' '
    getline(iss, str2, ',');
    g.addEdge(str1, str2);
  }

  //Perform BFS starting at Atlanta
  str = "Atlanta";
  cout << "BFS:\n";
  printBFS(g, str);

  //Perform DFS starting at Atlanta
  //cout << "\nDFS:\n";
  //printDFS(g, str);

  return 0;
}