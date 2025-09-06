#include <iostream>
#include <vector>
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

    /*Graph graph;
    graph.createGraph(matrix, labels);
    graph.printGraph();*/

    
    return 0;
}