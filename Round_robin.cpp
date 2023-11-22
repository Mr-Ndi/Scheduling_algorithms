#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

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
    }

    int quantum; // Time quantum for Round Robin
    cout << "Enter the time quantum for Round Robin: ";
    cin >> quantum;

    int waitingTimeRoundRobin[n] = {0};
    calculateWaitingTimeRoundRobin(processes, waitingTimeRoundRobin, n, quantum);

    // Display waiting times
    cout << "\nWaiting Time for each process (Round Robin):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Process " << processes[i].id << ": Round Robin=" << waitingTimeRoundRobin[i] << endl;
    }

    // Calculate average waiting time
    double avgWaitingTimeRoundRobin = accumulate(waitingTimeRoundRobin, waitingTimeRoundRobin + n, 0.0) / n;
    cout << "\nAverage Waiting Time (Round Robin): " << avgWaitingTimeRoundRobin << endl;

    return 0;
}
