#include "AVL.cpp"
#include "BST.cpp"
#include "Heap.cpp"

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
        cout << "Enter your choice: "<<endl;
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                StartBSTMenu();
                break;
            case 2:
                StartAVLMenu();
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
}