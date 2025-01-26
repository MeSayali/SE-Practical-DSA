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
        if (keyword < node->keyword) {//keyword is small than currents keyword.
            node->left = addKeyword(node->left, keyword, meaning);
        } else if (keyword > node->keyword) {//if large than current's keyword.
            node->right = addKeyword(node->right, keyword, meaning);
        } else {
            cout << "Keyword already exists!" << endl;
        }
        return node;
    }
    
    
    void addKeyword(string keyword, string meaning) {
        root = addKeyword(root, keyword, meaning);
    }
    
    void displayAscending(Node* node) {
    	if(node)
    	{
        displayAscending(node->left);
        cout << node->keyword << ": " << node->meaning << endl;
        displayAscending(node->right);
    
		}
    }
    
    void displayAscending() {
        displayAscending(root);
    }

    
    void displayDescending(Node* node)
    {
        if (node == NULL) return;
        displayDescending(node->right);
        cout << node->keyword << ": " << node->meaning << endl;
        displayDescending(node->left);
    }
    
    
    void displayDescending() {
        displayDescending(root);
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

    
    int calculateHeight(Node* node) {//height
        if (node == NULL) return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }
    
    void findMaxComparisons() {
        cout << "Maximum comparisons required: " << calculateHeight(root) << endl;
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
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin>>meaning;
                dictionary.addKeyword(keyword, meaning);
                break;

            case 2:
                cout << "\nDictionary in Ascending Order:\n";
                dictionary.displayAscending();
                break;

            case 3:
                cout << "\nDictionary in Descending Order:\n";
                dictionary.displayDescending();
                break;

            case 4:
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cout << "Enter new meaning: ";
                cin>>meaning;
                dictionary.updateMeaning(keyword, meaning);
                break;

            case 5:
                dictionary.findMaxComparisons();
                break;

            case 6:
                cout << "Exiting program!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}

