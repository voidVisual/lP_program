#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void calculateWaitingTime(vector<Process>& processes) {
    processes[0].waiting_time = 0;

    for (int i = 1; i < processes.size(); ++i) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void calculateTurnaroundTime(vector<Process>& processes) {
    for (int i = 0; i < processes.size(); ++i) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        processes[i].completion_time = processes[i].arrival_time + processes[i].turnaround_time;
    }
}

void displayProcesses(const vector<Process>& processes) {
    cout << "\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (const auto& p : processes) {
        cout << setw(10) << p.id << "\t" << setw(12) << p.arrival_time << "\t" << setw(9) << p.burst_time << "\t"
             << setw(12) << p.waiting_time << "\t" << setw(15) << p.turnaround_time << "\t" << setw(15) << p.completion_time << "\n";
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

    stable_sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    calculateWaitingTime(processes);
    calculateTurnaroundTime(processes);
    displayProcesses(processes);
    calculateAverages(processes);

    return 0;
}