#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void displayFrames(vector<int>& frames) {
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i] == -1) cout << " - ";
        else cout << " " << frames[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, capacity, pageFaults = 0;

    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> capacity;

    vector<int> frames(capacity, -1);
    queue<int> q;

    cout << "\nRef String | Frames \n";
    cout << "-----------|---------\n";

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        
        // Check if page is already in frames (Page Hit)
        auto it = find(frames.begin(), frames.end(), currentPage);
        
        if (it == frames.end()) { // Page Fault
            // If frame is full, remove the oldest page from queue
            if (q.size() == capacity) {
                int oldest = q.front();
                q.pop();
                // Replace the oldest page in the frames vector
                auto itReplace = find(frames.begin(), frames.end(), oldest);
                *itReplace = currentPage;
            } else {
                // Fill the first available empty slot
                for (int j = 0; j < capacity; j++) {
                    if (frames[j] == -1) {
                        frames[j] = currentPage;
                        break;
                    }
                }
            }
            q.push(currentPage);
            pageFaults++;
            cout << "    " << currentPage << "      | ";
            displayFrames(frames);
        } else {
            // Page Hit
            cout << "    " << currentPage << "      | (Hit)" << endl;
        }
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << n - pageFaults << endl;

    return 0;
}