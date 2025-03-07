/// Preemption SJF

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <ctime>
using namespace std;

struct Process {
    string name;          // Process name
    int arrivalTime;      // Arrival time (input)
    int burstTime;        // Burst time (randomly generated)
    int remainingTime;    // Remaining burst time
    int completionTime;   // Completion time
    int turnaroundTime;   // Turnaround time
    int waitingTime;      // Waiting time
    int responseTime;     // Response time
    bool started;         // Whether the process has started execution
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter the name and arrival time of process " << i + 1 << ": ";
        cin >> processes[i].name >> processes[i].arrivalTime;
        processes[i].burstTime = rand() % 10 + 1; // Random burst time (1-10)
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].started = false;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;  // Current time in simulation
    int completed = 0;    // Number of completed processes
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    while (completed < n) {
        int idx = -1;
        int minRemainingTime = INT_MAX;

        // Find the process with the shortest remaining time at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRemainingTime) {
                    minRemainingTime = processes[i].remainingTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Process the selected process for 1 unit of time
            if (!processes[idx].started) {
                processes[idx].responseTime = currentTime - processes[idx].arrivalTime;
                processes[idx].started = true;
            }
            processes[idx].remainingTime--;
            currentTime++;

            // If the process is completed
            if (processes[idx].remainingTime == 0) {
                completed++;
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

                totalTurnaroundTime += processes[idx].turnaroundTime;
                totalWaitingTime += processes[idx].waitingTime;
            }
        } else {
            // If no process is ready, advance time
            currentTime++;
        }
    }

    // Display the process table
    cout << "\nProcess Details:\n";
    cout << left << setw(10) << "Name"
         << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time"
         << setw(20) << "Completion Time"
         << setw(20) << "Turnaround Time"
         << setw(15) << "Waiting Time"
         << setw(15) << "Response Time" << endl;

    for (auto& process : processes) {
        cout << left << setw(10) << process.name
             << setw(15) << process.arrivalTime
             << setw(15) << process.burstTime
             << setw(20) << process.completionTime
             << setw(20) << process.turnaroundTime
             << setw(15) << process.waitingTime
             << setw(15) << process.responseTime << endl;
    }

    // Display averages
    cout << "\nAverage Turnaround Time: " << totalTurnaroundTime / n << endl;
    cout << "Average Waiting Time: " << totalWaitingTime / n << endl;

    return 0;
}

/*
4
p1 1
p2 2
p3 1
p4 4
*/
