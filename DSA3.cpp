#include <iostream>
using namespace std;

// Node class for Threaded BST
class Node {
public:
    int key;
    Node *left, *right;
    bool isThreaded; // True if right pointer is a thread

    Node(int k) {
        key = k;
        left = right = nullptr;
        isThreaded = false;
    }
};

// Threaded BST class
class ThreadedBST {
private:
    Node *root;

public:
    ThreadedBST() {
        root = nullptr;
    }

    // Insert a new node into TBT
    void insert(int key) {
        Node *parent = nullptr, *curr = root;

        while (curr != nullptr) {
            parent = curr;
            if (key < curr->key) {
                if (curr->left == nullptr)
                    break;
                curr = curr->left;
            } else {
                if (curr->isThreaded)
                    break;
                curr = curr->right;
            }
        }

        Node *newNode = new Node(key);
        if (parent == nullptr) {
            root = newNode;
        } else if (key < parent->key) {
            parent->left = newNode;
            newNode->right = parent;
            newNode->isThreaded = true;
        } else {
            newNode->right = parent->right;
            parent->right = newNode;
            parent->isThreaded = false;
            newNode->isThreaded = true;
        }
    }

    // Inorder Traversal (Non-Recursive)
    void inorder() {
        Node *curr = root;
        while (curr && curr->left) {
            curr = curr->left;
        }

        while (curr) {
            cout << curr->key << " ";
            if (curr->isThreaded)
                curr = curr->right;
            else {
                curr = curr->right;
                while (curr && curr->left)
                    curr = curr->left;
            }
        }
        cout << endl;
    }

    // Preorder Traversal (Non-Recursive)
    void preorder() {
        Node *curr = root;
        while (curr) {
            cout << curr->key << " ";

            if (curr->left) {
                curr = curr->left;
            } else {
                while (curr && curr->isThreaded) {
                    curr = curr->right;
                    if (curr)
                        cout << curr->key << " ";
                }
                if (curr)
                    curr = curr->right;
            }
        }
        cout << endl;
    }

    // Delete a node from TBT
    void deleteNode(int key) {
        Node *parent = nullptr, *curr = root;

        while (curr != nullptr) {
            if (curr->key == key)
                break;
            parent = curr;
            if (key < curr->key) {
                curr = curr->left;
            } else {
                if (curr->isThreaded)
                    break;
                curr = curr->right;
            }
        }

        if (curr == nullptr) {
            cout << "Key not found!" << endl;
            return;
        }

        if (curr->left == nullptr && (curr->right == nullptr || curr->isThreaded)) {
            if (parent == nullptr)
                root = nullptr;
            else if (parent->left == curr)
                parent->left = nullptr;
            else
                parent->right = curr->right;
            delete curr;
        } else if (curr->left == nullptr || (!curr->isThreaded && curr->right == nullptr)) {
            Node *child = (curr->left != nullptr) ? curr->left : curr->right;
            if (parent == nullptr)
                root = child;
            else if (parent->left == curr)
                parent->left = child;
            else
                parent->right = child;
            delete curr;
        } else {
            Node *successor = curr->right;
            Node *succParent = curr;
            while (successor->left) {
                succParent = successor;
                successor = successor->left;
            }
            curr->key = successor->key;
            if (succParent->left == successor)
                succParent->left = successor->right;
            else
                succParent->right = successor->right;
            delete successor;
        }
    }

    // Menu for user interaction
    void menu() {
        int choice, value;
        do {
            cout << "\n------ Threaded Binary Search Tree Menu ------\n";
            cout << "1. Insert a Node\n";
            cout << "2. Inorder Traversal (Non-Recursive)\n";
            cout << "3. Preorder Traversal (Non-Recursive)\n";
            cout << "4. Delete a Node\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> value;
                    insert(value);
                    break;
                case 2:
                    cout << "Inorder Traversal: ";
                    inorder();
                    break;
                case 3:
                    cout << "Preorder Traversal: ";
                    preorder();
                    break;
                case 4:
                    cout << "Enter value to delete: ";
                    cin >> value;
                    deleteNode(value);
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 5);
    }
};

// Driver Code
int main() {
    ThreadedBST tbt;
    tbt.menu();
    return 0;
}
