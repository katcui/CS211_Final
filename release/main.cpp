#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

#include "gtest/gtest.h"
#include "graph.h"

using namespace std;

//
// overall_test
//
// tests success of NumVertices, NumEdges, addVertex, addEdge
// includes false test for invalid vertices and edges
// test getWeight, and rewriting weight
// test success in creating copy using copy constructor
//
TEST(graph, overall_test)
{
    graph g;

    ASSERT_TRUE(g.NumVertices() == 0);
    ASSERT_TRUE(g.NumEdges() == 0);

    ASSERT_TRUE(g.addVertex("111") == true);
    ASSERT_TRUE(g.addVertex("222") == true);

    ASSERT_TRUE(g.NumVertices() == 2);
    ASSERT_TRUE(g.NumEdges() == 0);

    ASSERT_TRUE(g.addEdge("111", "222", 111.0) == true);
    ASSERT_TRUE(g.addEdge("222", "111", 222.0) == true);

    ASSERT_TRUE(g.NumVertices() == 2);
    ASSERT_TRUE(g.NumEdges() == 2);

    ASSERT_TRUE(g.addVertex("333"));
    ASSERT_TRUE(g.addEdge("222", "333", 333.0) == true);

    ASSERT_TRUE(g.NumVertices() == 3);
    ASSERT_TRUE(g.NumEdges() == 3);

    // 1. addVertex(v) returns false is v is already in the graph
    ASSERT_TRUE(g.addVertex("333") == false);

    // 2. addEdge(x, y, w) returns false if x or y do not exist
    ASSERT_TRUE(g.addEdge("112", "222", 123.0) == false);
    ASSERT_TRUE(g.addEdge("111", "223", 456.0) == false);
    ASSERT_TRUE(g.addEdge("112", "223", 456.0) == false);

    // 3. addEdge(x, y, w) updates the existing weight if the edge already exists.
    double weight = 0.0;
    ASSERT_TRUE(g.getWeight("111", "222", weight) == true);
    ASSERT_TRUE(weight == 111.0);
    ASSERT_TRUE(g.addEdge("111", "222", 123.0) == true);
    ASSERT_TRUE(g.getWeight("111", "222", weight) == true);
    ASSERT_TRUE(weight == 123.0);

    // 4. getWeight(x, y, w) returns false if a vertex does not exist, or the edge does not exist
    ASSERT_TRUE(g.getWeight("112", "222", weight) == false);
    ASSERT_TRUE(g.getWeight("111", "223", weight) == false);
    ASSERT_TRUE(g.getWeight("112", "223", weight) == false);
    ASSERT_TRUE(g.getWeight("111", "333", weight) == false); // nonexisting edge, existing vertices

    for(int v = 444; v <= 888; v = v + 111)
    {
        ASSERT_TRUE(g.addVertex(to_string(v)) == true);
    }
    ASSERT_TRUE(g.NumVertices() == 8);
    ASSERT_TRUE(g.NumEdges() == 3);

    for(int i = 111; i < 888; i = i + 111)
    {
        ASSERT_TRUE(g.addEdge(to_string(i), to_string(i + 111), double(i)));
    }
    ASSERT_TRUE(g.NumVertices() == 8);
    ASSERT_TRUE(g.NumEdges() == 8);
    ASSERT_TRUE(g.getWeight("111", "222", weight) == true);
    ASSERT_TRUE(weight == 111.0);
    ASSERT_TRUE(g.getWeight("333", "444", weight) == true);
    ASSERT_TRUE(weight == 333.0);
    ASSERT_TRUE(g.getWeight("666", "777", weight) == true);
    ASSERT_TRUE(weight == 666.0);

    for(int i = 111; i <= 444; i = i + 111) 
    {
        ASSERT_TRUE(g.addEdge(to_string(111), to_string(i + 222), double(111)));
    }
    ASSERT_TRUE(g.NumVertices() == 8);
    ASSERT_TRUE(g.NumEdges() == 12);
    ASSERT_TRUE(g.getWeight("111", "333", weight) == true);
    ASSERT_TRUE(weight == 111.0);
    ASSERT_TRUE(g.getWeight("111", "444", weight) == true);
    ASSERT_TRUE(weight == 111.0);
    ASSERT_TRUE(g.getWeight("111", "555", weight) == true);
    ASSERT_TRUE(weight == 111.0);
    ASSERT_TRUE(g.getWeight("111", "666", weight) == true);
    ASSERT_TRUE(weight == 111.0);
    ASSERT_TRUE(g.getWeight("111", "777", weight) == false);

    graph gcopy(g);

    ASSERT_TRUE(g.NumVertices() == 8);
    ASSERT_TRUE(g.NumEdges() == 12);

    ASSERT_TRUE(gcopy.NumVertices() == 8);
    ASSERT_TRUE(gcopy.NumEdges() == 12);

    ASSERT_TRUE(g.addVertex("123") == true);
    ASSERT_TRUE(g.addVertex("456") == true);
    ASSERT_TRUE(g.addEdge("222", "444", 234.0) == true);
    ASSERT_TRUE(g.addEdge("333", "555", 345.0) == true);
    ASSERT_TRUE(g.NumVertices() == 10);
    ASSERT_TRUE(g.NumEdges() == 14);

    ASSERT_TRUE(gcopy.addVertex("321") == true);
    ASSERT_TRUE(gcopy.addVertex("654") == true);
    ASSERT_TRUE(gcopy.addVertex("987") == true);
    ASSERT_TRUE(gcopy.addEdge("222", "666", 246.0) == true);
    ASSERT_TRUE(gcopy.addEdge("333", "777", 357.0) == true);
    ASSERT_TRUE(gcopy.addEdge("444", "888", 468.0) == true);
    ASSERT_TRUE(gcopy.NumVertices() == 11);
    ASSERT_TRUE(gcopy.NumEdges() == 15);

    ASSERT_TRUE(g.getWeight("222", "444", weight) == true);
    ASSERT_TRUE(g.getWeight("333", "555", weight) == true);
    ASSERT_TRUE(gcopy.getWeight("222", "666", weight) == true);
    ASSERT_TRUE(gcopy.getWeight("333", "777", weight) == true);

    ASSERT_TRUE(gcopy.getWeight("222", "444", weight) == false);
    ASSERT_TRUE(gcopy.getWeight("333", "555", weight) == false);
    ASSERT_TRUE(g.getWeight("222", "666", weight) == false);
    ASSERT_TRUE(g.getWeight("333", "777", weight) == false);
    
    ASSERT_TRUE(g.NumVertices() == 10);
    ASSERT_TRUE(gcopy.NumVertices() == 11);
    ASSERT_TRUE(g.NumEdges() == 14);
    ASSERT_TRUE(gcopy.NumEdges() == 15);
}//overall_test

