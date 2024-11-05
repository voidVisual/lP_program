#include <iostream>
#include <vector>
#include <unordered_set>
#include <iomanip>

using namespace std;

void displayChart(const vector<vector<int>>& chart, int capacity) {
    cout << "\nPage Replacement Chart:\n";
    for (int i = 0; i < chart.size(); i++) {
        cout << "Page " << setw(2) << i + 1 << ": ";
        for (int j = 0; j < capacity; j++) {
            if (chart[i][j] == -1)
                cout << " - ";
            else
                cout << setw(2) << chart[i][j] << " ";
        }
        cout << "\n";
    }
}

void FIFOPageReplacement(const vector<int>& pages, int capacity) {
    unordered_set<int> s;
    vector<int> pageFrames(capacity, -1);
    vector<vector<int>> chart;

    int pageFaults = 0;
    int pageHits = 0;
    int index = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (s.find(pages[i]) == s.end()) {
            pageFaults++;

            if (s.size() == capacity) {
                s.erase(pageFrames[index]);
            }

            pageFrames[index] = pages[i];
            s.insert(pages[i]);

            index = (index + 1) % capacity;
        } else {
            pageHits++;
        }

        chart.push_back(pageFrames);
    }

    displayChart(chart, capacity);
    
    int totalReferences = pages.size();
    double hitRatio = static_cast<double>(pageHits) / totalReferences;
    double faultRatio = static_cast<double>(pageFaults) / totalReferences;

    cout << "\nTotal page faults: " << pageFaults << endl;
    cout << "Total page hits: " << pageHits << endl;
    cout << "Page hit ratio: " << hitRatio << endl;
    cout << "Page fault ratio: " << faultRatio << endl;
}

int main() {
    int numPages, capacity;
    
    cout << "Enter the number of pages: ";
    cin >> numPages;
    cout << "Enter the page frame capacity: ";
    cin >> capacity;

    vector<int> pages(numPages);
    cout << "Enter the page reference string:\n";
    for (int i = 0; i < numPages; i++) {
        cout << "Page " << i + 1 << ": ";
        cin >> pages[i];
    }

    FIFOPageReplacement(pages, capacity);

    return 0;
}