#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

/////////////// Student Class //////////////
class Student {
private:
    int id;
    string name;
    double gpa;
    string department;

public:
    Student(int studentId, string studentName, double studentGpa, string studentDepartment)
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

    void setName(const string &studentName) {
        name = studentName;
    }

    void setGpa(double studentGpa) {
        gpa = studentGpa;
    }

    void setDepartment(const string &studentDepartment) {
        department = studentDepartment;
    }
};
////////////////////////////////////////////



/////////////// Main Menus ///////////////

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
/////////////////////////////////////////////////////



////////////////////  Max Heap  /////////////////////

class MaxHeap {

private:
    vector<Student> students;

public:
    MaxHeap() {
        loadStudents("heap.txt");
    }

    void loadStudents(string filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
        }

        int numStudents;
        file >> numStudents;

        // Ignore the newline char
        file.ignore();

        for (int i = 0; i < numStudents; i++) {
            int id;
            string name;
            double gpa;
            string department;

            // student ID
            string idString;
            if (!getline(file, idString)) {
                cout << "Error parsing student ID!" << endl;
            }
            id = stoi(idString);

            // student name
            if (!getline(file, name)) {
                cout << "Error parsing student name!" << endl;
            }

            // student GPA
            string gpaString;
            if (!getline(file, gpaString)) {
                cout << "Error parsing student GPA!" << endl;
            }
            gpa = stod(gpaString);

            // student department
            if (!getline(file, department)) {
                cout << "Error parsing student department!" << endl;
            }

            addStudent(Student(id, name, gpa, department));
        }

        file.close();

    }

    void maxHeapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && students[left].getGpa() > students[largest].getGpa()) {
            largest = left;
        }

        if (right < n && students[right].getGpa() > students[largest].getGpa()) {
            largest = right;
        }

        if (largest != i) {
            swap(students[i], students[largest]);
            maxHeapify(n, largest);
        }
    }

    void buildMaxHeap() {
        int n = students.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            maxHeapify(n, i);
        }
    }

    void printHeap() {
        // sort the students
        maxHeapSort();

        // Print the students
        for (Student student: students) {
            cout << "ID: " << setw(3) << student.getId() << ", Name: " << setw(18) << student.getName() << ", GPA: "
                 << setw(6) << fixed << setprecision(2) << student.getGpa() << ", Department: "
                 << student.getDepartment()
                 << endl;
        }
    }

    void maxHeapSort() {
        if (students.empty()) {
            return;
        }

        int n = students.size();

        buildMaxHeap();

        for (int i = n - 1; i > 0; i--) {
            swap(students[0], students[i]);
            maxHeapify(i, 0);
        }
    }

    void addStudent(Student student) {
        students.push_back(student); // Add the new student to the end of the vector

        int index = students.size() - 1; // Index of the newly added student

        // Perform the swim-up operation to maintain the max heap property
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (students[index].getGpa() > students[parentIndex].getGpa()) {
                swap(students[index], students[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }


};

/////////////////////////////////////////////////////



///////////////////  Min Heap  //////////////////////

class MinHeap {

private:
    vector<Student> students;

public:
    MinHeap() {
        loadStudents("heap.txt");
    }

    void loadStudents(string filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
        }

        int numStudents;
        file >> numStudents;

        // Ignore the newline char
        file.ignore();

        for (int i = 0; i < numStudents; i++) {
            int id;
            string name;
            double gpa;
            string department;

            // student ID
            string idString;
            if (!getline(file, idString)) {
                cout << "Error parsing student ID!" << endl;
            }
            id = stoi(idString);

            // student name
            if (!getline(file, name)) {
                cout << "Error parsing student name!" << endl;
            }

            // student GPA
            string gpaString;
            if (!getline(file, gpaString)) {
                cout << "Error parsing student GPA!" << endl;
            }
            gpa = stod(gpaString);

            // student department
            if (!getline(file, department)) {
                cout << "Error parsing student department!" << endl;
            }

            addStudent(Student(id, name, gpa, department));
        }

        file.close();

    }

    void minHeapify(int n, int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && students[left].getGpa() < students[smallest].getGpa()) {
            smallest = left;
        }

        if (right < n && students[right].getGpa() < students[smallest].getGpa()) {
            smallest = right;
        }

        if (smallest != i) {
            swap(students[i], students[smallest]);
            minHeapify(n, smallest);
        }
    }

    void buildMaxHeap() {
        int n = students.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            minHeapify(n, i);
        }
    }

    void printHeap() {
        // sort the students
        minHeapSort();

        // Print the students
        for (Student student: students) {
            cout << "ID: " << setw(3) << student.getId() << ", Name: " << setw(18) << student.getName() << ", GPA: "
                 << setw(6) << fixed << setprecision(2) << student.getGpa() << ", Department: "
                 << student.getDepartment()
                 << endl;
        }
    }

    void minHeapSort() {
        if (students.empty()) {
            return;
        }

        int n = students.size();

        buildMaxHeap();

        for (int i = n - 1; i > 0; i--) {
            swap(students[0], students[i]);
            minHeapify(i, 0);
        }
    }

    void addStudent(Student student) {
        students.push_back(student); // Add the new student to the end of the vector

        int index = students.size() - 1; // Index of the newly added student

        // Perform the swim-up operation to maintain the max heap property
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (students[index].getGpa() > students[parentIndex].getGpa()) {
                swap(students[index], students[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }


};

/////////////////////////////////////////////////////
void minHeap() {
    MinHeap minHeap = MinHeap();
    int subChoice;
    do {
        displayMinHeapMenu();
        cout << "Enter your choice: ";
        cin >> subChoice;

        switch (subChoice) {
            case 1: {
                // Add student logic for Max Heap
                int id;
                string name;
                double gpa;
                string department;

                cout << "Enter student ID: ";
                cin >> id;
                cin.ignore(); // Ignore the newline character

                cout << "Enter student name: ";
                getline(cin, name);

                cout << "Enter student GPA: ";
                cin >> gpa;

                cout << "Enter student department: ";
                cin >> department;

                minHeap.addStudent(Student(id, name, gpa, department));
                cout << "\nStudent added successfully!" << endl;

                break;
            }
            case 2:
                // Print all students sorted by GPA for Max Heap
                minHeap.printHeap();
                break;
            case 3:
                // Return to main menu
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (subChoice != 3);
}


void maxHeap() {
    MaxHeap maxHeap = MaxHeap();
    int subChoice;
    do {
        displayMaxHeapMenu();
        cout << "Enter your choice: ";
        cin >> subChoice;

        switch (subChoice) {
            case 1: {
                // Add student logic for Max Heap
                int id;
                string name;
                double gpa;
                string department;

                cout << "Enter student ID: ";
                cin >> id;
                cin.ignore(); // Ignore the newline character

                cout << "Enter student name: ";
                getline(cin, name);

                cout << "Enter student GPA: ";
                cin >> gpa;

                cout << "Enter student department: ";
                cin >> department;

                maxHeap.addStudent(Student(id, name, gpa, department));
                cout << "\nStudent added successfully!" << endl;

                break;
            }
            case 2:
                // Print all students sorted by GPA for Max Heap
                maxHeap.printHeap();
                break;
            case 3:
                return;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (subChoice != 3);
}



/////////////////// Main ///////////////////

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
                minHeap();
                break;
            case 4:
                maxHeap();
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

