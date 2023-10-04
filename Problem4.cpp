/*The program asks the user to specify the record
number. More likely than not, a user has no way of knowing the record
number. Write a program that asks the user for the name of an
employee, finds the record with that name, and displays the
record. Then the program should give the following options
to the user:
• Change the salary of this record
• View the next record
• Find another employee
• Quit
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Worker {
    string name;
    double salary;
};

int main(){
    ifstream inputFile("WorkerRecords.txt");
    if (!inputFile) {
        cout << "Error." << endl;
        return 1;
    }
    vector<Worker> workers;

    Worker tempWorker;

    while(inputFile >> tempWorker.name >> tempWorker.salary) {
        workers.push_back(tempWorker);
    }

    inputFile.close();

    int currentRecord = -1;
    string targetName;

    while(true) {
        // cin.ignore();
        cout << "Enter the name of an employee or 'q' to exit): ";
        getline(cin, targetName);

        if (targetName == "q"){
            break;
        }

        targetName.erase(targetName.find_first_not_of(" \t\n\r\f\v"), targetName.find_last_not_of(" \t\n\r\f\v") + 1);


        bool found = false;
        for (int i = 0; i < workers.size(); i++) {
            if (workers[i].name == targetName) {
                currentRecord = i;
                found = true;
                break;
            }
        }

        if(found) {
            // Display the record
            cout << "Name: " << workers[currentRecord].name << endl;
            cout << "Salary: $" << workers[currentRecord].salary << endl;

            // Offer options to the user
            int choice;
            cout << "Options:" << endl;
            cout << "1. Change the salary of this record" << endl;
            cout << "2. View the next record" << endl;
            cout << "3. Find another employee" << endl;
            cout << "4. Quit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            // Implement the chosen option
            switch (choice) {
                case 1:
                    cout << "Enter the new salary: $";
                    cin >> workers[currentRecord].salary;
                    cout << "Salary updated." << endl;
                    break;
                case 2:
                    currentRecord++;
                    if (currentRecord < workers.size()) {
                        cout << "Next record:" << endl;
                        cout << "Name: " << workers[currentRecord].name << endl;
                        cout << "Salary: $" << workers[currentRecord].salary << endl;
                    } else {
                        cout << "No more records." << endl;
                    }
                    break;
                case 3:
                    currentRecord = -1; // Reset current record
                    break;
                case 4:
                    return 0; // Quit the program
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } else {
            cout << "Employee not found." << endl;
        }
    }

    // Update the file with the modified records if needed
    ofstream outputFile("WorkerRecords.txt");
    if (!outputFile) {
        cout << "Error opening the file for writing." << endl;
        return 1;
    }

    for (const Worker& worker : workers) {
        outputFile << worker.name << " " << worker.salary << endl;
    }
    outputFile.close();

    return 0;
    }