//
// basics_test
//
// tests correctness for when two graphs are set equal to each other
// maintains distinct changes from after equalized
//
TEST(graph, basics_test)
{
    graph g;

    ASSERT_TRUE(g.NumVertices() == 0);
    ASSERT_TRUE(g.NumEdges() == 0);

    vector<string> friends = {"daisy", "amelia", "sanjana", "meera", "yasmin", "athena", "kyra", "gabi"};

    for(string f: friends)
    {
        ASSERT_TRUE(g.addVertex(f) == true);
        ASSERT_TRUE(g.addVertex(f) == false);
    }
    ASSERT_TRUE(g.NumVertices() == 8);

    ASSERT_TRUE(g.addEdge("daisy", "amelia", 4.0) == true);
    ASSERT_TRUE(g.addEdge("amelia", "sanjana", 4.5) == true);
    ASSERT_TRUE(g.addEdge("meera", "yasmin", 4.5) == true);
    ASSERT_TRUE(g.addEdge("yasmin", "athena", 5.0) == true);
    ASSERT_TRUE(g.addEdge("gabi", "kyra", 5.0) == true);
    ASSERT_TRUE(g.addEdge("kyra", "yasmin", 3.0) == true);
    ASSERT_TRUE(g.addEdge("meera", "daisy", 3.0) == true);
    ASSERT_TRUE(g.addEdge("athena", "sanjana", 3.5) == true);

    set<string> fr = g.neighbors("meera");
    set<string> frset = {"yasmin", "daisy"};
    ASSERT_TRUE(fr == frset);

    ASSERT_TRUE(g.NumEdges() == 8);

    graph G;

    ASSERT_TRUE(G.NumVertices() == 0);
    ASSERT_TRUE(G.NumEdges() == 0);

    vector<string> friends2 = {"ellen", "kayla", "maddie", "nathan", "david"};

    for(string f: friends2)
    {
        ASSERT_TRUE(G.addVertex(f) == true);
        ASSERT_TRUE(G.addVertex(f) == false);
    }
    ASSERT_TRUE(G.NumVertices() == 5);

    ASSERT_TRUE(G.addEdge("ellen", "maddie", 4.0) == true);
    ASSERT_TRUE(G.addEdge("ellen", "nathan", 4.5) == true);
    ASSERT_TRUE(G.addEdge("nathan", "david", 4.5) == true);
    ASSERT_TRUE(G.addEdge("david", "ellen", 5.0) == true);
    ASSERT_TRUE(G.addEdge("kayla", "nathan", 5.0) == true);

    fr = G.neighbors("ellen");
    frset = {"maddie", "nathan"};
    ASSERT_TRUE(fr == frset);

    ASSERT_TRUE(G.NumEdges() == 5);

    g = G;

    ASSERT_TRUE(G.NumVertices() == 5);
    ASSERT_TRUE(G.NumEdges() == 5);
    ASSERT_TRUE(g.NumVertices() == 5);
    ASSERT_TRUE(g.NumEdges() == 5);

    fr = g.neighbors("ellen");
    frset = {"maddie", "nathan"};
    ASSERT_TRUE(fr == frset);

    ASSERT_TRUE(g.addVertex("kat") == true);
    ASSERT_TRUE(g.addVertex("franklin") == true);
    ASSERT_TRUE(g.addVertex("louis") == true);

    ASSERT_TRUE(g.addEdge("ellen", "kat", 3.0) == true);
    ASSERT_TRUE(g.addEdge("franklin", "nathan", 4.5) == true);
    ASSERT_TRUE(g.addEdge("franklin", "david", 4.5) == true);
    ASSERT_TRUE(g.addEdge("louis", "ellen", 5.0) == true);
    ASSERT_TRUE(g.addEdge("louis", "nathan", 4.0) == true);
    ASSERT_TRUE(g.addEdge("david", "kayla", 3.0) == true);
    ASSERT_TRUE(g.addEdge("maddie", "franklin", 3.0) == true);

    ASSERT_TRUE(G.addVertex("brooks") == true);
    ASSERT_TRUE(G.addVertex("caleb") == true);
    ASSERT_TRUE(G.addVertex("joseph") == true);
    ASSERT_TRUE(G.addVertex("evan") == true);

    ASSERT_TRUE(G.addEdge("brooks", "caleb", 4.0) == true);
    ASSERT_TRUE(G.addEdge("brooks", "joseph", 4.5) == true);
    ASSERT_TRUE(G.addEdge("evan", "brooks", 4.5) == true);
    ASSERT_TRUE(G.addEdge("joseph", "caleb", 5.0) == true);
    ASSERT_TRUE(G.addEdge("joseph", "evan", 5.0) == true);

    ASSERT_TRUE(G.NumVertices() == 9);
    ASSERT_TRUE(G.NumEdges() == 10);
    ASSERT_TRUE(g.NumVertices() == 8);
    ASSERT_TRUE(g.NumEdges() == 12);
}//basics_test

