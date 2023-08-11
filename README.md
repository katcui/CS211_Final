# Validate Graphs

## Description
The program here was written for the purpose of honing good testing practices. There are 2 parts to the program:
1. A graph class
2. Unit testing
## Part 1: Graph Class
A `Graph` class is implemented in this program and is defined in `graph.h`. The graph is WUGraph (weighted nd undirected) which has string-based vertices and double-type edge weights. `graph.cpp` details the implementation of the Graph class with methods: name, return type, parameters, const, and behavior. Data members are private.

The graph is implemented as an *adjacency list* and has a space requirement of at most O(V+E), as well as supports all possible wieghts and cyclic edges. The class includes a print method (which outputs vertex and edge information), getter methods for vertices, edges, and weights, and methods of adding vertices and edges. 

## Part 2: Unit Testing
The program includes multiple non-trivial unit tests that test the public methods of the Graph class using **googletest**. The googletest files are contained in the folder `gtest`. `gtest.o` is the googletest library that implements the googletest framework, and `makefiel` comiles `main.cpp` with `gtest.o`. 

Each test creates a different graph with atleast 8 vertices and 12 edges by calling the add methods `addVertex()` and `addEdge()`. Below are some aspects tested by the unit tests:
1. `addVertex(v)` returns `False` is the vertex v is already in the graph.
2. `addEdge(x, y, w)` returns `False` is x or y (the vertices) do not exist.
3. `addEdge(x, y, w)` updates the existing weight is the edge already exists.
4. `getWeight(x, y, w)` returns `False` is a vertex does not exist, or the edge does not exist.

\* w stands for the weight of an edge

The testing includes simple tests that build a basic graph, tests on empty graphs, and **stress tests** large graphs with millions of vertices and edges. The stress tests are expected to build the large graphs in a few seconds. 
***
It is important to always maintain good testing practices. 
