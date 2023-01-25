#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "adjlist.h"

void printNeighbors(const AdjList& g, const char* city)
{
  string str(city);
  vector<string> N = g.getNeighbors(str);
  for (string s : N)
    cout << s << ", ";
  cout << '\n';
}

int main()
{
  AdjList g;
  int n, m;
  string str, str1, str2;

  //Read in graph from pandemic.txt
  cout << "Reading in graph..." << endl;
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
  cout << g.getOrder() << " vertices read\n";
  //for (auto p : g.getVertices())
  //  cout << p.second->id << " (deg " << p.second->I->size() << ")\n";
  g.checkGraph();

  /* Read m edges
  for (int i = 0; i < m; i++)
  {
    getline(in, str);
    istringstream iss(str);
    getline(iss, str1, ',');
    iss.ignore(); //Ignore ' '
    getline(iss, str2, ',');
    g.addEdge(str1, str2);
  }
  cout << "Graph has " << g.getOrder() << " vertices and " << g.getSize() << " edges\n";
  //for (auto p : g.getVertices())
  //  cout << p.second->id << " (deg " << p.second->I->size() << ")\n";
  g.checkGraph();

  /* Test isAdjacent
  str1 = "Miami"; str2 = "Atlanta";
  cout << "Miami is " << (g.isAdjacent(str1, str2)? "adjacent" : "not adjacent") << " to Atlanta\n";
  str1 = "Miami"; str2 = "St. Petersburg";
  cout << "Miami is " << (g.isAdjacent(str1, str2)? "adjacent" : "not adjacent") << " to St. Petersburg\n";

  /* Test getNeighbors
  cout << "Neighbors of Miami:  ";
  printNeighbors(g, "Miami");
  cout << "Neighbors of New York:  ";
  printNeighbors(g, "New York");
  cout << "Neighbors of Madrid:  ";
  printNeighbors(g, "Madrid");

  /* Test removeEdge
  cout << "Removing (Miami, Bogota)\n";
  str1 = "Miami";
  str2 = "Bogota";
  g.removeEdge(str1, str2);
  cout << "Neighbors of Miami:  ";
  printNeighbors(g, "Miami");
  g.checkGraph();

  /* Test removeVertex
  cout << "Removing New York\n";
  str = "New York";
  g.removeVertex(str);
  cout << "Graph has " << g.getOrder() << " vertices and " << g.getSize() << " edges\n";
  cout << "Neighbors of Madrid:  ";
  printNeighbors(g, "Madrid");
  g.checkGraph();
  //*/

  return 0;
}
