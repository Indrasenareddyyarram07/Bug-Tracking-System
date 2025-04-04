#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Bug {
    int id;
    string title;
    string description;
    string status;
};

void addBug() {
    ofstream file("bugs.txt", ios::app);
    Bug bug;
    cout << "Enter Bug ID: ";
    cin >> bug.id;
    cin.ignore();
    cout << "Enter Bug Title: ";
    getline(cin, bug.title);
    cout << "Enter Bug Description: ";
    getline(cin, bug.description);
    bug.status = "Open";
    file << bug.id << "," << bug.title << "," << bug.description << "," << bug.status << endl;
    file.close();
    cout << "Bug reported successfully!\n";
}

void viewBugs() {
    ifstream file("bugs.txt");
    if (!file) {
        cout << "No bug reports found.\n";
        return;
    }
    string line;
    cout << "\nBug Reports:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void updateBugStatus() {
    ifstream file("bugs.txt");
    if (!file) {
        cout << "No bug reports found.\n";
        return;
    }
    vector<Bug> bugs;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Bug bug;
        getline(ss, line, ',');
        bug.id = stoi(line);
        getline(ss, bug.title, ',');
        getline(ss, bug.description, ',');
        getline(ss, bug.status, ',');
        bugs.push_back(bug);
    }
    file.close();
    
    int id;
    cout << "Enter Bug ID to update: ";
    cin >> id;
    bool found = false;
    for (auto &bug : bugs) {
        if (bug.id == id) {
            cout << "Enter new status (Open/In Progress/Resolved): ";
            cin.ignore();
            getline(cin, bug.status);
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Bug ID not found.\n";
        return;
    }
    
    ofstream outFile("bugs.txt");
    for (const auto &bug : bugs) {
        outFile << bug.id << "," << bug.title << "," << bug.description << "," << bug.status << endl;
    }
    outFile.close();
    cout << "Bug status updated successfully!\n";
}

int main() {
    int choice;
    do {
        cout << "\nBug Tracking System\n";
        cout << "1. Report a Bug\n";
        cout << "2. View All Bugs\n";
        cout << "3. Update Bug Status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: addBug(); break;
            case 2: viewBugs(); break;
            case 3: updateBugStatus(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    return 0;
}
