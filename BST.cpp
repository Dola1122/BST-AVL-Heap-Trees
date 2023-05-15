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
Node* addStudent(BST r){
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
    r.root= r.insert(r.root,Id,name,gpa,department);
    cout<<"The student is added."<<endl;
    return r.root;

}


Node* removeStudent(BST Btree){
    int id;
    cout << "ID: "<<endl;
    cin >> id;

    if(Btree.search(id)){
        cout<<"Student is found."<<endl;
        Node* result = Btree.search(Btree.root,id);
        cout<<"["<<result->id<<", "<<result->name<<", "<<result->gpa<<", "<<result->department<<"]"<<endl;
        Node* result2 = Btree.Delete(Btree.root,id);
        return result2;
        cout<<"Student is deleted."<<endl;

    }
    else{
        cout<<"Student is not found."<<endl;
    }
}
void searchUsingBST(BST Btree){
    int id;
    cout << "ID: "<<endl;
    cin >> id;
    if(Btree.search(id)){
        cout<<"Student is found."<<endl;
        Node* result = Btree.search(Btree.root,id);
        cout<<"["<<result->id<<", "<<result->name<<", "<<result->gpa<<", "<<result->department<<"]"<<endl;
    }
    else{
        cout<<"Student is not found."<<endl;
    }
}

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

void printUsingBST(BST Btree){
    Btree.inorder(Btree.root);
    cout<<"Students per Departments:"<<endl;
    cout<<"CS " <<countDepartment(Btree.root,"CS")<<" students"<<endl;
    cout<<"IT " <<countDepartment(Btree.root,"IT")<<" students"<<endl;
    cout<<"DS " <<countDepartment(Btree.root,"DS")<<" students"<<endl;
    cout<<"IS " <<countDepartment(Btree.root,"IS")<<" students"<<endl;



}

int main(){
    string filename = "students.txt";
    BST Btree;
    Btree.root=Btree.readFile();
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
                Btree.root=addStudent(Btree);
                break;
            case 2:
                Btree.root= removeStudent(Btree);
                break;
            case 3:
                searchUsingBST(Btree);
                break;
            case 4:
                printUsingBST(Btree);
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);


}


