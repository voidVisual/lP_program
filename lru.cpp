#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <iomanip>

using namespace std;

void lruPageReplacement(const vector<int>& pages, int frames) {
    list<int> pageList;
    unordered_map<int, list<int>::iterator> pageMap;
    int page_faults = 0;
    int page_hits = 0;

    cout << "Page Reference\tFrames\tPage Fault\n";
    for (int page : pages) {
        if (pageMap.find(page) == pageMap.end()) {
            page_faults++;

            if (pageList.size() == frames) {
                int lru_page = pageList.back();
                pageList.pop_back();
                pageMap.erase(lru_page);
            }

            pageList.push_front(page);
            pageMap[page] = pageList.begin();

            cout << setw(12) << page << "\t";
            for (int p : pageList) {
                cout << p << " ";
            }
            for (int i = pageList.size(); i < frames; ++i) {
                cout << "- ";
            }
            cout << "\tYes\n";
        } else {
            page_hits++;
            pageList.erase(pageMap[page]);
            pageList.push_front(page);
            pageMap[page] = pageList.begin();

            cout << setw(12) << page << "\t";
            for (int p : pageList) {
                cout << p << " ";
            }
            for (int i = pageList.size(); i < frames; ++i) {
                cout << "- ";
            }
            cout << "\tNo\n";
        }
    }

    double hit_ratio = static_cast<double>(page_hits) / pages.size();
    double fault_ratio = static_cast<double>(page_faults) / pages.size();

    cout << "\nTotal Page Faults: " << page_faults << endl;
    cout << "Total Page Hits: " << page_hits << endl;
    cout << "Page Hit Ratio: " << fixed << setprecision(2) << hit_ratio * 100 << "%" << endl;
    cout << "Page Fault Ratio: " << fixed << setprecision(2) << fault_ratio * 100 << "%" << endl;
}

int main() {
    int n, frames;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    
    for (int i = 0; i < n; ++i) 
    {
        cout << "Enter page references " << i + 1 << ": ";
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames;

    lruPageReplacement(pages, frames);

    return 0;
}