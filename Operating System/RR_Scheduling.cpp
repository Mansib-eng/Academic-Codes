#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void roundRobin(vector<Process>& processes, int quantum) {
    queue<int> ready_queue;
    int current_time = 0;
    int n = processes.size();
    vector<bool> visited(n, false);

    while (true) {
        bool done = true;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ready_queue.push(i);
                visited[i] = true;
                done = false;
            }
        }

        if (done && ready_queue.empty()) {
            break;
        }

        if (!ready_queue.empty()) {
            int current_process = ready_queue.front();
            ready_queue.pop();

            clock_t start_time = clock(); // Start time of process execution

            if (processes[current_process].remaining_time > quantum) {
                current_time += quantum;
                processes[current_process].remaining_time -= quantum;
                ready_queue.push(current_process);
            } else {
                current_time += processes[current_process].remaining_time;
                processes[current_process].completion_time = current_time;
                processes[current_process].turnaround_time = processes[current_process].completion_time - processes[current_process].arrival_time;
                processes[current_process].waiting_time = processes[current_process].turnaround_time - processes[current_process].burst_time;
                processes[current_process].remaining_time = 0;
            }

            clock_t end_time = clock(); // End time of process execution
            processes[current_process].burst_time = (end_time - start_time) / CLOCKS_PER_SEC; // Calculating burst time
        } else {
            current_time++;
        }
    }
}

int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<Process> processes(num_processes);

    // Simulate random burst time for each process
    srand(time(NULL)); // Seed for random number generator

    for (int i = 0; i < num_processes; ++i) {
        processes[i].pid = i + 1;
        processes[i].burst_time = rand() % 20 + 1; // Random burst time between 1 and 20
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].arrival_time = 0; // Assuming all processes arrive at time 0
    }

    int quantum;
    cout << "Enter the time quantum for Round Robin: ";
    cin >> quantum;

    roundRobin(processes, quantum);

    cout << "\nProcess\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t\t" << process.burst_time << "\t\t"
             << process.completion_time << "\t\t" << process.turnaround_time << "\t\t" << process.waiting_time << "\n";
    }

    // Calculate average turnaround time and average waiting time
    double avg_turnaround = 0;
    double avg_waiting = 0;
    for (const auto& process : processes) {
        avg_turnaround += process.turnaround_time;
        avg_waiting += process.waiting_time;
    }
    avg_turnaround /= num_processes;
    avg_waiting /= num_processes;

    cout << "\nAverage Turnaround Time: " << avg_turnaround << endl;
    cout << "Average Waiting Time: " << avg_waiting << endl;

    return 0;
}
