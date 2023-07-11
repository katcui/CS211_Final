/*graph.cpp*/

//
// Graph class implemented as ...
// 
// adjacency list and not an adjacency matrix.
// 
// For this implementation of graph, the vertices are 
// string, and the weights are doubles.  Example:
// 
//   graph  G;
//   G.addVertex("Chicago");
//   G.addVertex("New York");
//   G.addEdge("Chicago", "New York", -999.99);
//
// Kathy Cui
//
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include "graph.h"

using namespace std;

// findVertex
//
// finds the vertex from vertices
// if found, returns the index position, if not, returns -1
int graph::findVertex(string vertex) const
{
    auto curr = vertIndex.find(vertex);

    // vertex looked up
    if (curr != vertIndex.end()) // found
    {
        return curr->second; // second in pair is index
    }
    else // not found
    {
        return -1;
    }
} // findVertex

//
// default constructor: no parameters
//
graph::graph()
{
    this->numEdge = 0;
}

//
// NumVertices
//
// Returns the # of vertices currently in the graph.
//
int graph::NumVertices() const
{
    return static_cast<int>(this->vertices.size());
}

//
// NumEdges
//
// Returns the # of edges currently in the graph.
//
int graph::NumEdges() const
{
    return this->numEdge;
}

//
// addVertex
//
// Adds the vertex v to the graph and returns true. However,
// if v is already in the graph, it is not added again and 
// false is returned.
//
bool graph::addVertex(string vertex)
{
    // prevent duplicate vertices by finding first
    if(findVertex(vertex) > -1)
    {
        return false;
    }

    // insert new vertex
    int index = this->NumVertices();
    this->vertIndex[vertex] = index;
    this->vertices.push_back(vertex);

    map<int, double> addMap;

    this->edges.push_back(addMap);

    return true;
}// addVertex

//
// addEdge
//
// Adds the edge (from, to, weight) to the graph, and returns
// true. If the vertices do not exist then no edge is added
// and false is returned.
//
// NOTE: if the edge already exists, the existing edge weight
// is overwritten with the new edge weight.
//
bool graph::addEdge(string from, string to, double weight)
{
    // find the position of vertex for start to finish
    int start = findVertex(from);
    int end = findVertex(to);

    // the vertex is not found so we can't do anything with edge
    if (start == -1)
    {
        return false;
    }
    if (end == -1)
    {
        return false;
    }

    // if this is a new edge being added, increase numEdge
    if (this->edges[start].find(end) == this->edges[start].end())
    {
        this->numEdge++;
    }

    // update the edge
    this->edges[start][end] = weight;

    return true;
} // addEdge

//
// getWeight
//
// Returns the weight associated with a given edge.  If 
// the edge exists, the weight is returned via the reference
// parameter and true is returned. If the edge does not 
// exist, the weight parameter is unchanged and false is
// returned.
//
bool graph::getWeight(string from, string to, double& weight) const
{
    // find the position of vertex for start to finish
    int start = findVertex(from);
    int end = findVertex(to);

    // the vertex is not found so we can't do anything with edge
    if (start == -1)
    {
        return false;
    }
    if (end == -1)
    {
        return false;
    }

    // determine if edge exists
    auto curr = this->edges[start].find(end);

    // if edge does not exist, no weight
    if (curr == this->edges[start].end())
    {
        return false;
    }
    else  // edge exists
    {
        weight = curr->second;

        return true;
    }
} // getWeight

//
// neighbors
//
// Returns a set containing the neighbors of v, i.e. all
// vertices that can be reached from v along one edge. If
// v does not exist, an empty set is returned.
//
set<string> graph::neighbors(string v) const
{
    set<string>  set1;

    // find position of v for row in matrix
    int start = findVertex(v);

    // if vertex is not found
    if (start == -1)
    {
        return set1;
    }

    //
    // we found the src, so loop across the map of edges and
    // return each dest vertex:
    // loop through map of edges
    for (auto startEnd : this->edges[start])
    {
        int end = startEnd.first;

        // inserts end vertices
        set1.insert(this->vertices[end]);
    }

    return set1;
} // neighbors

//
// getVertices
//
// Returns a vector containing all the vertices currently in
// the graph. There is no guaranteed order to the vertices 
// in the returned vector; the order should be considered 
// random.
//
vector<string> graph::getVertices() const
{
    return this->vertices;
}

//
// print
// 
// Prints the internal state of the graph to the given 
// output stream for debugging purposes. The output will
// contain the # of vertices, the # of edges, the vertices,
// and the edges. Vertices are output as strings and the 
// weights as doubles.
//
// Example:
//    graph G;
//    ...
//    G.print(cout);  // print to console
//
void graph::print(ostream& output) const
{
    output << "Graph: ---------------------------------------------" << endl;
    output << endl;
    output << "# of vertices: " << this->NumVertices() << endl;
    output << "# of edges: " << this->NumEdges() << endl;
    output << endl;

    output << "Vertices: " << endl;

    // loops through vertices and outputs
    for (int i = 0; i < this->NumVertices(); i++)
    {
        output << " " << i+1 << ") " << this->vertices[i] << endl;
    }

    output << endl;

    output << "Edges:" << endl;
    // loops through vertices and outputs edges
    for (int i = 0; i < this->NumVertices(); i++)
    {
        output << " " << i+1 << ") ";
        for (auto se : this->edges[i]) // point notation for edge vertices
        {
            output << "(" << i << "," << se.first << "," << se.second << ") ";
        }
        output << endl;
    }
    output << endl;
} // print