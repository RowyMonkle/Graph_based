#ifndef CHECKGRAPH_H
#define CHECKGRAPH_H

#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool checkPseudograph(Graph& graph);
bool checkWeightedGraph(Graph& graph);  
bool checkDisjointGraph(Graph& graph);

#endif

//check is this pseudograph type or not
//Pseudograph: a graph that having self-loop and multiple edges
bool checkPseudograph(Graph& graph) {
    graph.resetVisited();

    Node* rowNode = graph.Head;
    while (rowNode != nullptr) {
        Edge* edge = rowNode->Head;

        while (edge != nullptr) { //traverse edges
            if (edge->from == edge->to) { //has self-loop or not
                return true;
            }
            Edge* temp = edge->next;
            while (temp != nullptr) { //multiple edges check
                if (edge->to == temp->to) {
                    return true;
                }
                temp = temp->next;
            }
            edge = edge->next;
        }
        rowNode = rowNode->next;
    }
    return false; //if not this type
}

//check is this weighted graph or not
/*Weighted graph: refered as a graph that having edges not equal to 1*/
bool checkWeightedGraph(Graph& graph) {
    graph.resetVisited();

    Node* rowNode = graph.Head;
    while (rowNode != nullptr) {
        Edge* edge = rowNode->Head;

        while (edge != nullptr) { //traverse edges (while-loop)
            if (edge->weight != 1) {
                return true; // weight not equal to 1 = this is weighted!!
            }
            edge = edge->next;
        }
        rowNode = rowNode->next;
    }
    return false; //if not this type
} 


//check is this a disjoint graph or not
//Disjoint graph: has least 2 nodes not connected to each other 
bool checkDisjoint(Graph& graph) {

    //using BFS to traverse the graph, check is it all nodes are connected
    queue<Node*> q;
    Node* start = graph.Head;
    start->visited = true;
    q.push(start);

    //int for comparing, is all nodes = visited count or not
    int visitedCount = 0;
    int totalNodes = 0;

    Node* temp = graph.Head;
    while (temp != nullptr) { 
        totalNodes++;
        temp = temp->next;
    }
    while (!q.empty()) { //queue isn't empty -> BFS traversal
        Node* current = q.front();
        q.pop();
        visitedCount++; //check that nodes visited

        Edge* edge = current->Head;
        while (edge != nullptr) {
            if (!edge->to->visited) {
                edge->to->visited = true;
                q.push(edge->to);
            }
            edge = edge->next;
        }
    }

    graph.resetVisited();

    //after visiting all reachable nodes
    return visitedCount != totalNodes; //comparing, if not equal = disjoint graph
}