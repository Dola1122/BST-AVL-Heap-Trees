#include <iostream>

using namespace std;


class Student {
private:
    int id;
    string name;
    double gpa;
    string department;

public:
    Student(int studentId,  string studentName, double studentGpa,  string studentDepartment)
            : id(studentId), name(studentName), gpa(studentGpa), department(studentDepartment) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    double getGpa() const {
        return gpa;
    }

    string getDepartment() const {
        return department;
    }

    void setId(int studentId) {
        id = studentId;
    }

    void setName(const string& studentName) {
        name = studentName;
    }

    void setGpa(double studentGpa) {
        gpa = studentGpa;
    }

    void setDepartment(const string& studentDepartment) {
        department = studentDepartment;
    }
};
void displayBSTMenu() {
    cout << "((Second Menu - choice 1 BST))" << endl;
    cout << "Choose one of the following options:" << endl;
    cout << "1. Add student" << endl;
    cout << "2. Remove student" << endl;
    cout << "3. Search student" << endl;
    cout << "4. Print All (sorted by ID)" << endl;
    cout << "5. Return to main menu" << endl;
}

void displayAVLMenu() {
    cout << "((Second Menu - choice 2 AVL))" << endl;
    cout << "Choose one of the following options:" << endl;
    cout << "1. Add student" << endl;
    cout << "2. Remove student" << endl;
    cout << "3. Search student" << endl;
    cout << "4. Print All (sorted by ID)" << endl;
    cout << "5. Return to main menu" << endl;
}

void displayMinHeapMenu() {
    cout << "((Second Menu - choice 3 Min Heap))" << endl;
    cout << "Choose one of the following options:" << endl;
    cout << "1. Add student" << endl;
    cout << "2. Print All (sorted by GPA)" << endl;
    cout << "3. Return to main menu" << endl;
}

void displayMaxHeapMenu() {
    cout << "((Second Menu - choice 4 Max Heap))" << endl;
    cout << "Choose one of the following options:" << endl;
    cout << "1. Add student" << endl;
    cout << "2. Print All (sorted by GPA)" << endl;
    cout << "3. Return to main menu" << endl;
}

int main() {
    int mainChoice, subChoice;

    do {
        cout << "((First Menu - Main menu))" << endl;
        cout << "Choose Data Structure:" << endl;
        cout << "1. BST" << endl;
        cout << "2. AVL" << endl;
        cout << "3. Min Heap" << endl;
        cout << "4. Max Heap" << endl;
        cout << "5. Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                do {
                    displayBSTMenu();
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            // Add student logic for BST
                            break;
                        case 2:
                            // Remove student logic for BST
                            break;
                        case 3:
                            // Search student logic for BST
                            break;
                        case 4:
                            // Print all students sorted by ID for BST
                            break;
                        case 5:
                            // Return to main menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (subChoice != 5);
                break;
            case 2:
                do {
                    displayAVLMenu();
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            // Add student logic for AVL
                            break;
                        case 2:
                            // Remove student logic for AVL
                            break;
                        case 3:
                            // Search student logic for AVL
                            break;
                        case 4:
                            // Print all students sorted by ID for AVL
                            break;
                        case 5:
                            // Return to main menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (subChoice != 5);
                break;
            case 3:
                do {
                    displayMinHeapMenu();
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            // Add student logic for Min Heap
                            break;
                        case 2:
                            // Print all students sorted by GPA for Min Heap
                            break;
                        case 3:
                            // Return to main menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (subChoice != 3);
                break;
            case 4:
                do {
                    displayMaxHeapMenu();
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            // Add student logic for Max Heap
                            break;
                        case 2:
                            // Print all students sorted by GPA for Max Heap
                            break;
                        case 3:
                            // Return to main menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (subChoice != 3);
                break;
            case 5:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (mainChoice != 5);

    return 0;
}

