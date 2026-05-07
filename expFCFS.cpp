#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
};

// Sort processes by arrival time to ensure FCFS order
bool compareArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    cout << "Enter total number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << p[i].id << ": ";
        cin >> p[i].arrivalTime >> p[i].burstTime;
    }

    // Step 1: Sort by Arrival Time
    sort(p.begin(), p.end(), compareArrival);

    // Step 2: Calculate Times
    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        // If CPU is idle until the next process arrives
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;
        }
        
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;

        currentTime = p[i].completionTime;
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnAroundTime;
    }

    // Step 3: Display Results
    cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].arrivalTime << "\t" << p[i].burstTime << "\t" 
             << p[i].completionTime << "\t" << p[i].turnAroundTime << "\t" << p[i].waitingTime << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    return 0;
}