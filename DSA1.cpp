#include<iostream>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int current) {
        data = current;
        left = right = NULL;
    }
};

class Stack {
public:
    struct StackNode {
        Node* data;
        StackNode* next;
        StackNode(Node* node) : data(node), next(NULL) {}
    };

    StackNode* top; 

    Stack() : top(NULL) {}
    
    void push(Node* node) {
        StackNode* newNode = new StackNode(node);
        newNode->next = top;
        top = newNode;
    }
    Node* pop() {
        if (top == NULL) return NULL;
        StackNode* temp = top;
        top = top->next;
        Node* poppedNode = temp->data;
        delete temp;
        return poppedNode;
    }
    
    bool isEmpty() {
        return top == NULL;
    }
};

class Binary {
public:
    Node* root;

    Binary() {
        root = NULL;
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }
    void inorder() {
        inorder(root);
    }
    
    void preorder(Node* node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }
    void preorder() {
        preorder(root);
    }


    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    void postorder() {
        postorder(root);
    }
   
  void inorderNonRecursive() {
    if (root == NULL) return;//empty

    Stack stack;
    Node* current = root;

    while (current != NULL || !stack.isEmpty()) {
        while (current != NULL) {
            stack.push(current);
            current = current->left;
        }

        current = stack.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preorderNonRecursive() {
    if (root == NULL) return;

    Stack stack;
    stack.push(root);

    while (!stack.isEmpty()) {
        Node* current = stack.pop();
        cout << current->data << " ";

        if (current->right != NULL) {
            stack.push(current->right);
        }
        if (current->left != NULL) {
            stack.push(current->left);
        }
    }
}

void postorderNonRecursive() {
    if (root == NULL) return;

    Stack stack1, stack2;
    stack1.push(root);

    while (!stack1.isEmpty()) {
        Node* current = stack1.pop();
        stack2.push(current);

        if (current->left != NULL) {
            stack1.push(current->left);
        }
        if (current->right != NULL) {
            stack1.push(current->right);
        }
    }

    while (!stack2.isEmpty()) {
        cout << stack2.pop()->data << " ";
    }
}


    void swap(Node* node) {
        if (node == NULL) {
            return;
        }
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        swap(node->left);
        swap(node->right);
    }

    void swap() {
        swap(root);
    }

    int countLeaves(Node* node) {
        if (node == NULL) {
            return 0;
        }
        if (node->left == NULL && node->right == NULL) {
            return 1;
        }
        return countLeaves(node->left) + countLeaves(node->right);
    }

    int countLeaves() {
        return countLeaves(root);
    }

    int countInternalNodes(Node* node) {
        if (node == NULL) {
            return 0;
        }
        if (node->left != NULL || node->right != NULL) {
            return 1 + countInternalNodes(node->left) + countInternalNodes(node->right);
        }
        return 0;
    }

    int countInternalNodes() {
        return countInternalNodes(root);
    }
    int height(Node* node)
    {
    	if(node==NULL)
    	{
    		return 0;
		}
		
		int l_height=height(node->left);
		int r_height=height(node->right);
		
		if(l_height>=r_height)
		{
			return l_height+1;
		}
		else{
			return r_height+1;
		}
	}
    int height()
    {
    	return height(root);
	}
    Node* copy(Node* node) {
        if (node == NULL) {
            return NULL;
        }
        Node* newnode = new Node(node->data);
        newnode->left = copy(node->left);
        newnode->right = copy(node->right);
        return newnode;
    }

    Binary copy() {
        Binary newTree;
        newTree.root = copy(root);
        return newTree;
    }

    void insert(int value) {
        if (root == NULL) {
            root = new Node(value);
            return;
        }

        Node* current = root;
        while (true) {
            cout << "Where to add node with value " << value << " under Node " << current->data << ". Enter L (left) or R (right) to add: ";
            char choice;
            cin >> choice;

            choice = toupper(choice);

            if (choice == 'L') {
                if (current->left == NULL) {
                    current->left = new Node(value);
                    break;
                } else {
                    current = current->left;
                }
            } else if (choice == 'R') {
                if (current->right == NULL) {
                    current->right = new Node(value);
                    break;
                } else {
                    current = current->right;
                }
            } else {
                cout << "Invalid option, please enter a valid option (L or R)." << endl;
            }
        }
    }

    // Recursive method to erase all nodes
    void eraseRecursive(Node* node) {
        if (node == NULL) {
            return;
        }
        eraseRecursive(node->left);
        eraseRecursive(node->right);
        delete node;
    }

    void eraseRecursive() {
        eraseRecursive(root);
        root = NULL; 
    }

    void eraseNonRecursive() {
        if (root == NULL) {
            return;
        }

        Stack stack;
        stack.push(root);

        while (!stack.isEmpty()) {
            Node* current = stack.pop();

            // Push children nodes to stack
            if (current->right != NULL) {
                stack.push(current->right);
            }
            if (current->left != NULL) {
                stack.push(current->left);
            }

            // Delete the current node
            delete current;
        }

        root = NULL; // Set root to NULL after deletion
    }
};
int main() {
    Binary b;
    int choice;
    do {
        cout << "Binary Tree Menu:" << endl;
        cout << "1: Insertion" << endl;
        cout << "2: Inorder Traversal" << endl;
        cout << "3: Preorder Traversal" << endl;
        cout << "4: Postorder Traversal" << endl;
        cout << "5: Height" << endl;
        cout << "6: Swap Tree" << endl;
        cout << "7: Copied Tree" << endl;
        cout << "8: Count Leaves" << endl;
        cout << "9: Count Internal Nodes" << endl;
        cout << "10: Erase all nodes (Recursive)" << endl;
        cout << "11: Erase all nodes (Non-Recursive)" << endl;
        cout << "12: Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "Enter the value to insert: ";
                cin >> val;
                b.insert(val);
                break;
            }
            case 2: {
                cout << "Choose Traversal Method: 1 for Recursive, 2 for Non-Recursive: ";
                int method;
                cin >> method;
                if (method == 1) {
                    cout << "Inorder Traversal (Recursive): ";
                    b.inorder();
                } else if (method == 2) {
                    cout << "Inorder Traversal (Non-Recursive): ";
                    b.inorderNonRecursive();
                } else {
                    cout << "Invalid choice for traversal method." << endl;
                }
                cout << endl;
                break;
            }
            case 3: {
                cout << "Choose Traversal Method: 1 for Recursive, 2 for Non-Recursive: ";
                int method;
                cin >> method;
                if (method == 1) {
                    cout << "Preorder Traversal (Recursive): ";
                    b.preorder();
                } else if (method == 2) {
                    cout << "Preorder Traversal (Non-Recursive): ";
                    b.preorderNonRecursive();
                } else {
                    cout << "Invalid choice for traversal method." << endl;
                }
                cout << endl;
                break;
            }
            case 4: {
                cout << "Choose Traversal Method: 1 for Recursive, 2 for Non-Recursive: ";
                int method;
                cin >> method;
                if (method == 1) {
                    cout << "Postorder Traversal (Recursive): ";
                    b.postorder();
                } else if (method == 2) {
                    cout << "Postorder Traversal (Non-Recursive): ";
                    b.postorderNonRecursive();
                } else {
                    cout << "Invalid choice for traversal method." << endl;
                }
                cout << endl;
                break;
            }
            case 5:
                cout << "Height of tree is: " << b.height() << endl;
                break;
            case 6:
                b.swap();
                cout << "Tree after swap: ";
                b.inorder();
                cout << endl;
                break;
            case 7: {
                Binary copiedTree = b.copy();
                cout << "Copied Tree (Inorder Traversal): ";
                copiedTree.inorder();
                cout << endl;
                break;
            }
            case 8:
                cout << "Number of leaves: " << b.countLeaves() << endl;
                break;
            case 9:
                cout << "Number of internal nodes: " << b.countInternalNodes() << endl;
                break;
            case 10:
                b.eraseRecursive();
                cout << "All nodes have been erased recursively." << endl;
                break;
            case 11:
                b.eraseNonRecursive();
                cout << "All nodes have been erased non-recursively." << endl;
                break;
            case 12:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}

