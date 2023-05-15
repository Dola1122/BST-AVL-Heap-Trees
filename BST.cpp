#include <bits/stdc++.h>
using namespace std;
class Node{
public:
    int id;
    double gpa;
    string name;
    string department;
    Node*left;
    Node*right;

    Node(int ID,string Name,double GPA,string Department){
        id= ID;
        name= Name;
        gpa= GPA;
        department= Department;
        left= NULL;
        right=NULL;
    }
};
class BST{
public:
    Node*root;
    BST(){
        root=NULL;
    }
    Node* insert(Node* r, int ID, string Name,double GPA, string Department){
        if(r==NULL){
            Node* newNode=new Node(ID,Name,GPA,Department);
            r= newNode;
        }
        else if(ID < r->id){
            r->left=insert(r->left,ID,Name,GPA,Department);
        }
        else{
            r->right=insert(r->right,ID,Name,GPA,Department);
        }
        return r;
    }
    void insert(int ID,string Name,double GPA, string Department){
        root= insert(root,ID,Name,GPA,Department);
    }
    void inorder(Node* r){
        if(r==NULL){
            return;
        }
        inorder(r->left);
        cout<<"["<< r->id <<", "<<r->name <<", "<<r->gpa <<", "<<r->department<<"]"<<endl;
        inorder(r->right);
    }

    Node* search(Node*r , int key){
        if(r==NULL){
            return NULL;
        }
        else if(r->id == key){
            return r;
        }
        else if(key < r->id){
            search(r->left,key);
        }
        else if(key > r->id){
            search(r->right,key);
        }
    }
    bool search(int key){
        Node* result= search(root,key);
        if(result==NULL){
            return false;
        }
        else{
            return true;
        }
    }
    Node* findMin(Node* r){
        if(r==NULL){
            return NULL;
        }
        else if(r->left==NULL){
            return r;
        }
        else {
            findMin(r->left);
        }
    }
    Node* findMax(Node* r){
        if(r==NULL){
            return NULL;
        }
        else if(r->right==NULL){
            return r;
        }
        else{
            findMax(r->right);
        }
    }
    Node* Delete(Node* r, int ID) {
        if (r == NULL) {
            return NULL;
        }
        if (ID < r->id) {
            r->left = Delete(r->left, ID);
        }
        else if (ID > r->id) {
            r->right = Delete(r->right, ID);
        }
        else {
            if (r->left == NULL && r->right == NULL) {
                delete r;
                return NULL;
            }
            else if (r->left == NULL) {
                Node* temp = r->right;
                delete r;
                return temp;
            }
            else if (r->right == NULL) {
                Node* temp = r->left;
                delete r;
                return temp;
            }
            else {
                // Find the maximum node in the left subtree
                Node* maxNode = r->left;
                while (maxNode->right != NULL) {
                    maxNode = maxNode->right;
                }
                // Copy the data from the max node into the node to be deleted
                r->id = maxNode->id;
                r->name = maxNode->name;
                r->gpa = maxNode->gpa;
                r->department = maxNode->department;
                // Delete the max node from the left subtree
                r->left = Delete(r->left, maxNode->id);
            }
        }
        return r;
    }

    Node* readFile(){
        BST bst;
        ifstream infile("students.txt");
        int num_students;
        infile >> num_students;
        string line;
        getline(infile, line); // consume newline after num_students
        for (int i = 0; i < num_students; i++) {
            int ID; string Department, Name; double Gpa;
            infile >> ID;
            getline(infile, line); // read and discard line separator
            getline(infile, Name);
            infile >> Gpa;
            getline(infile, line); // read and discard newline after gpa
            getline(infile, Department);
            bst.insert(ID,Name,Gpa,Department);

        }
        infile.close();
        return bst.root;
    }

};
void changeFirstLineValue(string filename, int new_value) {
    ifstream infile(filename);
    vector<string> buffer;
    string line;
    getline(infile, line);
    int current_value = stoi(line);
    buffer.push_back(to_string(new_value));
    while (getline(infile, line)) {
        buffer.push_back(line);
    }
    infile.close();
    ofstream outfile(filename);
    for (string& line : buffer) {
        outfile << line << endl;
    }
    outfile.close();
}


