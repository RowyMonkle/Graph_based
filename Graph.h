#include <iostream>
#include <string>
#include <stack>
#include<queue>

using namespace std;

class Node { //Graph Node
public:
    string label;
    Edge* Head;
    Node* next;
    Node(string l) {
        label = l;
        Head = nullptr;
        next = nullptr;
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

class Edge {
public:
    Node* from;
    Node* to; // destination node
    int weight; //distance between nodes (finding shortest path)
    Edge* next;

    Edge(Node* f, Node* t, int w) { //constructor
        from = f;
        to = t;
        weight = w; 
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
    void createGraph(vector<vector<int>> matrix, vector<string> labels) {
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

    void printGraph() { //print the graph
        Node* rowNode = Head;
        while (rowNode != nullptr) {
            cout << rowNode->label << " | ";
            Edge* edge = rowNode->Head;
            while (edge != nullptr) {
                cout << "(" << edge->to->label << ", " << edge->weight << ") ";
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
    
    /*
    //check visited nodes
    */

    queue<Node*> q;

    cout << "\nDFS (using Queue): ";
    q.push(graph.Head);

    while (!q.empty()) { //while queue is not empty
        Node* current = q.front();
        q.pop();
        cout << current->label << " ";

        Edge* edge = current->Head; // add neighbors
        while (edge != nullptr) {
            q.push(edge->to);
            edge = edge->next;
        }
    }
}

void BFS(Graph& graph, string Label) { //breadth first search, using stack
    Node* start = graph.findNode(Label);
    if (start == nullptr) {
        cout << "Start node not found!" << endl;
        return;
    }

    
    /*
    //visited nodes 
    bool(<vector<Node*, bool> visited;)
    visited[start] = true;
    */
    stack<Node*> st;

    cout << "\nBFS (using Stack): ";
    st.push(graph.Head);

    while(!st.empty()) { //while stack is not empty
        Node* current = st.top();
        st.pop(); //remove top element
        cout << current->label << " ";
        /*
        //print visited nodes
        (...)
        visited[current] = true;
        */
        Edge* edge = current->Head; // adding neighbors
        while (edge != nullptr) {
            st.push(edge->to);
            edge = edge->next;
        }
    }

}

/*
//Dijkstra (finding shortest path)
void shoetestPath(Graph& graph, string Label, int weight) {
    //finding start node
    //Mapping from the shortest distance (Dijkstra)
    
    //print
    
}
*/