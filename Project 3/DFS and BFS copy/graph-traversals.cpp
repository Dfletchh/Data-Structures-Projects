#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
using namespace std;

#include "adjlist.h"

enum mark_t
{
  UNDISCOVERED,
  DISCOVERED,
  EXPLORED
};

//Perform BFS on g, starting at start
//Only visits component containing start
//Prints vertices to cout, separated by commas
void printBFS(const AdjList &g, const string &start)
{
  //Mark all vertices undiscovered
  unordered_map<string, mark_t> marks;
  //for (auto it = g.getVertices().begin(); it != g.getVertices().end(); ++it)
  for (auto p : g.getVertices())
    marks.insert(make_pair(p.first, UNDISCOVERED));

  //Mark start vertex and enqueue
  queue<string> q;
  q.push(start);
  marks[start] = DISCOVERED;

  while (!q.empty())
  {
    string v = q.front();
    q.pop();
    marks[v] = EXPLORED;
    cout << v << ", ";

    //Enqueue undiscovered neighbors
    for (string s : g.getNeighbors(v))
    {
      if (marks[s] == UNDISCOVERED)
      {
        q.push(s);
        marks[s] = DISCOVERED;
      }
    }
  }
  cout << endl;
}

//Recursive DFS function
//Prints and marks this vertex then explores neighbors
//Called by printDFS (below)
void DFS(const AdjList &g, unordered_map<string, mark_t> &mark, const string &v)
{
  cout << v << ", ";
  mark[v] = DISCOVERED;

  //Recurse on undiscovered neighbors
  for (string s : g.getNeighbors(v))
    if (mark[s] == UNDISCOVERED)
      DFS(g, mark, s);

  mark[v] = EXPLORED;
}

//Performs DFS, starting at start
//Only visits component containing start
//Prints all vertices, separated by commas
void printDFS(const AdjList &g, const string &start)
{
  //Mark all vertices undiscovered
  unordered_map<string, mark_t> marks;
  for (auto p : g.getVertices())
    marks.insert(make_pair(p.first, UNDISCOVERED));

  DFS(g, marks, start);
  cout << endl;
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
  //cout << "BFS:\n";
  //printBFS(g, str);

  //Perform DFS starting at Atlanta
  cout << "\nDFS:\n";
  printDFS(g, str);

  return 0;
}