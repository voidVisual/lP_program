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
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void calculateSJF(vector<Process>& processes) {
    int n = processes.size();
    vector<bool> completed(n, false);
    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n) {
        int shortest_index = -1;
        int min_burst_time = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].burst_time < min_burst_time) {
                min_burst_time = processes[i].burst_time;
                shortest_index = i;
            }
        }

        if (shortest_index != -1) {
            current_time += processes[shortest_index].burst_time;
            processes[shortest_index].completion_time = current_time;
            processes[shortest_index].waiting_time = current_time - processes[shortest_index].arrival_time - processes[shortest_index].burst_time;
            processes[shortest_index].turnaround_time = current_time - processes[shortest_index].arrival_time;
            completed[shortest_index] = true;
            ++completed_count;
        } else {
            ++current_time;
        }
    }
}

void displayProcesses(const vector<Process>& processes) {
    cout << "\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (const auto& p : processes) {
        cout << setw(10) << p.id << "\t" << setw(10) << p.arrival_time << "\t" << setw(10) << p.burst_time << "\t"
             << setw(10) << p.waiting_time << "\t" << setw(10) << p.turnaround_time << "\t" << setw(10) << p.completion_time << "\n";
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
    }

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    calculateSJF(processes);

    displayProcesses(processes);

    calculateAverages(processes);

    return 0;
}