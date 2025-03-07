#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <numeric>
#include<chrono>
#include<thread>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    double burst_time; // Using double to allow for fractional burst times
};

// Function to simulate a CPU-bound process
double cpuBoundProcess() {
    clock_t start = clock();
    // Simulate CPU-bound computation
    for (int i = 0; i < 100000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to simulate an I/O-bound process
double ioBoundProcess() {
    clock_t start = clock();
    // Simulate I/O-bound operation
    for (int i = 0; i < 1000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to simulate a process with high priority
double highPriorityProcess() {
    clock_t start = clock();
    // Simulate process with high priority
    for (int i = 0; i < 50000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to simulate a process with low priority
double lowPriorityProcess() {
    clock_t start = clock();
    // Simulate process with low priority
    for (int i = 0; i < 20000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Round Robin Scheduling Algorithm
pair<double, double> roundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<int> ready_queue;
    double total_time = 0;
    vector<double> remaining_time(n);
    vector<double> waiting_time(n, 0);
    vector<double> turnaround_time(n, 0);
    for (int i = 0; i < n; ++i)
        remaining_time[i] = processes[i].burst_time;

    cout << "\nTime Quantum: " << quantum << endl;
    cout << "\nRound Robin Scheduling:" << endl;

    while (true) {
        bool all_finished = true;
        for (int i = 0; i < n; ++i) {
            if (remaining_time[i] > 0) {
                all_finished = false;
                if (remaining_time[i] > quantum) {
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in ready queue" << endl;
                    total_time += quantum;
                    remaining_time[i] -= quantum;
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in running queue" << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                } else {
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in ready queue" << endl;
                    total_time += remaining_time[i];
                    waiting_time[i] = total_time - processes[i].burst_time;
                    remaining_time[i] = 0;
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " completes execution" << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }
            }
        }
        if (all_finished) break;
    }

    for (int i = 0; i < n; ++i)
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];

    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / n;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / n;
    this_thread::sleep_for(chrono::seconds(2));

    return {avg_waiting_time, avg_turnaround_time};
}

int main() {
    // Initialize processes
    vector<Process> processes;
    processes.push_back({1, 0, cpuBoundProcess()});
    processes.push_back({2, 0, ioBoundProcess()});
    processes.push_back({3, 0, highPriorityProcess()});
    processes.push_back({4, 0, lowPriorityProcess()});

    int quantum = 2; // Quantum for Round Robin

    // Print burst times of the processes
    cout << "Burst times of the processes:" << endl;
    for (const auto& process : processes) {
        cout << "Process " << process.pid << ": " << process.burst_time << " seconds" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    // Run Round Robin Scheduling
    //cout << "\nRound Robin Scheduling:" << endl;
    pair<double, double> rr_results = roundRobin(processes, quantum);
    cout << "\nAverage Waiting Time: " << rr_results.first << " seconds" << endl;
    cout << "Average Turnaround Time: " << rr_results.second << " seconds" << endl;

    return 0;
}
