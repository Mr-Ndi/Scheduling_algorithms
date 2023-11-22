#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process
{
    int id;
    int priority;
    int burstTime;
    int arrivalTime;
};

struct ComparePriority
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.priority > p2.priority;
    }
};

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    priority_queue<Process, vector<Process>, ComparePriority> readyQueue;

    for (int i = 0; i < n; ++i)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter priority for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    int time = 0;
    double totalWaitingTime = 0.0;

    cout << "Preemptive Priority Scheduling Order: " << endl;
    while (!readyQueue.empty() || !processes.empty())
    {
        while (!processes.empty() && processes.front().arrivalTime <= time)
        {
            readyQueue.push(processes.front());
            processes.erase(processes.begin());
        }

        if (readyQueue.empty())
        {
            time++;
            continue;
        }

        Process current = readyQueue.top();
        readyQueue.pop();

        cout << "Executing Process " << current.id << " (Priority " << current.priority << ") for 1 unit." << endl;

        totalWaitingTime += (time - current.arrivalTime);
        current.burstTime--;

        if (current.burstTime > 0)
        {
            readyQueue.push(current);
        }

        time++;
    }

    double averageWaitingTime = totalWaitingTime / n;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    return 0;
}
