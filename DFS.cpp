#include <bits/stdc++.h>

using namespace std;

// Function to perform DFS and find the path
bool DFS(vector<vector<int>>& adj, int node, int goal, vector<bool>& visited, vector<int>& path) {
    visited[node] = true;
    path.push_back(node);

    if (node == goal) {
        return true; // Goal found
    }

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (DFS(adj, neighbor, goal, visited, path)) {
                return true; // Path found in recursion
            }
        }
    }

    path.pop_back(); // Backtrack if goal is not found
    return false;
}

int main() {
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;
    cout << "Enter number of edges: ";
    cin >> edges;

    vector<vector<int>> adj(vertices);

    cout << "Enter the edges (vertex1 vertex2):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // For unidirection
    }

    int start, goal;
    cout << "Enter the initial vertex: ";
    cin >> start;
    cout << "Enter the goal vertex: ";
    cin >> goal;

    vector<bool> visited(vertices, false);
    vector<int> path;

    if (DFS(adj, start, goal, visited, path)) {
        cout << "Goal vertex " << goal << " is reachable from initial vertex " << start << endl;
        cout << "Path: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "Goal vertex " << goal << " is NOT reachable from initial vertex " << start << endl;
    }

    return 0;
}


/**
Example =>
Number of Verteces = 9
Number of Edges = 10
Edges (vertex1 vertex2):
0 1
0 2
0 3
1 4
1 5
2 7
3 6
4 8
5 7
6 7
Initial Vertex = 0
Goal Vertex = 7
*/
