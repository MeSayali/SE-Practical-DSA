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
        if (ptr->rthread)//if it is thread==true
            return ptr->right;//it will return it
        
        ptr = ptr->right;//if not move to right child
        while (!ptr->lthread)//if ptr is not lthread move to leftmost node
            ptr = ptr->left;
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
    while (ptr != NULL) {//to find insertion point
        if (ikey == ptr->info) {
            cout << "Duplicate Key\n";
            return;
        }
        par = ptr;//parent=current child
        if (ikey < ptr->info) {
            if (!ptr->lthread)//if it is false
                ptr = ptr->left;//move to left
            else
                break;//if left is thread  then break
        } else {
            if (!ptr->rthread)
                ptr = ptr->right;
            else
                break;
        }
    }
    //inserting node
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

int main() {
    TBTree tbt;
    tbt.insert(20);
    tbt.insert(10);
    tbt.insert(30);
    tbt.insert(5);
    tbt.insert(15);
    tbt.insert(25);
    tbt.insert(35);
    
    cout << "Inorder Traversal: ";
    tbt.inorder();
    
    cout << "Preorder Traversal: ";
    tbt.preorder();
    
    return 0;
}