//
// neighbors_test
//
// tests if the neighbors function works correctly
// test on empty graph, where v does not exist, and when v has no neighbors
//
TEST(graph, neighbors_test)
{
    graph g;

    set<string> set0 = g.neighbors("v");
    ASSERT_TRUE(set0.size() == 0);

    ASSERT_TRUE(g.NumVertices() == 0);
    ASSERT_TRUE(g.NumEdges() == 0);

    for(int i = 1; i <= 10; i++)
    {
        ASSERT_TRUE(g.addVertex(to_string(i)) == true);
        ASSERT_TRUE(g.addVertex(to_string(i)) == false);
    }
    ASSERT_TRUE(g.NumVertices() == 10);

    for(int i = 1; i <= g.NumVertices(); i++)
    {
        for(int j = i+1; j <= g.NumVertices(); j++)
        {
            ASSERT_TRUE(g.addEdge(to_string(i), to_string(j), double(i * 10)) == true);
        }
    }
    ASSERT_TRUE(g.NumEdges() == 45);

    set0 = g.neighbors("v");
    ASSERT_TRUE(set0.size() == 0);

    set<string> set1;
    set<string> set2;

    set1 = g.neighbors("1");
    ASSERT_TRUE(set1.size() == 9);
    set2 = {"2", "3", "4", "5", "6", "7", "8", "9", "10"};
    ASSERT_TRUE(set1 == set2);

    set1 = g.neighbors("3");
    ASSERT_TRUE(set1.size() == 7);
    set2 = {"4", "5", "6", "7", "8", "9", "10"};
    ASSERT_TRUE(set1 == set2);

    set1 = g.neighbors("5");
    ASSERT_TRUE(set1.size() == 5);
    set2 = {"6", "7", "8", "9", "10"};
    ASSERT_TRUE(set1 == set2);

    set1 = g.neighbors("7");
    ASSERT_TRUE(set1.size() == 3);
    set2 = {"8", "9", "10"};
    ASSERT_TRUE(set1 == set2);

    set1 = g.neighbors("9");
    ASSERT_TRUE(set1.size() == 1);
    set2 = {"10"};
    ASSERT_TRUE(set1 == set2);

    set1 = g.neighbors("10");
    ASSERT_TRUE(set1.size() == 0);

    ASSERT_TRUE(g.NumVertices() == 10);
    ASSERT_TRUE(g.NumEdges() == 45);
}//neighbors_test

