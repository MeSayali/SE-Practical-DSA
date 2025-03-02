#include <iostream>
using namespace std;

class Node {
public:
    int info;
    Node *left, *right;
    bool lthread, rthread; // Thread indicators for left and right
    
    Node(int key) {
        info = key;
        left = right = NULL;
        lthread = rthread = true; // Initially, threads are true
    }
};

class TBTree {
private:
    Node *root;

    // Function to find the inorder successor of a given node
    Node* inorderSuccessor(Node* ptr) {
        if (ptr->rthread) // If right thread exists, return right pointer
            return ptr->right;
        ptr = ptr->right;
        while (!ptr->lthread) // Move to the leftmost node
            ptr = ptr->left;
        return ptr;
    }

    // Function to find the inorder predecessor of a given node
    Node* inorderPredecessor(Node* ptr) {
        if (ptr->lthread) // If left thread exists, return left pointer
            return ptr->left;
        ptr = ptr->left;
        while (!ptr->rthread) // Move to the rightmost node
            ptr = ptr->right;
        return ptr;
    }

public:
    TBTree() { root = NULL; }
    
    void insert(int key);
    void inorder();
    void preorder();
    void deleteNode(int key);
};

void TBTree::insert(int ikey) {
    Node *ptr = root, *par = NULL;
    while (ptr != NULL) { // Traverse to find the correct position
        if (ikey == ptr->info) { // Duplicate key not allowed
            cout << "Duplicate Key\n";
            return;
        }
        par = ptr;
        if (ikey < ptr->info) { // Move left if smaller
            if (!ptr->lthread)
                ptr = ptr->left;
            else
                break;
        } else { // Move right if greater
            if (!ptr->rthread)
                ptr = ptr->right;
            else
                break;
        }
    }
    Node* tmp = new Node(ikey); // Create new node
    if (par == NULL) {
        root = tmp; // First node in tree
    } else if (ikey < par->info) { // Attach new node to left
        tmp->left = par->left;
        tmp->right = par;
        par->lthread = false;
        par->left = tmp;
    } else { // Attach new node to right
        tmp->left = par;
        tmp->right = par->right;
        par->rthread = false;
        par->right = tmp;
    }
}

void TBTree::inorder() {
    if (root == NULL) {
        cout << "Tree is empty\n";
        return;
    }
    Node* ptr = root;
    while (!ptr->lthread) // Move to the leftmost node
        ptr = ptr->left;
    
    while (ptr != NULL) { // Traverse inorder
        cout << ptr->info << " ";
        ptr = inorderSuccessor(ptr);
    }
    cout << "\n";
}

void TBTree::preorder() {
    if (root == NULL) {
        cout << "Tree is empty\n";
        return;
    }
    Node* ptr = root;
    while (ptr != NULL) {
        cout << ptr->info << " ";
        if (!ptr->lthread) // Move to left child if exists
            ptr = ptr->left;
        else if (!ptr->rthread) // Move to right child if exists
            ptr = ptr->right;
        else { // Move to next threaded node
            while (ptr != NULL && ptr->rthread)
                ptr = ptr->right;
            if (ptr != NULL)
                ptr = ptr->right;
        }
    }
    cout << "\n";
}

void TBTree::deleteNode(int key) {
    Node *ptr = root, *par = NULL;
    while (ptr != NULL) { // Find node to delete
        if (key == ptr->info)
            break;
        par = ptr;
        if (key < ptr->info) { // Move left if key is smaller
            if (!ptr->lthread)
                ptr = ptr->left;
            else
                return;
        } else { // Move right if key is greater
            if (!ptr->rthread)
                ptr = ptr->right;
            else
                return;
        }
    }
    if (ptr == NULL) {
        cout << "Key not found!\n";
        return;
    }
    
    if (!ptr->lthread && !ptr->rthread) { // Node has two children
        Node* succ = inorderSuccessor(ptr); // Find inorder successor
        ptr->info = succ->info; // Replace value
        deleteNode(succ->info); // Recursively delete successor
        return;
    }
    
    Node *child = (ptr->lthread) ? ptr->right : ptr->left; // Find child
    if (par == NULL) {
        root = child; // If deleting root node
    } else if (ptr == par->left) { // If node is left child
        par->left = child;
        par->lthread = ptr->lthread;
    } else { // If node is right child
        par->right = child;
        par->rthread = ptr->rthread;
    }
    if (!ptr->lthread) { // Update predecessor thread
        Node* pred = inorderPredecessor(ptr);
        pred->right = ptr->right;
    } else if (!ptr->rthread) { // Update successor thread
        Node* succ = inorderSuccessor(ptr);
        succ->left = ptr->left;
    }
    delete ptr; // Delete the node
}

int main() {
    TBTree tbt;
    int choice, key;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n2. Inorder Traversal\n3. Preorder Traversal\n4. Delete\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                tbt.insert(key);
                break;
            case 2:
                cout << "Inorder Traversal: ";
                tbt.inorder();
                break;
            case 3:
                cout << "Preorder Traversal: ";
                tbt.preorder();
                break;
            case 4:
                cout << "Enter key to delete: ";
                cin >> key;
                tbt.deleteNode(key);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}
