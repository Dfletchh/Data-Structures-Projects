#include "adjlist.h"

//Adds a vertex to the graph with the given name
void AdjList::addVertex(const string& str)
{
  //If vertex exists, return early
  if (vertex.count(str) > 0)
    return;

  //Create new vertex with id = str
  //Add to vertex set
  //Create new incidence list
  vertex_t* temp = new vertex_t;
  temp->id = str;
  unordered_set<edge_t*>* templist = new unordered_set<edge_t*>();
  temp->I = templist;
  vertex.insert(make_pair(str, temp));
}

//Adds an edge to the graph
//Graph is undirected, so adds (v1, v2) and (v2, v1)
void AdjList::addEdge(const string& v1, const string& v2)
{
  if (vertex.count(v1) == 0 || vertex.count(v2) == 0)
    return;
  vertex_t* u = vertex[v1];
  vertex_t* v = vertex[v2];
  auto id = getEdgeID(u, v);

  //If edge already exists, return early
  if (edge.count(id) > 0)
    return;

  //Create edge (u, v)
  //Add to edge list
  //Update N(u) and N(v)
  edge_t* temp = new edge_t;
  temp->v1 = u;
  temp->v2 = v;
  edge.insert(make_pair(id, temp));
  u->I->insert(temp);
  v->I->insert(temp);
}

//Return whether v1 and v2 are adjacent
bool AdjList::isAdjacent(const string& v1, const string& v2) const
{
  if (vertex.count(v1) == 0 || vertex.count(v2) == 0)
    return false;
  
  const vertex_t* u = vertex.at(v1);
  const vertex_t* v = vertex.at(v2);

  //Return whether v is a neighbor of u
  for (edge_t* e : *u->I)
    if (e->v1 == v || e->v2 == v)
      return true;
  return false;
}

//Return the neighbors of a vertex
vector<string> AdjList::getNeighbors(const string& str) const
{
  vector<string> N;
  if (vertex.count(str) == 0)
    return N;

  const vertex_t* v = vertex.at(str);
  //Scan I[v] to get neighbors
  for (edge_t* e : *v->I)
    if (e->v1 == v)
      N.push_back(e->v2->id);
    else
      N.push_back(e->v1->id);

  return N;
}

//Removes an edge from the graph
void AdjList::removeEdge(const string& v1, const string& v2)
{
  if (vertex.count(v1) == 0 || vertex.count(v2) == 0)
    return;
  vertex_t* u = vertex.at(v1);
  vertex_t* v = vertex.at(v2);
  auto e = getEdgeID(u, v);

  if (edge.count(e) == 0)
    return;

  //Remove edge from incidence lists
  //Remove it from edge map
  //Free edge struct
  edge_t* temp = edge[e];
  edge.erase(e);
  u->I->erase(temp);
  v->I->erase(temp);
  delete temp;
}

//Removes a given vertex from the graph
void AdjList::removeVertex(const string& str)
{
  if (vertex.count(str) == 0)
    return;

  vertex_t* v = vertex[str];
  //While v has incident edges
  //Call removeEdge on first edge
  while (!v->I->empty())
  {
    edge_t* victim = *v->I->begin();
    removeEdge(victim->v1->id, victim->v2->id);
  }

  //Remove from vertex map
  //Free v->I and v
  vertex.erase(str);
  delete v->I;
  delete v;
}

//Validates that the data members of AdjList line up with each other
void AdjList::checkGraph() const
{
  //Check that sum of degrees = 2*m
  int count = 0;
  for (auto p : vertex)
    count += p.second->I->size();
  if (count != 2 * edge.size())
    cout << "m = " << edge.size() << ", but incidence lists only have " << count / 2 << " edges\n";

  //Check that incidence list edges incident on v
  for (auto p : vertex)
    for (edge_t* e : *p.second->I)
      if (e->v1 != p.second && e->v2 != p.second)
        cout << "Edge (" << e->v1->id << ", " << e->v2->id << ") appears in " << p.first << " incidence list\n";
  
  //Check that edges are their vertices' incidence lists
  for (auto p : edge)
  {
    if (p.second->v1->I->count(p.second) == 0)
      cout << "Edge (" << p.second->v1->id << ", " << p.second->v2->id << ") not in N(" << p.second->v1->id << ")\n";
    if (p.second->v2->I->count(p.second) == 0)
      cout << "Edge (" << p.second->v1->id << ", " << p.second->v2->id << ") not in N(" << p.second->v2->id << ")\n";
  }
}

//AdjList destructor
//Deallocates all vertices, edges, and incidence lists
AdjList::~AdjList()
{
  for (auto p : vertex)
  {
    delete p.second->I;
    delete p.second;
  }
  for (auto p : edge)
    delete p.second;
}

//Print the graph to an ostream
//Prints # vertices and # edges on first line
//Prints all vertices
//Prints all edges
ostream& operator<<(ostream& out, const AdjList& g)
{
  out << g.getOrder() << ' ' << g.getSize() << '\n';
  //Print vertices
  for (auto p : g.getVertices())
    out << p.first << '\n';

  //Print edges
  for (auto p : g.getVertices())
    for (edge_t* e : *p.second->I)
      if (e->v1 == p.second)
        out << e->v2->id << ' ' << e->v1->id << '\n';
      else
        out << e->v1->id << ' ' << e->v2->id << '\n';
  return out;
}
