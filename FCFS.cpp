#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

/**
 * n : number of process
 * processes : array of process
 *
 * @Process : This structure defines a process with an ID, arrival time, and burst time.
 * @compareArrivalTime: It's a comparator function used for sorting processes based on their arrival time.
 * @calculateWaitingTimeFCFS: This function calculates the waiting time for each process in the First-Come-First-Serve
 */
struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
};

bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

void calculateWaitingTimeFCFS(Process processes[], int waitingTime[], int n)
{
    waitingTime[0] = 0;

    for (int i = 1; i < n; ++i)
    {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
}

int main()
{
    int n;
    cout << "\n\nEnter the number of processes\t: ";
    cin >> n;

    Process processes[n];

    cout << "\n"; // Input process details

    for (int i = 0; i < n; ++i)
    {
        processes[i].id = i + 1;
        cout << "\nEnter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "\t\tEnter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "----------------------------------------------------" << endl;
    }

    // Sorting the
    sort(processes, processes + n, compareArrivalTime);

    int waitingTimeFCFS[n] = {0};
    calculateWaitingTimeFCFS(processes, waitingTimeFCFS, n);

    // Display waiting times
    cout << "\n\tBasing on the details of your process \n\tthe Waiting time for each process by the algorithm of (FCFS):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Process " << i + 1 << ": FCFS=" << waitingTimeFCFS[i] << endl;
    }

    // Calculate average waiting time
    double avgWaitingTimeFCFS = accumulate(waitingTimeFCFS, waitingTimeFCFS + n, 0.0) / n;
    cout << "\nHence the average Waiting time becames: " << avgWaitingTimeFCFS << endl;

    return 0;
}
