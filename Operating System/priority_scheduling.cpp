#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

const int N = 10000000;
const int n = 5;

struct Process {
    int pid;
     int arrival_time;
    double burst_time;
    int priority;
};


void func0()
{
    int sum = 0;
    for(int i=0; i<6*N; i++){
        sum = sum + i;
    }
}

void func1()
{
    int sum = 0;
    for(int i=0; i<12*N; i++){
            sum = sum + i;
    }

}

void func2()
{
    int sum = 0;
    for(int i=0;i<15*N;i++){
        sum = sum + i;
    }
}

void func3()
{
    int sum = 0;
    for(int i=0;i<3*N;i++){
        sum = sum + i;
    }
}

void func4()
{
    int sum = 0;
    for(int i=0;i<N;i++){
        sum = sum + i;
    }
}


void calculateTimes(Process proc[], double wt[], double tt[]) {
    wt[0] = 0;


    for (int i = 1; i < n; i++) {
        wt[i] = proc[i - 1].burst_time + wt[i - 1];
    }


    for (int i = 0; i < n; i++) {
        tt[i] = proc[i].burst_time + wt[i];
    }
}

bool comparePriority(Process a, Process b) {
    return a.priority > b.priority;
}

int main() {
    Process proc[n];
    double wt[n] = {0};
    double tt[n] = {0};


    clock_t start_time, end_time;

    // Process P0
    start_time = clock();
    func0();
    end_time = clock();
    proc[0] = {0, 0,static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC, 2};

    // Process P1
    start_time = clock();
    func1(); // Replace with your actual computation
    end_time = clock();
    proc[1] = {1,0, static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC, 1};

    // Process P2
    start_time = clock();
    func2(); // Replace with your actual computation
    end_time = clock();
    proc[2] = {2, 0,static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC, 4};

     start_time = clock();
    func3(); // Replace with your actual computation
    end_time = clock();
    proc[3] = {3, 0,static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC, 5};

     start_time = clock();
    func4(); // Replace with your actual computation
    end_time = clock();
    proc[4] = {4, 0,static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC, 3};

    // Sort processes by priority
    sort(proc, proc + n, comparePriority);

    // Calculate waiting time and turnaround time
    calculateTimes(proc, wt, tt);

    // Display process details
    cout << "Process\tArrival Time \tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << proc[i].pid << "\t" << proc[i].arrival_time << "\t\t" << proc[i].burst_time << "\t\t" << proc[i].priority
             << "\t\t" << wt[i] << "\t\t" << tt[i] << endl;
    }

    // Calculate average waiting time and average turnaround time
    double avg_wt = 0;
    double avg_tt = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }
    avg_wt /= n;
    avg_tt /= n;

    cout << "\nAverage waiting time = " << avg_wt << endl;
    cout << "Average turnaround time = " << avg_tt << endl;

    return 0;
}
