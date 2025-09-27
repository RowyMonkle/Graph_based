#include "Dijkstra.h"
using namespace std;

void shortestPath(Graph& graph, string Label, string Destination) {
    Node* start = graph.findNode(Label);
    Node* end = graph.findNode(Destination);
    if (start == nullptr) {
        cout << "Start node not found!" << endl;
        return;
    }
    graph.resetVisited(); 

    //check node
    vector<Node*> nodes;
    Node* temp = graph.Head;
    while (temp != nullptr) {
        nodes.push_back(temp);
        temp = temp->next;
    }
    
    /*Mapping from the shortest distance (Dijkstra)
    initialize distance as MAX before finding shortest path*/
    vector<int> distance(nodes.size(), INT_MAX);
    vector<bool> visited(nodes.size(), false); 
    vector<int> previous(nodes.size(), -1); //store previous node (mapping)
    
    int index = -1;
    int endIndex = -1;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] == start) {
            index = i;
            distance[i] = 0; 
        }
        if (nodes[i] == end) {
            endIndex = i;
        }
    }

    for (int step = 0; step < nodes.size() - 1; step++) {
        int reach = -1;
        int min = INT_MAX;
        for (int i = 0; i < nodes.size(); i++) {
            if (!visited[i] && distance[i] < min) {
                min = distance[i];
                reach = i;
            }
        }
        if (reach == -1) break; //no reachable node
        visited[reach] = true; 

        //neighbors
        Edge* edge = nodes[reach]->Head;
        while (edge != nullptr) {
            int neighIndex = -1; //neghbor index = edge -> node to be compared
            for (int i = 0; i < nodes.size(); i++) { //traverse
                if (nodes[i] == edge->to) {
                    neighIndex = i;
                    break;
                }
            }
            //if the distance to neighbor is shorter than current node, update distance + route
            if (neighIndex != -1 && distance[reach] + edge->weight < distance[neighIndex]) {
                distance[neighIndex] = distance[reach] + edge->weight;
                previous[neighIndex] = reach; //previous node for mapping route, from this node to neighbor
                
            }
            edge = edge->next;
        }
    }
    
    //print results
    cout << " ====== Dijkstra's Algorithm ======" << endl;
    cout << "\nThe shortest path from " << Label << " -> " << Destination << " was... " << endl;
    
    if (distance[endIndex] == INT_MAX) {
        cout << "oops! results come out as infinity (unreachable)" << endl;
        return;
    } else {
        //showing the backtracking route
        cout << "\nMapping route from " << Label << " to " << Destination << ": ";
        vector<string> path;
            
        //Assume that now we already reaching at the destination (node i) and need to know "what track we've passed?""
        //set variable 'stop' = current as destination node, then keep going back to previous node (previous[stop])
        //So, if stop = -1, means no previous node 
        
        for(int stop = endIndex; stop != -1; stop = previous[stop]) {
            path.push_back(nodes[stop]->label);
        }
        for(int cost = path.size() - 1; cost >= 0; cost--) {
            cout << path[cost];
            if (cost != 0) {
                cout << " -> ";
            }
        }
        cout << " (cost used: " << distance[endIndex] << ")" << endl;
    }
}