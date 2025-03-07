#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <numeric>
#include <chrono>
#include <thread>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    double burst_time; // Using double to allow for fractional burst times
    int priority;
};

// Function to simulate a CPU-bound process
double cpuBoundProcess() {
    clock_t start = clock();
    // Simulate CPU-bound computation
    for (int i = 0; i < 100000000; ++i) {}
    clock_t end = clock();
     //this_thread::sleep_for(chrono::seconds(1)) ;
    return (double)(end - start)*1000 / CLOCKS_PER_SEC;
}

// Function to simulate an I/O-bound process
double ioBoundProcess() {
    clock_t start = clock();
    // Simulate I/O-bound operation
    for (int i = 0; i < 1000000; ++i) {}
    clock_t end = clock();
     //this_thread::sleep_for(chrono::seconds(1)) ;
    return (double)(end - start)*1000 / CLOCKS_PER_SEC;
}

// Function to simulate a process with high priority
double highPriorityProcess() {
    clock_t start = clock();
    // Simulate process with high priority
    for (int i = 0; i < 50000000; ++i) {}
    clock_t end = clock();
     //this_thread::sleep_for(chrono::seconds(1)) ;
    return (double)(end - start)*1000 / CLOCKS_PER_SEC;
}

// Function to simulate a process with low priority
double lowPriorityProcess() {
    clock_t start = clock();
    // Simulate process with low priority
    for (int i = 0; i < 20000000; ++i) {}
    clock_t end = clock();
     //this_thread::sleep_for(chrono::seconds(1)) ;
    return (double)(end - start)*1000 / CLOCKS_PER_SEC;
}

/*
// Priority Scheduling Algorithm
pair<double, double> priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    double total_time = 0;
    vector<double> waiting_time(n, 0);
    vector<double> turnaround_time(n, 0);

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority > b.priority;
    });

    for (int i = 0; i < n; ++i) {
            this_thread::sleep_for(chrono::seconds(1)) ;
        total_time += processes[i].burst_time;
        waiting_time[i] = total_time - processes[i].burst_time;
        turnaround_time[i] = total_time;
    }

    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / n;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / n;

    return {avg_waiting_time, avg_turnaround_time};
}*/
// Priority Scheduling Algorithm
pair<double, double> priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    double total_time = 0;
    vector<double> waiting_time(n, 0);
    vector<double> turnaround_time(n, 0);

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority > b.priority;
    });

    for (int i = 0; i < n; ++i) {
        this_thread::sleep_for(chrono::seconds(1)); // Introduce 1-second delay
        double process_time;
        if (processes[i].priority == 4)
            process_time = cpuBoundProcess();
        else if (processes[i].priority == 1)
            process_time = ioBoundProcess();
        else if (processes[i].priority == 2)
            process_time = highPriorityProcess();
        else if (processes[i].priority == 3)
            process_time = lowPriorityProcess();

        total_time += process_time;
        waiting_time[i] = total_time - process_time;
        turnaround_time[i] = total_time;
    }

    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / n;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / n;

    return {avg_waiting_time, avg_turnaround_time};
}

int main() {
    // Initialize processes
    vector<Process> processes;
    processes.push_back({1, 0, cpuBoundProcess(), 4});
    processes.push_back({2, 0, ioBoundProcess(), 1});
    processes.push_back({3, 0, highPriorityProcess(), 2});
    processes.push_back({4, 0, lowPriorityProcess(), 3});

    //this_thread::sleep_for(chrono::seconds(1)) ;

    // Print burst times of the processes
    cout << "Burst times and Priority of the processes:" << endl;
    for (const auto& process : processes) {
        cout << "Process " << process.pid << ": Burst Time => " << process.burst_time << " miliseconds" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

     // Run Priority Scheduling
    cout << "\nPriority Scheduling:" << endl;
    pair<double, double> priority_results = priorityScheduling(processes);
    cout << "Average Waiting Time: " << priority_results.first << " miliseconds" << endl;
    cout << "Average Turnaround Time: " << priority_results.second << " miliseconds" << endl;

    return 0;
}
