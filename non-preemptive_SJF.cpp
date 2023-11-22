#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

struct CompareRemainingTime
{
    bool operator()(const Process &a, const Process &b)
    {
        return a.remainingTime > b.remainingTime;
    }
};

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrivalTime < b.arrivalTime; });

    int time = 0;
    double totalWaitingTime = 0.0;

    cout << "Preemptive Shortest Job First Scheduling Order: " << endl;

    priority_queue<Process, vector<Process>, CompareRemainingTime> readyQueue;

    int i = 0;
    readyQueue.push(processes[i]);

    while (!readyQueue.empty())
    {
        Process current = readyQueue.top();
        readyQueue.pop();

        if (current.remainingTime == current.burstTime)
        {
            cout << "Process " << current.id << " starts execution at time " << time << endl;
        }

        current.remainingTime--;

        if (current.remainingTime > 0)
        {
            readyQueue.push(current);
        }
        else
        {
            cout << "Process " << current.id << " completes at time " << time + 1 << endl;
            totalWaitingTime += (time + 1 - current.arrivalTime - current.burstTime);
            i++;
            if (i < n)
            {
                while (i < n && processes[i].arrivalTime <= time + 1)
                {
                    readyQueue.push(processes[i]);
                    i++;
                }
            }
        }

        time++;
    }

    double averageWaitingTime = totalWaitingTime / n;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    return 0;
}
