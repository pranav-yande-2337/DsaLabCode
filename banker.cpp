#include <iostream>
#include <vector>

using namespace std;

int main() {
    // P = Number of processes, R = Number of resources
    int P, R;
    cout << "Enter number of processes: ";
    cin >> P;
    cout << "Enter number of resources: ";
    cin >> R;

    vector<int> available(R);
    vector<vector<int>> max(P, vector<int>(R));
    vector<vector<int>> allocation(P, vector<int>(R));
    vector<vector<int>> need(P, vector<int>(R));

    cout << "Enter Available Resources: ";
    for (int i = 0; i < R; i++) cin >> available[i];

    cout << "Enter Maximum Demand Matrix:\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) cin >> max[i][j];

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) cin >> allocation[i][j];

    // Step 1: Calculate Need Matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Step 2: Safety Algorithm
    vector<bool> finish(P, false);
    vector<int> safeSequence(P);
    vector<int> work = available;
    int count = 0;

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) break;
                }

                if (j == R) { // If all needs can be met
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT in a safe state (Deadlock possible).";
            return 0;
        }
    }

    cout << "\nSystem is in a SAFE STATE.\nSafe Sequence: ";
    for (int i = 0; i < P; i++) {
        cout << "P" << safeSequence[i] << (i == P - 1 ? "" : " -> ");
    }
    cout << endl;

    return 0;
}