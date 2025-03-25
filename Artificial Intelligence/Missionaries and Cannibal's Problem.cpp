#include <iostream>
#include <queue>
#include <unordered_set>
#include <tuple>
#include <vector>

using namespace std;

struct State {
    int m_left, c_left, boat, m_right, c_right;
    vector<string> path;

    State(int ml, int cl, int b, int mr, int cr, vector<string> p = {})
        : m_left(ml), c_left(cl), boat(b), m_right(mr), c_right(cr), path(p) {}

    bool is_valid() const {
        if ((m_left < c_left && m_left > 0) || (m_right < c_right && m_right > 0))
            return false;
        return m_left >= 0 && c_left >= 0 && m_right >= 0 && c_right >= 0;
    }

    bool is_goal() const {
        return m_left == 0 && c_left == 0 && m_right == 3 && c_right == 3;
    }

    bool operator==(const State& other) const {
        return tie(m_left, c_left, boat, m_right, c_right) ==
               tie(other.m_left, other.c_left, other.boat, other.m_right, other.c_right);
    }
};

// Custom Hash Function for unordered_set
struct StateHash {
    size_t operator()(const State& s) const {
        return hash<int>()(s.m_left) ^ hash<int>()(s.c_left) ^ hash<int>()(s.boat) ^
               hash<int>()(s.m_right) ^ hash<int>()(s.c_right);
    }
};

vector<State> get_next_states(State current) {
    vector<State> next_states;
    vector<pair<int, int>> moves = {{1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}};

    for (size_t i = 0; i < moves.size(); i++) {
        int m = moves[i].first;
        int c = moves[i].second;

        if (current.boat == 1) { // Move from left to right
            State new_state(current.m_left - m, current.c_left - c, 0, current.m_right + m, current.c_right + c, current.path);
            if (new_state.is_valid()) {
                new_state.path.push_back("Move " + to_string(m) + "M, " + to_string(c) + "C to right (Boat: " + to_string(m) + "M, " + to_string(c) + "C) "
                                         "[Left: " + to_string(new_state.m_left) + "M, " + to_string(new_state.c_left) + "C | "
                                         "Right: " + to_string(new_state.m_right) + "M, " + to_string(new_state.c_right) + "C]");
                next_states.push_back(new_state);
            }
        } else { // Move from right to left
            State new_state(current.m_left + m, current.c_left + c, 1, current.m_right - m, current.c_right - c, current.path);
            if (new_state.is_valid()) {
                new_state.path.push_back("Move " + to_string(m) + "M, " + to_string(c) + "C to left (Boat: " + to_string(m) + "M, " + to_string(c) + "C) "
                                         "[Left: " + to_string(new_state.m_left) + "M, " + to_string(new_state.c_left) + "C | "
                                         "Right: " + to_string(new_state.m_right) + "M, " + to_string(new_state.c_right) + "C]");
                next_states.push_back(new_state);
            }
        }
    }
    return next_states;
}

void solve() {
    State initial(3, 3, 1, 0, 0);
    queue<State> q;
    unordered_set<State, StateHash> visited;
    initial.path.push_back("Start: [Left: 3M, 3C | Right: 0M, 0C]");
    q.push(initial);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (visited.find(current) != visited.end()) continue;
        visited.insert(current);

        if (current.is_goal()) {
            cout << "Solution Steps: (Total Steps: " << current.path.size() - 1 << ")\n";
            for (size_t i = 0; i < current.path.size(); i++) {
                cout << "Step " << i << ": " << current.path[i] << endl;
            }
            return;
        }

        for (State next : get_next_states(current)) {
            q.push(next);
        }
    }

    cout << "No solution found.\n";
}

int main() {
    solve();
    return 0;
}
