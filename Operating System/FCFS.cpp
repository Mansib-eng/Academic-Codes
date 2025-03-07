/*
// FCFS

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
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

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter process name, arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].name >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    // Sort processes by arrival time (FCFS scheduling assumes processes arrive in order)
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    double totalTurnaroundTime = 0, totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        // Completion time
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;
        processes[i].completionTime = currentTime + processes[i].burstTime;
        currentTime = processes[i].completionTime;

        // Turnaround time = Completion time - Arrival time
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnaroundTime += processes[i].turnaroundTime;

        // Waiting time = Turnaround time - Burst time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;

        // Response time = Waiting time in FCFS
        processes[i].responseTime = processes[i].waitingTime;
    }

    // Display the results
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n";
    for (const auto& process : processes) {
        cout << process.name << "\t" << process.arrivalTime << "\t" << process.burstTime
             << "\t" << process.completionTime << "\t\t" << process.turnaroundTime
             << "\t\t" << process.waitingTime << "\t" << process.responseTime << "\n";
    }

    // Calculate averages
    double avgTurnaroundTime = totalTurnaroundTime / n;
    double avgWaitingTime = totalWaitingTime / n;

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << "\n";
    cout << "Average Waiting Time: " << avgWaitingTime << "\n";

    return 0;
}
*/
// FCFS with burst time generation

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
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

int generateRandomBurstTime(int minBurst = 1, int maxBurst = 10) {
    return minBurst + rand() % (maxBurst - minBurst + 1);
}

int main() {
    srand(time(0)); // Seed for random number generation

    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter process name and arrival time for process " << i + 1 << ": ";
        cin >> processes[i].name >> processes[i].arrivalTime;
        processes[i].burstTime = generateRandomBurstTime();
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    double totalTurnaroundTime = 0, totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        processes[i].responseTime = processes[i].waitingTime;

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;

        currentTime = processes[i].completionTime;
    }

    // Display the results
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n";
    for (const auto& process : processes) {
        cout << process.name << "\t" << process.arrivalTime << "\t" << process.burstTime
             << "\t" << process.completionTime << "\t\t" << process.turnaroundTime
             << "\t\t" << process.waitingTime << "\t" << process.responseTime << "\n";
    }

    // Calculate averages
    double avgTurnaroundTime = totalTurnaroundTime / n;
    double avgWaitingTime = totalWaitingTime / n;

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << "\n";
    cout << "Average Waiting Time: " << avgWaitingTime << "\n";

    return 0;
}