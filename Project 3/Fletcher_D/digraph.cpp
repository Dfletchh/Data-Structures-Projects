/*
 * Author: Dean Fletcher
 * 
 * Purpose: In this project, you will implement topological sorting in a
 *          directed acyclic graph. In addition, your implementation will:
 *              * Represent the graph as an adjacency matrix 
 *              * Always choose the vertex with the lowest ID when given a 
 *                choice (e.g., when iterating through the neighbors of a
 *                vertex and when selecting a vertex to start)
 *              * Throw an exception if it encounters a cycle
 * 
*/

#include "digraph.h"
#include <fstream>
#include <iostream>
#include <exception>

DigraphMatrix::DigraphMatrix(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Error opening " << filename << endl;
        return;
    }
    //Read n vertices and m edges
    int n, m;
    in >> n >> m;
    vertices = n;

    initMatrix();

    //Add directed edges
    for (int i = 0; i < m; i++)
    {
        int v1, v2;
        in >> v1 >> v2;
        addEdge(v1, v2);
    }
    in.close();
}

void DigraphMatrix::addEdge(const int start, const int end)
{
    adjMatrix[start][end] = 1;
}

vector<int> DigraphMatrix::topologicalSort()
{
    vector<int> result;
    stack<int> stack;
    unordered_map<int, mark_t> marks;

    initDiscovery(marks);

    for (int i = 0; i < vertices; i++) // Search nodes via DFS
    {
        if (marks[i] == UNDISCOVERED)
        {
            DFS(stack, marks, i); // recursively visits all nodes neighbors
            if (cycle)
                throw std::invalid_argument("Cycle");
        }
    }

    while (stack.empty() == false) // Empty stack into result
    {
        result.push_back(stack.top());
        stack.pop();
    }
    return result;
}

void DigraphMatrix::DFS(stack<int> &stack, unordered_map<int, mark_t> &mark, const int &cur)
{
    if (mark[cur] == EXPLORED) // base case
        return;

    if (mark[cur] == DISCOVERED) // cycle has occured
    {
        cycle = true;
        return;
    }
    mark[cur] = DISCOVERED;

    //Recurse on undiscovered neighbors
    for (int i = 0; i < vertices; i++)
    {
        if (adjMatrix[cur][i] == 1)
            DFS(stack, mark, i);
    }
    mark[cur] = EXPLORED;
    stack.push(cur);
}

// Util helper functions //
void DigraphMatrix::initDiscovery(unordered_map<int, mark_t> &marks)
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (adjMatrix[i][j] == 1)
                marks.insert(make_pair(i, UNDISCOVERED));
        }
    }
}
void DigraphMatrix::initMatrix()
{
    adjMatrix = new int *[vertices]; //Number rows
    for (int i = 0; i < vertices; i++)
        adjMatrix[i] = new int[vertices]; //Number columns
}