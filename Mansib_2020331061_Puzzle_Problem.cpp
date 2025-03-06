/// 8 Puzzle Problem Solved

#include <bits/stdc++.h>
using namespace std;

#define N 3


int row[] = {1, 0, -1, 0};
int col[] = {0, 1, 0, -1};
string moveDir[] = {"D", "R", "U", "L"};

struct Node {
    vector<vector<int>> puzzle;
    int x, y;
    int cost, level;
    string path;

    bool operator>(const Node& other) const {
        return (cost + level) > (other.cost + other.level);
    }
};

// Function to calculate Manhattan distance
int manhattDist(vector<vector<int>> &puzzle, vector<vector<int>> &goal) {
    int dist = 0;
    unordered_map<int, pair<int, int>> goalPos;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            goalPos[goal[i][j]] = {i, j};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != 0) {
                pair<int, int> correctPos = goalPos[puzzle[i][j]];
                dist += abs(i - correctPos.first) + abs(j - correctPos.second);
            }
        }
    }
    return dist;
}

// Function to check if the new position is valid
bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Solve the 8-puzzle problem using A* algorithm
void solvePuzzle(vector<vector<int>> &initial, vector<vector<int>> &goal, int x, int y) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<vector<vector<int>>> visited;

    Node start = {initial, x, y, manhattDist(initial, goal), 0, ""};
    pq.push(start);

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.puzzle == goal) {
            cout << "Solution found!\nMoves: " << node.path << "\n";
            cout << "Total Moves: " << node.level << "\n";
            return;
        }

        visited.insert(node.puzzle);

        for (int i = 0; i < 4; i++) {
            int newX = node.x + row[i], newY = node.y + col[i];

            if (isValid(newX, newY)) {
                vector<vector<int>> newPuzzle = node.puzzle;
                swap(newPuzzle[node.x][node.y], newPuzzle[newX][newY]);

                if (visited.find(newPuzzle) == visited.end()) {
                    int newCost = manhattDist(newPuzzle, goal);
                    Node child = {newPuzzle, newX, newY, newCost, node.level + 1, node.path + moveDir[i]};
                    pq.push(child);
                }
            }
        }
    }

    cout << "No solution found!\n";
}

int main() {
    vector<vector<int>> initial(N, vector<int>(N));
    vector<vector<int>> goal(N, vector<int>(N));

    cout << "Enter initial state (3x3 matrix, use 0 for blank):\n";
    int blankX, blankY;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> initial[i][j];
            if (initial[i][j] == 0) {
                blankX = i;
                blankY = j;
            }
        }
    }

    cout << "Enter goal state (3x3 matrix):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> goal[i][j];
        }
    }

    solvePuzzle(initial, goal, blankX, blankY);

    return 0;
}
