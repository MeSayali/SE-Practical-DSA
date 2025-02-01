#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string keyword;
    string meaning;
    Node* left;
    Node* right;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = NULL;
    }
};

class Stack {
public:
    class StackNode {
    public:
        StackNode* next;
        Node* data;

        StackNode(Node* value) {
            next = NULL;
            data = value;
        }
    };

    StackNode* top;

public:
    Stack() { 
        top = NULL; 
    }

    void push(Node* value) {
        StackNode* newnode = new StackNode(value);
        newnode->next = top;
        top = newnode;
    }

    Node* pop() {
        if (top == NULL) {
            cout << "Stack underflow!" << endl;
            return NULL;
        }

        StackNode* temp = top;
        top = top->next;
        Node* result = temp->data;
        delete temp;
        return result;
    }

    bool isEmpty() { 
        return top == NULL; 
    }
};

class DictionaryBST {
public:
    Node* root;

    DictionaryBST() { 
        root = NULL; 
    }

    // Recursive insertion (unchanged)
    Node* addKeyword(Node* node, string keyword, string meaning) {
        if (node == NULL) return new Node(keyword, meaning);

        if (keyword < node->keyword)
            node->left = addKeyword(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = addKeyword(node->right, keyword, meaning);
        else
            cout << "Keyword already exists!" << endl;
        
        return node;
    }

    // Wrapper function for insertion
    void addKeyword(string keyword, string meaning) {
        root = addKeyword(root, keyword, meaning);
    }

    // Recursive helper for updating meaning (unchanged)
    bool updateMeaning(Node* node, string keyword, string newMeaning) {
        if (node == NULL) return false;
        
        if (keyword == node->keyword) {
            node->meaning = newMeaning;
            return true;
        } else if (keyword < node->keyword) {
            return updateMeaning(node->left, keyword, newMeaning);
        } else {
            return updateMeaning(node->right, keyword, newMeaning);
        }
    }

    // Wrapper function for updating meaning
    void updateMeaning(string keyword, string newMeaning) {
        if (updateMeaning(root, keyword, newMeaning))
            cout << "Meaning updated successfully!" << endl;
        else
            cout << "Keyword not found!" << endl;
    }

    // Calculate the height of the BST (unchanged)
    int calculateHeight(Node* node) {
        if (node == NULL) return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    void findMaxComparisons() {
        cout << "Maximum comparisons required: " << calculateHeight(root) << endl;
    }

    // In-order traversal for ascending order display
    void ascending() {
        Stack s;
        Node* current = root;
        while (current != nullptr || !s.isEmpty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.pop();
            if (current != NULL) {
                cout << current->keyword << " ";
                current = current->right;
            }
        }
        cout << endl;
    }

    // In-order traversal in reverse for descending order display
    void descending() {
        Stack s;
        Node* current = root;
        while (current != NULL || !s.isEmpty()) {
            while (current != NULL) {
                s.push(current);
                current = current->right;
            }
            current = s.pop();
            if (current != NULL) {
                cout << current->keyword << " ";
                current = current->left;
            }
        }
        cout << endl;
    }

    // Find the minimum node (used for deletion with two children)
    Node* findMinimum(Node* node) {
        while (node && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

   
    void deletion(string keyword) {
        if (root == NULL) {
            cout << "Tree is empty!" << endl;
            return;
        }
        
        Node* parent = NULL;
        Node* current = root;
        
        //Find the node to delete and its parent.
        while (current != NULL && current->keyword != keyword) {
            parent = current;
            if (keyword < current->keyword)
                current = current->left;
            else
                current = current->right;
        }
        
        // If node not found, print a message and return.
        if (current == NULL) {
            cout << "Keyword not found!" << endl;
            return;
        }
        
        // 2. Case 1: Node to delete is a leaf (no children).
        if (current->left == NULL && current->right == NULL) {
            if (current == root) {
                root = NULL;
            } else if (parent->left == current) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
            delete current;
        }
        // 3. Case 2: Node to delete has one child.
        else if (current->left == NULL || current->right == NULL) {
            Node* child = (current->left != NULL) ? current->left : current->right;
            if (current == root) {
                root = child;
            } else if (parent->left == current) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            delete current;
        }
        // 4. Case 3: Node to delete has two children.
        else {
            // Find the in-order successor (the smallest node in the right subtree).
            Node* successorParent = current;
            Node* successor = current->right;
            while (successor->left != NULL) {
                successorParent = successor;
                successor = successor->left;
            }
            // Replace current node's data with the successor's data.
            current->keyword = successor->keyword;
            current->meaning = successor->meaning;
            // Remove the successor node.
            if (successorParent->left == successor)
                successorParent->left = successor->right;
            else
                successorParent->right = successor->right;
            delete successor;
        }
        cout << "Node deleted successfully!" << endl;
    }
    // ------------------------------------------------------------

    // Recursive search helper function (unchanged)
    Node* search(Node* node, string keyword) {
        if (node == NULL || node->keyword == keyword)
            return node;
        if (keyword < node->keyword)
            return search(node->left, keyword);
        else
            return search(node->right, keyword);
    }

    // Wrapper for searching a keyword.
    void searchKeyword(string keyword) {
        Node* result = search(root, keyword);
        if (result != NULL)
            cout << "Keyword: " << result->keyword << " | Meaning: " << result->meaning << endl;
        else
            cout << "Keyword not found!" << endl;
    }
};

int main() {
    DictionaryBST dictionary;
    int choice;
    string keyword, meaning;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Display in Ascending Order\n";
        cout << "3. Display in Descending Order\n";
        cout << "4. Update Meaning\n";
        cout << "5. Find Maximum Comparisons (Height of Tree)\n";
        cout << "6. Delete Keyword (Non-Recursive)\n";
        cout << "7. Search for a Keyword\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cin.ignore();  // Clear newline from input buffer
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dictionary.addKeyword(keyword, meaning);
                break;

            case 2:
                cout << "\nDictionary in Ascending Order:\n";
                dictionary.ascending();
                break;

            case 3:
                cout << "\nDictionary in Descending Order:\n";
                dictionary.descending();
                break;

            case 4:
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cin.ignore();
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dictionary.updateMeaning(keyword, meaning);
                break;

            case 5:
                dictionary.findMaxComparisons();
                break;

            case 6:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                dictionary.deletion(keyword);
                cout << "\nDictionary after deletion (Ascending Order):\n";
                dictionary.ascending();
                break;

            case 7:
                cout << "Enter keyword to search: ";
                cin >> keyword;
                dictionary.searchKeyword(keyword);
                break;

            case 8:
                cout << "Exiting program!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 8);

    return 0;
}
