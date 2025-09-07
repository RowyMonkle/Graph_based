#include <iostream>
#include <vector>
#include "Graph.h"

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
    //shortestPath(Graph& graph, string start, string Destination, int weight) format
    shortestPath(graph, "A", "I", 0);
    shortestPath(graph, "E", "G", 0);

    return 0;
}
