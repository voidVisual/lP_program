#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void calculatePriorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int completed_count = 0;
    vector<bool> completed(n, false);

    while (completed_count < n) {
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }

        if (highest_priority_index != -1) {
            current_time += processes[highest_priority_index].burst_time;
            processes[highest_priority_index].completion_time = current_time;
            processes[highest_priority_index].waiting_time = current_time - processes[highest_priority_index].arrival_time - processes[highest_priority_index].burst_time;
            processes[highest_priority_index].turnaround_time = current_time - processes[highest_priority_index].arrival_time;
            completed[highest_priority_index] = true;
            ++completed_count;
        } else {
            ++current_time;
        }
    }
}

void displayProcesses(const vector<Process>& processes) {
    cout << "\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (const auto& p : processes) {
        cout << setw(10) << p.id << "\t" << setw(12) << p.arrival_time << "\t" << setw(9) << p.burst_time << "\t"
             << setw(8) << p.priority << "\t" << setw(12) << p.waiting_time << "\t" << setw(15) << p.turnaround_time
             << "\t" << setw(15) << p.completion_time << "\n";
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
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << processes[i].id << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << processes[i].id << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for Process " << processes[i].id << ": ";
        cin >> processes[i].priority;
    }

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    calculatePriorityScheduling(processes);
    displayProcesses(processes);
    calculateAverages(processes);

    return 0;
}