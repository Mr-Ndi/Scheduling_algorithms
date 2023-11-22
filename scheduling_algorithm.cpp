#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
};

bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(const Process &a, const Process &b)
{
    return a.burstTime < b.burstTime;
}

bool comparePriority(const Process &a, const Process &b)
{
    return a.priority < b.priority;
}

void calculateWaitingTimeFCFS(Process processes[], int waitingTime[], int n)
{
    waitingTime[0] = 0;

    for (int i = 1; i < n; ++i)
    {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
}

void calculateWaitingTimeSJF(Process processes[], int waitingTime[], int n)
{
    waitingTime[0] = 0;

    for (int i = 1; i < n; ++i)
    {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
}

void calculateWaitingTimePriority(Process processes[], int waitingTime[], int n)
{
    waitingTime[0] = 0;

    for (int i = 1; i < n; ++i)
    {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
}

void calculateWaitingTimeRoundRobin(Process processes[], int waitingTime[], int n, int quantum)
{
    int remainingTime[n];
    for (int i = 0; i < n; ++i)
    {
        remainingTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;

    while (true)
    {
        bool allProcessesDone = true;

        for (int i = 0; i < n; ++i)
        {
            if (remainingTime[i] > 0)
            {
                allProcessesDone = false;

                if (remainingTime[i] > quantum)
                {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                }
                else
                {
                    currentTime += remainingTime[i];
                    waitingTime[i] = currentTime - processes[i].burstTime;
                    remainingTime[i] = 0;
                }
            }
        }

        if (allProcessesDone)
        {
            break;
        }
    }
}

int main()
{
    int n; // Number of processes
    cout << "\n\nEnter the number of processes: ";
    cin >> n;

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; ++i)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }

    // Sort processes based on arrival time
    sort(processes, processes + n, compareArrivalTime);

    int waitingTimeFCFS[n] = {0};
    calculateWaitingTimeFCFS(processes, waitingTimeFCFS, n);

    Process processesSJF[n];
    copy(processes, processes + n, processesSJF); // Copy processes for SJF
    sort(processesSJF, processesSJF + n, compareBurstTime);
    int waitingTimeSJF[n] = {0};
    calculateWaitingTimeSJF(processesSJF, waitingTimeSJF, n);

    Process processesPriority[n];
    copy(processes, processes + n, processesPriority); // Copy processes for Priority
    sort(processesPriority, processesPriority + n, comparePriority);
    int waitingTimePriority[n] = {0};
    calculateWaitingTimePriority(processesPriority, waitingTimePriority, n);

    int quantum; // Time quantum for Round Robin
    cout << "Enter the time quantum for Round Robin: ";
    cin >> quantum;
    int waitingTimeRoundRobin[n] = {0};
    calculateWaitingTimeRoundRobin(processes, waitingTimeRoundRobin, n, quantum);

    // Display waiting times
    cout << "\nWaiting Time for each process:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Process " << i + 1 << ": FCFS=" << waitingTimeFCFS[i] << " SJF=" << waitingTimeSJF[i]
             << " Priority=" << waitingTimePriority[i] << " Round Robin=" << waitingTimeRoundRobin[i] << endl;
    }

    // Calculate average waiting time
    double avgWaitingTimeFCFS = accumulate(waitingTimeFCFS, waitingTimeFCFS + n, 0.0) / n;
    double avgWaitingTimeSJF = accumulate(waitingTimeSJF, waitingTimeSJF + n, 0.0) / n;
    double avgWaitingTimePriority = accumulate(waitingTimePriority, waitingTimePriority + n, 0.0) / n;
    double avgWaitingTimeRoundRobin = accumulate(waitingTimeRoundRobin, waitingTimeRoundRobin + n, 0.0) / n;

    // Display average waiting times
    cout << "\nAverage Waiting Time:\n";
    cout << "FCFS=" << avgWaitingTimeFCFS << " SJF=" << avgWaitingTimeSJF
         << " Priority=" << avgWaitingTimePriority << " Round Robin=" << avgWaitingTimeRoundRobin << endl;

    return 0;
}
