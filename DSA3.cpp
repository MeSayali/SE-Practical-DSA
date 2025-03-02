#include <iostream>
using namespace std;

class Node {
public:
    int info;
    Node *left, *right;
    bool lthread, rthread;
    
    Node(int key) {
        info = key;
        left = right = NULL;
        lthread = rthread = true;//not pointting to children but can be used as thread
    }
};

class TBTree {
private:
    Node *root;

    Node* inorderSuccessor(Node* ptr) {
        if (ptr->rthread)////if it is thread==true
            return ptr->right;//it will return it
        ptr = ptr->right;//if not move to right child
        while (!ptr->lthread)//if ptr is not lthread move to leftmost node
            ptr = ptr->left;
        return ptr;
    }

    Node* inorderPredecessor(Node* ptr) {
        if (ptr->lthread)
            return ptr->left;
        ptr = ptr->left;
        while (!ptr->rthread)
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
    while (ptr != NULL) {
        if (ikey == ptr->info) {
            cout << "Duplicate Key\n";
            return;
        }
        par = ptr;
        if (ikey < ptr->info) {
            if (!ptr->lthread)
                ptr = ptr->left;
            else
                break;
        } else {
            if (!ptr->rthread)
                ptr = ptr->right;
            else
                break;
        }
    }
    Node* tmp = new Node(ikey);
    if (par == NULL) {
        root = tmp;
    } else if (ikey < par->info) {
        tmp->left = par->left;
        tmp->right = par;
        par->lthread = false;
        par->left = tmp;
    } else {
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
    while (!ptr->lthread)
        ptr = ptr->left;
    
    while (ptr != NULL) {
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
        if (!ptr->lthread)
            ptr = ptr->left;
        else if (!ptr->rthread)
            ptr = ptr->right;
        else {
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
    while (ptr != NULL) {
        if (key == ptr->info)
            break;
        par = ptr;
        if (key < ptr->info) {
            if (!ptr->lthread)
                ptr = ptr->left;
            else
                return;
        } else {
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
    
    if (!ptr->lthread && !ptr->rthread) {
        Node* succ = inorderSuccessor(ptr);
        ptr->info = succ->info;
        deleteNode(succ->info);
        return;
    }
    
    Node *child = (ptr->lthread) ? ptr->right : ptr->left;
    if (par == NULL) {
        root = child;
    } else if (ptr == par->left) {
        par->left = child;
        par->lthread = ptr->lthread;
    } else {
        par->right = child;
        par->rthread = ptr->rthread;
    }
    if (!ptr->lthread) {
        Node* pred = inorderPredecessor(ptr);
        pred->right = ptr->right;
    } else if (!ptr->rthread) {
        Node* succ = inorderSuccessor(ptr);
        succ->left = ptr->left;
    }
    delete ptr;
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
