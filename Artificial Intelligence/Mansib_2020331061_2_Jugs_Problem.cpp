#include <bits/stdc++.h>

using namespace std;

struct State {
    int jug1, jug2;
    string op;
};

bool solvetwoWaterJug(int X, int Y, int Z) {
    if (Z > X && Z > Y) return false;
    if (Z % __gcd(X, Y) != 0) return false;

    queue<vector<State>> q;
    set<pair<int, int>> visited;

    q.push({{0, 0, "Start with empty jugs"}});
    visited.insert({0, 0});

    while (!q.empty()) {
        vector<State> path = q.front();
        q.pop();

        State current = path.back();
        int a = current.jug1, b = current.jug2;

        if (a == Z || b == Z) {
            cout << "Solution found!\n";
            for (const auto& step : path) {
                cout << step.op << " -> (" << step.jug1 << ", " << step.jug2 << ")\n";
            }
            return true;
        }

        vector<State> nextStates = {
            {X, b, "Fill Jug1"},
            {a, Y, "Fill Jug2"},
            {0, b, "Empty Jug1"},
            {a, 0, "Empty Jug2"},
            {a - min(a, Y - b), b + min(a, Y - b), "Pour Jug1 -> Jug2"},
            {a + min(b, X - a), b - min(b, X - a), "Pour Jug2 -> Jug1"}
        };

        for (auto next : nextStates) {
            if (visited.find({next.jug1, next.jug2}) == visited.end()) {
                vector<State> newPath = path;
                newPath.push_back(next);
                q.push(newPath);
                visited.insert({next.jug1, next.jug2});
            }
        }
    }

    cout << "No solution possible!\n";
    return false;
}

int main() {
    int X = 3, Y = 4, Z = 2;
    if (!solvetwoWaterJug(X, Y, Z)) {
        cout << "No solution exists!\n";
    }
    return 0;
}


