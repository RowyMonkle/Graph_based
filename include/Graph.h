//Team Project of 670615022 and 6706150XX
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include<queue>

using namespace std;

class Node; //for Edge() access Node()

class Edge {
public:
    Node* from;
    Node* to;
    int weight;
    Edge* next;
    Edge(Node* f, Node* t, int w);
};

class Node {
public:
    string label;
    Edge* Head;
    Node* next;
    bool visited;
    ~Node();

    Node(string Label);
};

class Graph {
public:
    Node* Head;
    Graph();
    ~Graph();

    void createGraph(vector<vector<int>> matrix,
                     vector<string> labels);

    Node* findNode(string label);
    void resetVisited();
    void printGraph();
};

// DFS & BFS prototypes
void DFS(Graph& graph, string Label);
void BFS(Graph& graph, string Label);

#endif