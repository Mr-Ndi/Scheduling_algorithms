#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime; // Add remainingTime attribute
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareRemainingTime(const Process& a, const Process& b) {
    return a.remainingTime < b.remainingTime;
}

void calculateWaitingTimeSJF(Process processes[], int waitingTime[], int n) {
    processes[0].remainingTime = processes[0].burstTime;
    waitingTime[0] = 0;

    for (int i = 1; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
        waitingTime[i] = 0; // Initialize waiting times to 0
    }
}

int main() {
    int n; // Number of processes
    cout << "\nEnter the number of processes: ";
    cin >> n;

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "\t\tEnter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    // Sort processes based on arrival time
    sort(processes, processes + n, compareArrivalTime);

    // Calculate initial waiting times
    int waitingTime[n];
    calculateWaitingTimeSJF(processes, waitingTime, n);

    int currentTime = 0;

    // Execute processes
    while (true) {
        sort(processes, processes + n, compareRemainingTime);

        int shortestJobIndex = -1;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                shortestJobIndex = i;
                break;
            }
        }

        if (shortestJobIndex == -1) {
            // No process is ready to execute
            break;
        }

        processes[shortestJobIndex].remainingTime--;
        currentTime++;

        if (processes[shortestJobIndex].remainingTime == 0) {
            // Process completed
            waitingTime[shortestJobIndex] = currentTime - processes[shortestJobIndex].arrivalTime -
                                               processes[shortestJobIndex].burstTime;
        }
    }

    // Display waiting times
    cout << "\nWaiting Time for each process (SJF Preemptive):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << processes[i].id << ": SJF Preemptive=" << waitingTime[i] << endl;
    }

    // Calculate average waiting time
    double avgWaitingTimeSJF = accumulate(waitingTime, waitingTime + n, 0.0) / n;
    cout << "\nAverage Waiting Time (SJF Preemptive): " << avgWaitingTimeSJF << endl;

    return 0;
}
