#include<iostream>
#include<ios>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;

class employee{
    public:
        long int EID;
        char name[50];
        char designation[50];
        double salary;
};
class SequentialFile{
    public:
        string file = "filename.dat";
        employee emp;

        void readData();
        void addEmployee();
        void searchEmployee(string name);
        void updateEmployee(string name);
        void deleteEmployee(string name);
        void displayEmployee();


};

void SequentialFile::readData(){
    cout<<"enter the EID :: ";
    cin>>emp.EID;

    cin.ignore();
    cout<<"enter the name: ";
    cin.getline(emp.name, 50);

    cout<<"enter the designation : ";
    cin.getline(emp.designation, 50);
    
    cout<<"enter the salary : ";
    cin>>emp.salary;

    cout<<"data stored successfully !!!"<<endl;
}

void SequentialFile::addEmployee(){
    ofstream out(file, ios::binary | ios::app);

    readData();

    out.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    out.close();

    cout<<"add successfully!\n"<<endl;

    out.close();
    out.close();
}

void SequentialFile::displayEmployee(){
    ifstream in(file, ios::binary);
    if(!in){cout<<"file is Empty !";return;}
    
    cout<<left<<setw(10)<<"ID"<<setw(10)<<"NAME"<<setw(20)<<"designation"<<setw(10)<<"SALARY"<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;

    while(in.read(reinterpret_cast<char*>(&emp), sizeof(employee))){
        cout<<left<<setw(10)<<emp.EID<<setw(10)<<emp.name<<setw(20)<<emp.designation<<setw(10)<<emp.salary<<endl;
    }

    in.close();

}
void SequentialFile:: searchEmployee(string name){
    fstream in(file, ios::in | ios::binary);

    while(in.read(reinterpret_cast<char*>(&emp), sizeof(employee))){
        if(strcmp(emp.name, name.c_str()) == 0){
            cout<<"record found"<<endl;
            cout<<left<<setw(10)<<emp.EID<<setw(20)<<emp.name<<setw(20)<<emp.designation<<setw(20)<<emp.salary<<endl;
            return;
        }
    }
    cout<<"record not found"<<endl;
    
    return;

    in.close();
}

void SequentialFile::updateEmployee(string name){
    fstream inout(file, ios::in | ios::out | ios::binary);
    if(!inout){cout<<"file is empty";return;}
    
    while(inout.read(reinterpret_cast<char*>(&emp), sizeof(employee))){
        
        if(strcmp(emp.name, name.c_str()) == 0){
            readData();

            inout.seekp(-sizeof(emp), ios::cur);
            inout.write(reinterpret_cast<char*>(&emp), sizeof(employee));
            inout.close();
            cout<<"data upadted successfully\n"<<endl;
            return;
        }
    }
    cout<<"record Not found"<<endl;
    inout.close();
    return;
}

void SequentialFile::deleteEmployee(string name){
    fstream in(file, ios::in | ios::binary);

    fstream out("temp.dat", ios::out | ios:: binary);

    while(in.read(reinterpret_cast<char*>(&emp), sizeof(employee))){
        if(strcmp(emp.name, name.c_str()) != 0){
            out.write(reinterpret_cast<char*>(&emp), sizeof(employee));
        }
    }
    in.close();
    out.close();

    remove("filename.dat");
    rename("temp.dat", "filename.dat");
    return;
}

int main(){

    SequentialFile a;
    // a.addEmployee();
    
    // a.addEmployee();
    // a.addEmployee();

    // a.displayEmployee();
    // a.searchEmployee("pranav");
    // cout<<endl<<endl;
    // a.updateEmployee("pranav");
    // a.displayEmployee();
    
    // cout<<endl<<endl;
    
    a.deleteEmployee("ajay ");
    a.displayEmployee();
    
    return 0;
}