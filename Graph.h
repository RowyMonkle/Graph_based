#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <vector>
#include<queue>

using namespace std;

class Node; //for Edge() access Node()

class Edge {
public:
    Node* from;
    Node* to; // destination node
    int weight; //distance between nodes (finding shortest path)
    Edge* next;

    Edge(Node* f, Node* t, int w) { 
        from = f;
        to = t;
        weight = w;
        next = nullptr;
    }
};

class Node { //Graph Node
public:
    string label;
    Edge* Head;
    Node* next;
    bool visited; //for BFS & DFS
    Node(string l) {
        label = l;
        Head = nullptr;
        next = nullptr;
        visited = false; //before traversal (using BFS & DFS)
    }

    ~Node() {
        Edge* current = Head;
        while (current != nullptr) {
            Edge* temp = current;
            current = current->next; 
            delete temp;
        }
    }
};

class Graph {
public:
    Node* Head; //head of the graph
    Graph() {
        Head = nullptr;
    }

    ~Graph() {
        Node* current = Head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    //create graph using adjacency matrix and labels
    //I stored in vector (Main())
    void createGraph(vector<vector<int>> matrix, vector<string> labels) {
        Head = nullptr; //reset head
        
        if (matrix.size() != labels.size()) {
            cout << "Error: Matrix size and labels size do not match." << endl;
            return;
        }

        //create nodes
        Node* prev = nullptr;
        for (size_t i = 0; i < labels.size(); i++) {
            Node* newNode = new Node(labels[i]);
            if (Head == nullptr) { //check Head
                Head = newNode;
            } else {
                prev->next = newNode; 
            }
            prev = newNode;
        }

        //create edges (in matrix view)
        Node* rowNode = Head; //traveral through rows
        for (size_t i = 0; i < matrix.size(); i++) {
            Node* colNode = Head;
            for (size_t j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != 0) { //if there is an edge
                    Edge* newEdge = new Edge(rowNode, colNode, matrix[i][j]);
                    newEdge->next = rowNode->Head;
                    rowNode->Head = newEdge;
                }
                colNode = colNode->next; // column traversal
            }
            rowNode = rowNode->next; // row traversal
        }
    }

    Node* findNode(string label) { //For searching algorithms (BFS & DFS)
        Node* temp = Head;
        while (temp != nullptr) {
            if (temp->label == label) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr; // if not found
    }

    void resetVisited() { //reset visited status for future calls
        Node* temp = Head;
        while (temp != nullptr) {
            temp->visited = false;
            temp = temp->next;
        }
    }

    void printGraph() { 
        Node* rowNode = Head;
        while (rowNode != nullptr) {
            cout << rowNode -> label << " ";
            Edge* edge = rowNode->Head;
            while (edge != nullptr) {
                cout << "(" << edge->to->label << ", " << edge->weight << ") "; // expected format: (destination, weight)
                edge = edge->next;
            }
            cout << endl;
            rowNode = rowNode->next;
        }
    }
};

//DFS and BFS 
void DFS(Graph& graph, string Label) { //depth first search, using stack
    Node* start = graph.findNode(Label);
    if (start == nullptr) {
        cout << "Start node not found!" << endl;
        return;
    }
    stack<Node*> st;
    graph.resetVisited(); //reset visited
    cout << "\nDFS (using Stack): ";
    st.push(start);
    start->visited = true; //mark as visited node

    while(!st.empty()) { //while stack is not empty
        Node* current = st.top(); //LIFO
        st.pop(); //remove top element

        current->visited = true; //mark as visited node
        cout << current->label << " ";

        Edge* edge = current->Head;
        while (edge != nullptr) {
            if(!edge->to->visited) { //check if not visited
                st.push(edge->to);
                edge = edge->next;
            } else {
                edge = edge->next; //in case already visited
            }
        } 
    }
    cout << "\nVisited Nodes: ";
    Node* temp = graph.Head;
    while (temp != nullptr) {
        if (temp->visited) {
            cout << temp->label << " ";
        }
        temp = temp->next;
    }   
    cout << endl;
}

void BFS(Graph& graph, string Label) { //breadth first search, using queue
    Node* start = graph.findNode(Label);
    if (start == nullptr) {
        cout << "Start node not found!" << endl;
        return;
    }

    graph.resetVisited(); //reset visited
    queue<Node*> q;
    
    cout << "\nBFS (using Queue): ";
    q.push(start);

    while (!q.empty()) { //while queue is not empty
        Node* current = q.front();
        q.pop();

        if(current->visited) {
            continue; //if already visited
        }
        current->visited = true; //mark as visited node

        cout << current->label << " ";

        Edge* edge = current->Head; // add neighbors
        while (edge != nullptr) {
            q.push(edge->to);
            edge->to->visited = true; //mark as visited edge
            edge = edge->next;
        }
    }
    cout << "\nVisited Nodes: ";
    Node* temp = graph.Head;
    while (temp != nullptr) {
        if (temp->visited) {
            cout << temp->label << " ";
        }
        temp = temp->next;
    }   
    cout << endl;
}
    

//Dijkstra (finding shortest path)

void shortestPath(Graph& graph, string Label, string Destination, int weight) {
    Node* start = graph.findNode(Label);
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
    
    //Mapping from the shortest distance (Dijkstra)
    //initialize distance as MAX before finding shortest path
    vector<int> distance(nodes.size(), INT_MAX);
    vector<bool> visited(nodes.size(), false); 
    vector<int> previous(nodes.size(), -1); //store previous node (mapping)
    
    int index = -1;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] == start) {
            index = i;
            distance[i] = 0; 
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
            /*if the distance to neighbor is shorter than current node
            update distance + route*/
            if (neighIndex != -1 && distance[reach] + edge->weight < distance[neighIndex]) {
                distance[neighIndex] = distance[reach] + edge->weight;
                previous[neighIndex] = reach; //previous node for mapping route, from this node to neighbor
                
            }
            edge = edge->next;
        }
    }
    
    //print results
    cout << " ====== Dijkstra's Algorithm ======" << endl;
    cout << "\nThe shortest path from " << start->label << "):" << endl;
    for(int i = 0; i , nodes.size(); i++) {
        cout << "Distance to" << nodes[i]->label << ": ";
        if (distance[i] == INT_MAX) {
            cout << "oops! results come out as infinity (unreachable)" << endl;
            cout << "\nSeems like there is no path from " << start->label << " to " << nodes[i]->label << endl;
        } else {
            cout << distance[i] << endl;
        }

    //print route
    cout << "Mapping route: ";
    for(int i = 0; i < nodes.size(); i++) {
        if (distance[i] == INT_MAX) continue; //skip, don't show

        //if found
        cout << "The shortest route from " << start->label << " to " << nodes[i]->label << ": ";
        vector<string> path;

        //showing the backtracking route
        /* 
        Assume that now we already reaching at the destination (node i) and need to know "what track we've passed?""
        set variable 'stop' = current as destination node, then keep going back to previous node (previous[stop])
        So, if stop = -1, means no previous node
        */
        for(int stop = i; stop != -1; stop = previous[stop]) {
            path.push_back(nodes[stop]->label);
        }
        for(int cost = path.size() - 1; cost >= 0; cost--) {
            cout << path[cost];
            if (cost != 0) {
                cout << " -> ";
            }
        }
        cout << " (cost used: " << distance[i] << ")" << endl;
    }
}
    cout << endl;
}