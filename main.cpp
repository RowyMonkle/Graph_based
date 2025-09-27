#include <iostream>
#include <vector>
#include "Graph.h"
#include "Dijkstra.h"
#include "CheckGraph.h"
/*#include "GraphLab2.cpp"*/

using namespace std;

int main() {
    //create matrix
    vector<vector<int>> matrix = {
        {0,2,1,7,0,0,0,0,0}, 
        {2,0,5,5,0,0,0,0,0}, 
        {1,5,0,4,0,9,0,0,0}, 
        {7,5,4,0,8,0,0,0,0}, 
        {0,0,0,8,0,3,7,0,0}, 
        {0,0,9,0,3,0,5,10,0},
        {0,0,0,0,7,5,0,11,6},
        {0,0,0,0,0,10,11,0,3},
        {0,0,0,0,0,0,6,3,0}
    };
    vector<string> labels = {"A","B","C","D","E","F","G","H","I"};

    Graph graph;
    graph.createGraph(matrix, labels);
    graph.printGraph();
    cout << endl; 

    //run DFS and BFS
    DFS(graph, "A"); 
    DFS(graph, "E"); //test if don't using resetVisited()
    graph.resetVisited(); 
    BFS(graph, "A");
    BFS(graph, "H"); 

    cout << endl;
    //Dijkstra (finding shortest path)
    //For error, it said that a reference type "Graph &graph" connot be initialized with a value of type "Graph" 
    shortestPath(graph, "A", "I");
    shortestPath(graph, "E", "G");

    cout << endl;
    //Check graph type
    cout << "Check Pseudograph? "  << (checkPseudograph(graph)? "Yes" : "No") << endl;
    cout << "Check Weighted Graph? " << (checkWeightedGraph(graph)? "Yes" : "No") << endl;
    // Check if the graph is disjoint
    cout << "Is the graph disjoint? " << (checkDisjointGraph(graph) ? "Yes" : "No") << endl;

    return 0;
}
