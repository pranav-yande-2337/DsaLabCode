#include<iostream>
#include<string>
#include<queue>

using namespace std;

// Node structure for Adjacency List
class Node {
public:
    int val;
    Node* next;

    Node(int v) {
        val = v;
        next = NULL;
    }
};

class GraphLandmarks {
public:
    int GAM[10][10];       // Adjacency Matrix
    Node* HeaderGAL[10];   // Adjacency List (Array of Headers)
    int visited[10];
    int n;
    
    // Landmark names mapping
    string landmarks[10] = {"Admin", "Canteen", "Sports", "Workshop", "Library", "Hostel"};

    GraphLandmarks() {
        n = 0;
        for (int i = 0; i < 10; i++) {
            visited[i] = 0;
            HeaderGAL[i] = NULL;
            for (int j = 0; j < 10; j++) {
                GAM[i][j] = 0;
            }
        }
    }

    // Function to add edges to both Matrix and List
    void addEdge(int s, int d) {
        // 1. Update Adjacency Matrix
        GAM[s][d] = 1;
        GAM[d][s] = 1; // Assuming undirected for a map

        // 2. Update Adjacency List
        Node* newNode = new Node(d);
        if (HeaderGAL[s] == NULL) {
            HeaderGAL[s] = newNode;
        } else {
            Node* temp = HeaderGAL[s];
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNode;
        }

        // Add reverse for undirected list
        Node* newNodeRev = new Node(s);
        if (HeaderGAL[d] == NULL) {
            HeaderGAL[d] = newNodeRev;
        } else {
            Node* temp = HeaderGAL[d];
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNodeRev;
        }
    }

    // DFS using Adjacency Matrix (Recursive)
    void DFS(int startNode) {
        cout << landmarks[startNode] << " ";
        visited[startNode] = 1;

        for (int i = 0; i < n; i++) {
            if (GAM[startNode][i] == 1 && !visited[i]) {
                DFS(i);
            }
        }
    }

    // BFS using Adjacency List (Non-recursive using Queue)
    void BFS(int startNode) {
        queue<int> q;
        
        visited[startNode] = 1;
        q.push(startNode);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << landmarks[current] << " ";

            Node* temp = HeaderGAL[current];
            while (temp != NULL) {
                if (!visited[temp->val]) {
                    visited[temp->val] = 1;
                    q.push(temp->val);
                }
                temp = temp->next;
            }
        }
    }

    void resetVisited() {
        for (int i = 0; i < 10; i++) visited[i] = 0;
    }
};

int main() {
    GraphLandmarks g;
    g.n = 4; // Admin(0), Canteen(1), Sports(2), Workshop(3)

    // Building a sample campus map
    g.addEdge(0, 1); // Admin to Canteen
    g.addEdge(1, 2); // Canteen to Sports
    g.addEdge(2, 3); // Sports to Workshop
    g.addEdge(0, 3); // Admin to Workshop

    cout << "DFS Traversal (Matrix): ";
    g.resetVisited();
    g.DFS(0); 

    cout << "\nBFS Traversal (List): ";
    g.resetVisited();
    g.BFS(0);

    return 0;
}