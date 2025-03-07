// SJF(non-preemption)

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Process {
    string name;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

bool compareArrival(const Process &a, const Process &b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.burstTime < b.burstTime; // If arrival time is the same, sort by burst time
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurst(const Process &a, const Process &b) {
    return a.burstTime < b.burstTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    srand(time(0)); // Seed for random burst time generation

    // Input process name and arrival time
    for (int i = 0; i < n; ++i) {
        cout << "Enter process name and arrival time for process " << i + 1 << ": ";
        cin >> processes[i].name >> processes[i].arrivalTime;
        processes[i].burstTime = rand() % 10 + 1; // Random burst time between 1 and 10
    }

    // Sort processes by arrival time (and by burst time if arrival times are the same)
    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;
    float totalTurnaroundTime = 0, totalWaitingTime = 0;

    for (int i = 0; i < n; ++i) {
        // Find the next process to execute (shortest burst time among arrived processes)
        int shortestIndex = -1;
        for (int j = 0; j < n; ++j) {
            if (processes[j].arrivalTime <= currentTime && processes[j].completionTime == 0) {
                if (shortestIndex == -1 || processes[j].burstTime < processes[shortestIndex].burstTime) {
                    shortestIndex = j;
                }
            }
        }

        // If no process has arrived yet, move time forward
        if (shortestIndex == -1) {
            currentTime++;
            i--; // Retry for the current iteration
            continue;
        }

        // Process execution
        currentTime += processes[shortestIndex].burstTime;
        processes[shortestIndex].completionTime = currentTime;
        processes[shortestIndex].turnaroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
        processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;
        processes[shortestIndex].responseTime = processes[shortestIndex].waitingTime;

        totalTurnaroundTime += processes[shortestIndex].turnaroundTime;
        totalWaitingTime += processes[shortestIndex].waitingTime;
    }

    // Output results
    cout << "\nProcess Details:\n";
    cout << setw(10) << "Name"
         << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time"
         << setw(20) << "Completion Time"
         << setw(20) << "Turnaround Time"
         << setw(15) << "Waiting Time"
         << setw(15) << "Response Time"
         << "\n";

    for (const auto &p : processes) {
        cout << setw(10) << p.name
             << setw(15) << p.arrivalTime
             << setw(15) << p.burstTime
             << setw(20) << p.completionTime
             << setw(20) << p.turnaroundTime
             << setw(15) << p.waitingTime
             << setw(15) << p.responseTime
             << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << totalTurnaroundTime / n;
    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << "\n";

    return 0;
}
/*
4
p1 1
p2 2
p3 1
p4 4
*/
