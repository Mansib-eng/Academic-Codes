#include <iostream>
#include <vector>

using namespace std;

class BankerAlgorithm {
private:
    vector<vector<int>> allocation;
    vector<vector<int>> max_resources;
    vector<int> available;
    vector<vector<int>> need;
    int num_processes;
    int num_resources;

    vector<int> calculate_need(int process_id) {
        vector<int> process_need;
        for (int i = 0; i < num_resources; ++i) {
            process_need.push_back(max_resources[process_id][i] - allocation[process_id][i]);
        }
        return process_need;
    }

    bool is_safe_state(vector<int>& work, vector<bool>& finish, vector<int>& process_sequence) {
        bool found;
        for (int i = 0; i < num_processes; ++i) {
            if (!finish[i]) {
                found = true;
                for (int j = 0; j < num_resources; ++j) {
                    if (need[i][j] > work[j]) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    for (int j = 0; j < num_resources; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    process_sequence.push_back(i);
                    return true;
                }
            }
        }
        return false;
    }

public:
    BankerAlgorithm(vector<vector<int>>& alloc, vector<vector<int>>& max_res, vector<int>& avail) {
        allocation = alloc;
        max_resources = max_res;
        available = avail;
        num_processes = alloc.size();
        num_resources = avail.size();
        need.resize(num_processes);
        for (int i = 0; i < num_processes; ++i) {
            need[i] = calculate_need(i);
        }
    }

    string find_safe_sequence() {
        vector<int> work = available;
        vector<bool> finish(num_processes, false);
        vector<int> process_sequence;

        while (true) {
            bool safe_state_found = false;
            for (int i = 0; i < num_processes; ++i) {
                if (!finish[i] && is_safe_state(work, finish, process_sequence)) {
                    safe_state_found = true;
                }
            }
            if (!safe_state_found) {
                for (int i = 0; i < num_processes; ++i) {
                    if (!finish[i]) {
                        return "No safe sequence found";
                    }
                }
                string sequence_str = "Safe sequence: ";
                for (int i = 0; i < num_processes; ++i) {
                    sequence_str += to_string(process_sequence[i]);
                    if (i != num_processes - 1) {
                        sequence_str += " -> ";
                    }
                }
                return sequence_str;
            }
        }
    }
};

int main() {
    vector<vector<int>> allocation_matrix = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    vector<vector<int>> max_resources_matrix = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    vector<int> available_resources = {3, 3, 2};

    BankerAlgorithm banker(allocation_matrix, max_resources_matrix, available_resources);
    cout << banker.find_safe_sequence() << endl;

    return 0;
}
