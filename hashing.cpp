#include <iostream>
#include <string>

#define BSIZE 10 // Increased size for better demonstration

using namespace std;

struct Client {
    long int telephoneNo;
    string name;
};

class TelephoneDirectory {
private:
    Client LPHashTable[BSIZE];
    Client QPHashTable[BSIZE];

public:
    TelephoneDirectory() {
        for (int i = 0; i < BSIZE; i++) {
            LPHashTable[i].telephoneNo = -1;
            QPHashTable[i].telephoneNo = -1;
        }
    }

    // Linear Probing: h(k, i) = (hash(k) + i) % size
    void insertRecordLP(long int tel, string n) {
        int index = tel % BSIZE;
        for (int i = 0; i < BSIZE; i++) {
            int newIndex = (index + i) % BSIZE;
            if (LPHashTable[newIndex].telephoneNo == -1) {
                LPHashTable[newIndex] = {tel, n};
                return;
            }
        }
        cout << "Linear Probing Table is full!" << endl;
    }

    void searchRecordLP(long int tel) {
        int index = tel % BSIZE;
        int noc = 0;
        for (int i = 0; i < BSIZE; i++) {
            noc++;
            int newIndex = (index + i) % BSIZE;
            if (LPHashTable[newIndex].telephoneNo == tel) {
                cout << "Found: " << LPHashTable[newIndex].name << " after " << noc << " comparison(s)." << endl;
                return;
            }
            if (LPHashTable[newIndex].telephoneNo == -1) break; 
        }
        cout << "Record not found! Comparisons: " << noc << endl;
    }

    // Quadratic Probing: h(k, i) = (hash(k) + i^2) % size
    void insertRecordQP(long int tel, string n) {
        int index = tel % BSIZE;
        for (int i = 0; i < BSIZE; i++) {
            int newIndex = (index + (i * i)) % BSIZE;
            if (QPHashTable[newIndex].telephoneNo == -1) {
                QPHashTable[newIndex] = {tel, n};
                return;
            }
        }
        cout << "Quadratic Probing Table could not find a slot!" << endl;
    }

    void searchRecordQP(long int tel) {
        int index = tel % BSIZE;
        int noc = 0;
        for (int i = 0; i < BSIZE; i++) {
            noc++;
            int newIndex = (index + (i * i)) % BSIZE;
            if (QPHashTable[newIndex].telephoneNo == tel) {
                cout << "Found: " << QPHashTable[newIndex].name << " after " << noc << " comparison(s)." << endl;
                return;
            }
            if (QPHashTable[newIndex].telephoneNo == -1) break;
        }
        cout << "Record not found! Comparisons: " << noc << endl;
    }

    void display(bool isLP) {
        cout << "\nIndex\tPhone\t\tName" << endl;
        for (int i = 0; i < BSIZE; i++) {
            Client c = isLP ? LPHashTable[i] : QPHashTable[i];
            if (c.telephoneNo != -1)
                cout << i << "\t" << c.telephoneNo << "\t" << c.name << endl;
            else
                cout << i << "\t--- EMPTY ---" << endl;
        }
    }
};

int main() {
    TelephoneDirectory td;
    int choice, subChoice;
    long int tel;
    string name;

    do {
        cout << "\n--- TELEPHONE DIRECTORY HASHING ---";
        cout << "\n1. Insert Record\n2. Display Records\n3. Search Record\n4. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Phone & Name: ";
                cin >> tel >> name;
                td.insertRecordLP(tel, name);
                td.insertRecordQP(tel, name);
                break;
            case 2:
                cout << "1. LP Table  2. QP Table: ";
                cin >> subChoice;
                td.display(subChoice == 1);
                break;
            case 3:
                cout << "Enter Phone to search: ";
                cin >> tel;
                cout << "\n[Linear Probing Results]: ";
                td.searchRecordLP(tel);
                cout << "[Quadratic Probing Results]: ";
                td.searchRecordQP(tel);
                break;
        }
    } while (choice != 4);

    return 0;
}