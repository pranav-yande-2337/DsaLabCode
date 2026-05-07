#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

// Shared variables
atomic<bool> flag[2] = { false, false };
atomic<int> turn(0);

void criticalSection(int id) {
    // We simulate the process trying to enter multiple times
    for (int i = 0; i < 2; ++i) {
        int other = 1 - id;

        // --- ENTRY SECTION ---
        flag[id] = true;           // "I want to enter"
        turn = other;              // "But I'll let you go first"

        // Wait while the other process wants to enter AND it's their turn
        while (flag[other] && turn == other) {
            // Busy waiting (spinning)
        }

        // --- CRITICAL SECTION ---
        cout << ">>> Process " << id << " has entered the Critical Section." << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // Simulate work
        cout << "<<< Process " << id << " is leaving the Critical Section." << endl;

        // --- EXIT SECTION ---
        flag[id] = false;          // "I am finished"

        // --- REMAINDER SECTION ---
        this_thread::sleep_for(chrono::milliseconds(100)); 
    }
}

int main() {
    cout << "Starting Peterson's Algorithm Simulation..." << endl;

    // Create two threads representing Process 0 and Process 1
    thread p0(criticalSection, 0);
    thread p1(criticalSection, 1);

    // Wait for both to finish
    p0.join();
    p1.join();

    cout << "Simulation Complete." << endl;
    return 0;
}