//
// getVertices_test
//
// tests if the getVertices function works correctly
// tests on empty graph
//
TEST(graph, getVertices_test)
{
    graph g;
    vector<string> vert = g.getVertices();
    vector<string> animals = {"duck", "moose", "tiger", "platypus", "cow", "bunny"};

    ASSERT_TRUE(vert.size() == 0);

    ASSERT_TRUE(g.NumVertices() == 0);
    ASSERT_TRUE(g.NumEdges() == 0);

    ASSERT_TRUE(g.addVertex("cat") == true);
    ASSERT_TRUE(g.addVertex("dog") == true);
    ASSERT_TRUE(g.addVertex("cat") == false);
    ASSERT_TRUE(g.addEdge("cat", "dog", 1.0) == true);
    ASSERT_TRUE(g.addEdge("dog", "cat", -1.0) == true);

    ASSERT_TRUE(g.NumVertices() == 2);
    ASSERT_TRUE(g.NumEdges() == 2);

    vert = g.getVertices();
    ASSERT_TRUE(vert.size() == 2);
    ASSERT_TRUE(vert[0] == "cat");
    ASSERT_TRUE(vert[1] == "dog");

    for(string a: animals)
    {
        ASSERT_TRUE(g.addVertex(a) == true);
    }
    ASSERT_TRUE(g.NumVertices() == 8);
    ASSERT_TRUE(g.NumEdges() == 2);

    vert = g.getVertices();
    ASSERT_TRUE(vert.size() == 8);
    ASSERT_TRUE(g.NumVertices() == vert.size());

    ASSERT_TRUE(g.addEdge("cat", "tiger", 4.0) == true);
    ASSERT_TRUE(g.addEdge("tiger", "cat", -4.0) == true);
    ASSERT_TRUE(g.addEdge("bunny", "dog", 6.0) == true);
    ASSERT_TRUE(g.addEdge("dog", "bunny", -6.0) == true);
    ASSERT_TRUE(g.addEdge("duck", "moose", 9.0) == true);
    ASSERT_TRUE(g.addEdge("moose", "duck", -9.0) == true);
    ASSERT_TRUE(g.addEdge("platypus", "cow", 7.0) == true);
    ASSERT_TRUE(g.addEdge("cow", "platypus", -7.0) == true);
    ASSERT_TRUE(g.addEdge("bunny", "cat", 3.0) == true);
    ASSERT_TRUE(g.addEdge("cat", "bunny", -3.0) == true);

    ASSERT_TRUE(g.NumVertices() == 8);
    ASSERT_TRUE(g.NumEdges() == 12);
}//getVertices_test

//
// stress_test
//
// very large graph
//
TEST(graph, stress_test)
{
    graph g;

    ASSERT_TRUE(g.NumVertices() == 0);
    ASSERT_TRUE(g.NumEdges() == 0);

    for(int i = 0; i < 5000000; i++)
    {
        ASSERT_TRUE(g.addVertex(to_string(i)) == true);
    }
    ASSERT_TRUE(g.NumVertices() == 5000000);

    for(int i = 0; i < 5000000 - 5; i = i + 5)
    {
        ASSERT_TRUE(g.addEdge(to_string(i), to_string(i + 5), i) == true);
    }
    ASSERT_TRUE(g.NumEdges() == 999999);

    set<string> n = g.neighbors("0");
    set<string> nset = {"5"};
    ASSERT_TRUE(n == nset);

    n = g.neighbors("1");
    nset = {};
    ASSERT_TRUE(n == nset);

    n = g.neighbors("4999990");
    nset = {"4999995"};
    ASSERT_TRUE(n == nset);

    vector<string> v = g.getVertices();
    ASSERT_TRUE(v.size() == 5000000);

    double weight = 0.0;
    for(int i = 0; i < 5000000 - 5; i = i + 5)
    {
        weight = 0.0;
        string first = to_string(i);
        string second = to_string(i + 5);

        ASSERT_TRUE(g.getWeight(first, second, weight) == true);

        ASSERT_TRUE(fabs(i - weight) < 0.00001);
    }

    ASSERT_TRUE(g.NumVertices() == 5000000);
    ASSERT_TRUE(g.NumEdges() == 999999);
}//stress_test

int main()
{
    ::testing::InitGoogleTest();

    //
    // run all the tests, returns 0 if they
    // all pass and 1 if any fail:
    //
    int result = RUN_ALL_TESTS();

    return result;
}

