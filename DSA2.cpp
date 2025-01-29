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
        left = NULL;
        right = NULL;
    }
};

class Stack {
public:
    class StackNode {
    public:
        StackNode* next;
        Node* data;

        StackNode(Node* value) {
            next = nullptr;
            data = value;
        }
    };

    StackNode* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(Node* value) {
        StackNode* newnode = new StackNode(value);
        newnode->next = top;
        top = newnode;
    }

    Node* pop() {
        if (top == nullptr) {
            cout << "Stack underflow!" << endl;
            return nullptr;
        }

        StackNode* temp = top;
        top = top->next;
        Node* result = temp->data;
        delete temp;
        return result;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

class DictionaryBST {
public:
    Node* root;

    DictionaryBST() {
        root = NULL;
    }

    Node* addKeyword(Node* node, string keyword, string meaning) {
        if (node == NULL) {
            return new Node(keyword, meaning);
        }
        if (keyword < node->keyword) {
            node->left = addKeyword(node->left, keyword, meaning);
        } else if (keyword > node->keyword) {
            node->right = addKeyword(node->right, keyword, meaning);
        } else {
            cout << "Keyword already exists!" << endl;
        }
        return node;
    }

    void addKeyword(string keyword, string meaning) {
        root = addKeyword(root, keyword, meaning);
    }

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

    void updateMeaning(string keyword, string newMeaning) {
        if (updateMeaning(root, keyword, newMeaning)) {
            cout << "Meaning updated successfully!" << endl;
        } else {
            cout << "Keyword not found!" << endl;
        }
    }

    int calculateHeight(Node* node) {
        if (node == NULL) return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    void findMaxComparisons() {
        cout << "Maximum comparisons required: " << calculateHeight(root) << endl;
    }

    void ascending() {
        Stack s;
        Node* current = root;
        while (current != nullptr || !s.isEmpty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.pop();
            cout << current->keyword << " ";
            current = current->right;
        }
        cout << endl;
    }

    void descending() {
        Stack s;
        Node* current = root;
        while (current != NULL || !s.isEmpty()) {
            while (current != NULL) {
                s.push(current);
                current = current->right;
            }
            current = s.pop();
            cout << current->keyword << " ";
            current = current->left;
        }
        cout << endl;
    }

    Node* findMinimum(Node* node) {
        while (node && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    void deletion(string keyword) {
        root = deletion(root, keyword, nullptr);
    }

 Node* deletion(Node* root, string keyword, Node* parent) {
        if (root == NULL) {
            cout << "Keyword not found!" << endl;
            return root;
        }

        if (keyword < root->keyword) {
            root->left = deletion(root->left, keyword, root);
        } else if (keyword > root->keyword) {
            root->right = deletion(root->right, keyword, root);
        } else {//leaf node
            if (root->left == NULL && root->right == NULL) {
                if (root != this->root) {
                    if (parent->left == root) parent->left = NULL;
                    else parent->right = NULL;
                } else {
                    this->root = NULL;
                }
                delete root;
            }
            else if (root->left && root->right) {
                Node* successor = findMinimum(root->right);
                root->keyword = successor->keyword;
                root->meaning = successor->meaning;
                root->right = deletion(root->right, successor->keyword, root);
            }
            else
            {
                Node* child = (root->left) ? root->left : root->right;
                if (root != this->root) {
                    if (root == parent->left) parent->left = child;
                    else parent->right = child;
                } else {
                    this->root = child;
                }
                delete root;
            }
        }
        return root;
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
        cout << "6. Delete Keyword\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin >> meaning;
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
                cout << "Enter new meaning: ";
                cin >> meaning;
                dictionary.updateMeaning(keyword, meaning);
                break;

            case 5:
                dictionary.findMaxComparisons();
                break;

            case 6:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                dictionary.deletion(keyword);
                break;

            case 7:
                cout << "Exiting program!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 7);

    return 0;
}
