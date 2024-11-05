#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void roundRobinScheduling(vector<Process>& processes, int time_quantum) {
    int n = processes.size();
    int current_time = 0;
    int completed_count = 0;
    queue<int> ready_queue;

    for (int i = 0; i < n; ++i) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
    }

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    ready_queue.push(0);
    vector<bool> in_queue(n, false);
    in_queue[0] = true;

    while (completed_count < n) {
        int index = ready_queue.front();
        ready_queue.pop();

        if (processes[index].remaining_time > time_quantum) {
            current_time += time_quantum;
            processes[index].remaining_time -= time_quantum;
        } else {
            current_time += processes[index].remaining_time;
            processes[index].remaining_time = 0;
            processes[index].completion_time = current_time;
            processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
            ++completed_count;
        }

        for (int i = 0; i < n; ++i) {
            if (!in_queue[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }

        if (processes[index].remaining_time > 0) {
            ready_queue.push(index);
        }

        if (ready_queue.empty()) {
            for (int i = 0; i < n; ++i) {
                if (processes[i].remaining_time > 0) {
                    ready_queue.push(i);
                    in_queue[i] = true;
                    break;
                }
            }
        }
    }
}

void displayProcesses(const vector<Process>& processes) {
    cout << "\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& p : processes) {
        cout << setw(10) << p.id << "\t" << setw(12) << p.arrival_time << "\t" << setw(9) << p.burst_time << "\t"
             << setw(15) << p.completion_time << "\t" << setw(12) << p.waiting_time << "\t" << setw(15) << p.turnaround_time << "\n";
    }
}

void calculateAverages(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }

    float avg_waiting_time = static_cast<float>(total_waiting_time) / processes.size();
    float avg_turnaround_time = static_cast<float>(total_turnaround_time) / processes.size();

    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

int main() {
    int n, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << processes[i].id << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << processes[i].id << ": ";
        cin >> processes[i].burst_time;
    }

    roundRobinScheduling(processes, time_quantum);

    displayProcesses(processes);

    calculateAverages(processes);

    return 0;
}