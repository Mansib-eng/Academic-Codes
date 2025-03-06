/// BFS with all have equal path cost and that is 1.

#include <bits/stdc++.h>

using namespace std;

// Function to perform BFS and find the shortest path
void BFS(vector<vector<int>>& adj, int start, int goal, int vertices) {
    vector<bool> visited(vertices, false);
    vector<int> parent(vertices, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == goal) {

            vector<int> path;
            for (int v = goal; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());

            cout << "Goal vertex " << goal << " is reachable from initial vertex " << start << endl;
            cout << "Path: ";
            for (int v : path) {
                cout << v << " ";
            }
            cout << endl;
            return;
        }

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = node;
                q.push(neighbor);
            }
        }
    }

    cout << "Goal vertex " << goal << " is NOT reachable from initial vertex " << start << endl;
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
        adj[v].push_back(u);   // For unidirection
    }

    int start, goal;
    cout << "Enter the initial vertex: ";
    cin >> start;
    cout << "Enter the goal vertex: ";
    cin >> goal;

    BFS(adj, start, goal, vertices);

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