void writeToFile(int ID, string Name, double GPA, string Department) {
    ofstream outfile("students.txt", ios::app);
    outfile << ID<<endl;
    outfile <<Name<<endl;
    outfile <<GPA<<endl;
    outfile <<Department<<endl;
    ifstream infile("students.txt");
    outfile.close();
    //update the number of students
    int num_students;
    infile >> num_students;
    num_students++;
    changeFirstLineValue("students.txt", num_students);
    infile.close();
}

void addStudent(){
    int Id;
    string name,department;
    double gpa;
    cout<<"ID: "<<endl;
    cin>>Id;
    cout<<"Name: "<<endl;
    cin>>name;
    cout<<"GPA: "<<endl;
    cin>>gpa;
    cout<<"Department: "<<endl;
    cin>>department;
    writeToFile(Id, name, gpa, department);
    cout<<"The student is added."<<endl;

}
void removeById(string filename, int id) {
    vector<string> lines;
    ifstream infile(filename);
    string line;
    getline(infile, line);
    lines.push_back(line); // Store the number of students in the first line
    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        int student_id = stoi(line);
        if (student_id == id) {
            // Skip the next three lines to remove the student's data
            getline(infile, line); // name
            getline(infile, line); // gpa
            getline(infile, line); // department
        } else {
            lines.push_back(line);
            getline(infile, line); // name
            lines.push_back(line);
            getline(infile, line); // gpa
            lines.push_back(line);
            getline(infile, line); // department
            lines.push_back(line);
        }
    }
    infile.close();
    ofstream outfile(filename);
    for (string& line : lines) {
        outfile << line << endl;
    }
    outfile.close();
    ifstream in("students.txt");
    int num_students;
    in >> num_students;
    num_students--;
    changeFirstLineValue("students.txt", num_students);
    in.close();
}

void removeStudent(){
    int id;
    cout << "ID: "<<endl;
    cin >> id;
    BST Btree;
    Btree.root = Btree.readFile();
    if(Btree.search(id)){
        cout<<"Student is found."<<endl;
        Node* result = Btree.search(Btree.root,id);
        cout<<"["<<result->id<<", "<<result->name<<", "<<result->gpa<<", "<<result->department<<"]"<<endl;
        removeById("students.txt", id);
        cout<<"Student is deleted."<<endl;

    }
    else{
        cout<<"Student is not found."<<endl;
    }


}
void searchUsingBST(){
    int id;
    cout << "ID: "<<endl;
    cin >> id;
    BST Btree;
    Btree.root = Btree.readFile();
    if(Btree.search(id)){
        cout<<"Student is found."<<endl;
        Node* result = Btree.search(Btree.root,id);
        cout<<"["<<result->id<<", "<<result->name<<", "<<result->gpa<<", "<<result->department<<"]"<<endl;
    }
    else{
        cout<<"Student is not found."<<endl;
    }
}
//int countDepartment(Node* r,string Department){
//    int counter=0;
//    if(r==NULL){
//        return counter;
//    }
//    countDepartment(r->left,Department);
//    if(r->department == Department){
//        counter++;
//    }
//    countDepartment(r->right,Department);
//    return counter;
//
//}
int countDepartment(Node* r, string Department) {
    if (r == NULL) {
        return 0;
    }
    int counter = 0;
    if (r->department == Department) {
        counter++;
    }
    counter += countDepartment(r->left, Department);
    counter += countDepartment(r->right, Department);
    return counter;
}

void printUsingBST(){
    BST Btree;
    Btree.root = Btree.readFile();
    Btree.inorder(Btree.root);
    cout<<"Students per Departments:"<<endl;
    cout<<"CS " <<countDepartment(Btree.root,"CS")<<" students"<<endl;
    cout<<"IT " <<countDepartment(Btree.root,"IT")<<" students"<<endl;
    cout<<"DS " <<countDepartment(Btree.root,"DS")<<" students"<<endl;
    cout<<"IS " <<countDepartment(Btree.root,"IS")<<" students"<<endl;



}
int main(){
    string filename = "students.txt";
    int choice;
    do {
        cout << "1. Add student" << endl;
        cout << "2. Remove student" << endl;
        cout << "3. Search student" << endl;
        cout << "4. Print all (sorted by id)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: "<<endl;
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                removeStudent();
                break;
            case 3:
                searchUsingBST();
                break;
            case 4:
                printUsingBST();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    cout<<"Doneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"<<endl;

}


