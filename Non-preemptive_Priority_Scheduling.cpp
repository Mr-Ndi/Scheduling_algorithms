#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int priority;
    int burstTime;
    int arrivalTime;
};

int main() {
    int n;
    cout << "\n\n\tEnter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "\n\n";
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "\t\tEnter priority for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
        cout << "\t\t\tEnter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout<<"------------------------------------------------"<<endl;
    }

    int time = 0;
    double totalWaitingTime = 0.0;

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    cout << "Non-Preemptive Priority Scheduling Order: " << endl;
    for (int i = 0; i < n; ++i) {
        if (time < processes[i].arrivalTime) {
            time = processes[i].arrivalTime;
        }

        cout << "Executing Process " << processes[i].id << " (Priority " << processes[i].priority << ") for " << processes[i].burstTime << " units. Waiting Time: " << (time - processes[i].arrivalTime) << endl;

        totalWaitingTime += (time - processes[i].arrivalTime) + processes[i].burstTime;
        time += processes[i].burstTime;
    }

    double averageWaitingTime = totalWaitingTime / n;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    return 0;
}
