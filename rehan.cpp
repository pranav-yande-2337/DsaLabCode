#include<iostream>
#include<fstream>
#include<iomanip>
#include<limits>
#include<cstring>
#define MAX 20
using namespace std;

typedef struct Employee{
     int EID;
     string name;
     string designation;
     float salary;
}EMP;

class SequentialFile
{
private:
    EMP eObj;

public:
    void readData();
    void displayData();
    void insertRecord();
    void updateRecord(string name);
    void searchRecord(string name);
    void deleteRecord();
    void displayRecords();
};

void SequentialFile::readData(){
    cout<<"\nEnter Employee ID::";
    cin>>eObj.EID;

    cout<<"\nEnter Employee Name::";
    cin>>eObj.name;

    cout<<"\nEnter Employee Designation::";
    cin>>eObj.designation;

    cout<<"\nEnter Employee Salary::";
    cin>>eObj.salary;
}

void SequentialFile::displayData(){
    cout<<"\nEnter Employee ID::"<<eObj.EID;
    cout<<"\nEnter Employee Name::"<<eObj.name;
    cout<<"\nEnter Employee Designation::"<<eObj.designation;
    cout<<"\nEnter Employee Salary::"<<eObj.salary;
}

void SequentialFile::insertRecord(){
    fstream fout;
    fout.open("employee3.txt",ios::app | ios::binary);
    readData();
    fout.write((char*)&eObj,sizeof(eObj));
    fout.close();
}

void SequentialFile::displayRecords(){    
    fstream fin;
    fin.open("employee3.txt", ios::in | ios::binary);

    while(fin.read((char*)&eObj,sizeof(eObj))){
        cout<<"\n"<<eObj.EID<<setw(15)<<eObj.name<<setw(15)<<eObj.designation<<setw(15)<<eObj.salary;
    }

    fin.close();
}

void SequentialFile::searchRecord(string name){
    fstream in;
    EMP obj;   
    in.open("employee1.txt",ios::in | ios::binary);

    while(in.read((char*) &obj,sizeof(obj))){
        if (obj.name == name) {
            cout<<"\nRecord Found";
            cout<<"\n"<<obj.EID<<setw(15)<<obj.name<<setw(15)<<obj.designation<<setw(15)<<obj.salary;
            return;
        }
    }

    cout<<"\nRecord not found";
    in.close();
}

void SequentialFile::updateRecord(string name){
    fstream inout;
    EMP obj;  
    int count=0;

    inout.open("employee1.txt",ios::in | ios::out | ios::binary);

    while(inout.read((char*) &obj,sizeof(obj))){
        count++;
        if (obj.name == name) {
            cout<<"\nRecord Found";
            cout<<"\n"<<obj.EID<<setw(15)<<obj.name<<setw(15)<<obj.designation<<setw(15)<<obj.salary;

            readData();

            inout.seekp(sizeof(obj)*(count-1),ios::beg);   
            inout.write((char*)&obj,sizeof(obj));          
            return;
        }
    }

    inout.close();
}

void SequentialFile::deleteRecord(){   
}

int main(){
    SequentialFile sf;
    int choice;
    string name;

    do{
        cout<<"\n1.Insert\n2.Display\n3.Search\n4.Update\n5.Exit\nEnter choice:";
        cin>>choice;

        switch(choice){
            case 1: sf.insertRecord(); break;
            case 2: sf.displayRecords(); break;
            case 3:
                cout<<"\nEnter name to search:";
                cin>>name;
                sf.searchRecord(name);
                break;
            case 4:
                cout<<"\nEnter name to update:";
                cin>>name;
                sf.updateRecord(name);
                break;
        }

    }while(choice != 5);

    return 0;
}