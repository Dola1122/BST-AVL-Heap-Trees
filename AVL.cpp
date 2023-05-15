#include <iostream>
#include <fstream>

using namespace std;
struct Student {
    string Fname;
    string Lname;
    string department;
    double gpa;
    int id;

    Student() = default;

    Student(string Fname, string Lname , string department, double gpa, int id) {
        this->Fname = Fname;
        this->Lname = Lname;
        this->department = department;
        this->gpa = gpa;
        this->id = id;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AVLNode{
    Student student;
    AVLNode *left;
    AVLNode *right;
    int height;
    AVLNode(Student student){
        this->student = student;
        left = right = nullptr;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int height(AVLNode* node) {
    if (!node) {
        return 0;
    }
    int left_height = height(node->left);
    int right_height = height(node->right);
    return max(left_height, right_height) + 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void displayAVLMenu(){
    cout <<"-------------------------------------------------------------\n";
    cout << "Choose one of the following options:\n"
            "-------------------------------------------------------------\n"
            "1. Add student\n"
            "2. Remove student\n"
            "3. Search student\n"
            "4. Print All (sorted by id)\n"
            "5. Return to main menu\n"
            "Enter number of option:\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AVLNode* rightRotate(AVLNode* node) {
    AVLNode* newRoot = node->left;
    AVLNode* tmp = newRoot->right;

    newRoot->right = node;
    node->left = tmp;

    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AVLNode* leftRotate(AVLNode* node) {
    AVLNode* newRoot = node->right;
    AVLNode* tmp = newRoot->left;

    newRoot->left = node;
    node->right = tmp;

    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getBalance(AVLNode* root) {
    if (!root) {
        return 0;
    }
    return height(root->left) - height(root->right);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AVLNode* balanceTree(AVLNode* root) {
    int balance = getBalance(root);

    // Left-Left case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left-Right case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-Right case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right-Left case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Student enterStudent(){
    string Fname, Lname , department , id , gpa;
    cout << "id:";
    cin >> id;
    cout << "Name:";
    cin >> Fname >> Lname;
    cout << "GPA:";
    cin >> gpa;
    cout << "Department:";
    cin >> department;

    int ID = stoi(id);
    float GPA = stof(gpa);
    Student student(Fname, Lname, department, GPA, ID);
    return student;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AVLNode* insertStudent(AVLNode* root, Student student) {
    AVLNode* node = new AVLNode(student);
    if (!root) {
        return node;
    }

    if (student.id < root->student.id) {
        root->left = insertStudent(root->left, student);
    } else if (student.id > root->student.id) {
        root->right = insertStudent(root->right, student);
    } else {
        return node;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    return balanceTree(root);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loadStudentsFromFile( AVLNode*& root){
    fstream StudentFile;
    StudentFile.open("AVLStudentTree.txt" , ios::in);
    int ID;
    float GPA;
    if(root == nullptr) {
        if (StudentFile.is_open()) {
            // This to get the number of students in the file, and it is not included in the tree.
            int numberOfStudents;
            StudentFile >> numberOfStudents;
            while (!StudentFile.eof()) {
                string Fname, Lname, department, id, gpa;
                StudentFile >> id >> Fname >> Lname >> gpa >> department;
                try {
                    ID = stoi(id);
                    GPA = stof(gpa);
                }
                    // This is for handling invalid arguments
                catch (const std::invalid_argument &e) {
                    continue;
                }
                Student student(Fname, Lname, department, GPA, ID);
                root = insertStudent(root, student);
            }
        }
        else {
            cout << "File not found" << endl;
            return;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




AVLNode*& searchForStudent(AVLNode*& root, int id){
    if(!root){
        return root;
    }
    if(root->student.id == id){
        cout << "Student found:" << endl;
        cout << root->student.id << " " <<  root->student.Fname << " " << root->student.Lname << " " << root->student.gpa << " " << root->student.department << " " <<   endl;
        cout << "-----------------------------------\n";
        return root;
    }
    if(root->student.id > id){
        return searchForStudent(root->left , id);
    }
    else{
        return searchForStudent(root->right , id);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool inOrder(AVLNode* root) {
    if (!root) {
        return false;
    }
    inOrder(root->left);
    cout << root->student.id << " " <<  root->student.Fname << " " << root->student.Lname << " " << root->student.gpa << " " << root->student.department << " " <<   endl;
    inOrder(root->right);
    return true;
}
//function to balance the tree


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool deleteStudent(AVLNode*& root , int id)
{AVLNode*& nodeToDelete = searchForStudent(root , id);
    if (!nodeToDelete) {
        cout << "Student not found" << endl;
        return false;
    }
    if(nodeToDelete->left == nullptr && nodeToDelete->right == nullptr){
        delete nodeToDelete;
        nodeToDelete = nullptr;
        return true;
    }
    else if(nodeToDelete->left == nullptr){
        AVLNode* tmp = nodeToDelete;
        nodeToDelete = nodeToDelete->right;
        delete tmp;
        return true;
    }
    else if(nodeToDelete->right == nullptr){
        AVLNode* tmp = nodeToDelete;
        nodeToDelete = nodeToDelete->left;
        delete tmp;
        return true;
    }
    else{
        AVLNode* tmp = nodeToDelete->right;
        while(tmp->left != nullptr){
            tmp = tmp->left;
        }
        nodeToDelete->student = tmp->student;

        return deleteStudent(nodeToDelete->right , tmp->student.id);
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    AVLNode* root = nullptr;
    loadStudentsFromFile(root);

    while (true) {
        displayAVLMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                Student student = enterStudent();
                root = insertStudent(root, student);
                cout << "Student added successfully\n";
                break;
            }
            case 2: {
                cout << "Enter student id:";
                int id;
                cin >> id;
                if (deleteStudent(root , id))
                    cout << "Student deleted successfully\n";


                break;
            }
            case 3: {
                cout << "Enter student id:";
                int id;
                cin >> id;
                if(!searchForStudent(root , id)){
                    cout << "Student not found\n";
                }
                break;
            }
            case 4: {
                if (!inOrder(root)) {
                    cout << "No students found\n";
                }
                break;
            }
            case 5: {
                // Return to main menu
                exit(0);  // it will be changed to return to main menu
                break;
            }
            default: {
                cout << "Invalid choice\n";
                break;
            }
        }
    }
}
