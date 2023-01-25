#ifndef __ADJLIST_H
#define __ADJLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
using namespace std;

struct edge;

typedef struct vertex
{
  string id;
  unordered_set<struct edge*>* I;
} vertex_t;

typedef struct edge
{
  vertex_t* v1;
  vertex_t* v2;
} edge_t;

class AdjList
{
  friend ostream& operator<<(ostream&, const AdjList&);
private:
  unordered_map<string, vertex_t*> vertex;
  unordered_map<string, edge_t*> edge;
  string getEdgeID(const vertex_t* u, const vertex_t* v) const
    { return u->id < v->id? u->id + v->id : v->id + u->id; }
public:
  AdjList() {}
  ~AdjList();
  //Note:  should have copy constructors and assignment
  void addVertex(const string&);
  void removeVertex(const string&);
  void addEdge(const string&, const string&);
  void removeEdge(const string&, const string&);
  bool isAdjacent(const string&, const string&) const;
  vector<string> getNeighbors(const string&) const;
  void checkGraph() const;

  int getOrder() const { return vertex.size(); }
  int getSize() const { return edge.size(); }
  const unordered_map<string, vertex_t*>& getVertices() const { return vertex; }
  bool hasVertex(const string& name) { return vertex.count(name) > 0; }
};

ostream& operator<<(ostream&, const AdjList&);

#endif