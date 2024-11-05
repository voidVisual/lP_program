#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int findOptimal(const vector<int>& pages, const vector<int>& frame, int index) {
    int farthest = index;
    int frame_index = -1;

    for (int i = 0; i < frame.size(); ++i) {
        int j;
        for (j = index; j < pages.size(); ++j) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    frame_index = i;
                }
                break;
            }
        }
        if (j == pages.size()) return i;
    }
    return frame_index;
}

void optimalPageReplacement(const vector<int>& pages, int frames) {
    vector<int> frame(frames, -1);
    int page_faults = 0;
    int page_hits = 0;

    cout << "Page Reference\tFrames\t\tPage Fault\n";
    for (int i = 0; i < pages.size(); ++i) {
        bool page_found = false;

        for (int j = 0; j < frames; ++j) {
            if (frame[j] == pages[i]) {
                page_found = true;
                page_hits++;
                break;
            }
        }

        if (!page_found) {
            page_faults++;

            bool replaced = false;
            for (int j = 0; j < frames; ++j) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    replaced = true;
                    break;
                }
            }

            if (!replaced) {
                int index_to_replace = findOptimal(pages, frame, i + 1);
                frame[index_to_replace] = pages[i];
            }

            cout << setw(12) << pages[i] << "\t";
            for (int k = 0; k < frames; ++k) {
                if (frame[k] == -1) cout << "- ";
                else cout << frame[k] << " ";
            }
            cout << "\tYes\n";
        } else {
            cout << setw(12) << pages[i] << "\t";
            for (int k = 0; k < frames; ++k) {
                if (frame[k] == -1) cout << "- ";
                else cout << frame[k] << " ";
            }
            cout << "\tNo\n";
        }
    }

    cout << "\nTotal Page Faults: " << page_faults << endl;
    cout << "Total Page Hits: " << page_hits << endl;

    double total_references = pages.size();
    double page_fault_ratio = static_cast<double>(page_faults) / total_references;
    double page_hit_ratio = static_cast<double>(page_hits) / total_references;

    cout << fixed << setprecision(2);
    cout << "Page Fault Ratio: " << page_fault_ratio << endl;
    cout << "Page Hit Ratio: " << page_hit_ratio << endl;
}

int main() {
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);

    for (int i = 0; i < n; ++i) {
        cout << "Enter page references "<<i+1<<":";
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames;

    optimalPageReplacement(pages, frames);

    return 0;
}