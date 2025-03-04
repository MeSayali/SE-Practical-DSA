#include <iostream>
using namespace std;

#define TABLE_SIZE 10  


class Node {
public:
    int key;
    string value;
    Node* next;//next node 

    Node(int k, string v) {
        key = k;
        value = v;
        next = NULL;
    }
};

// Hash Table using Separate Chaining
class Dictionary {
private:
    Node* table[TABLE_SIZE]; // Array of linked list heads

    int hashFunction(int key) {
        return key % TABLE_SIZE; 
    }

public:
    Dictionary() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL; // Initialize all buckets as empty
        }
    }

    // Insert a key-value pair
    void insert(int key, string value) {
        int index = hashFunction(key);//find index
        Node* newNode = new Node(key, value);

        if (table[index] == NULL) {
            table[index] = newNode; // First node in the linked list
        }
		 else 
		 {
            Node* temp = table[index];//collosion happend
            while (temp->next != NULL) {//need to traverse until last node
                if (temp->key == key) {
                    cout << "Key already exists! Updating value." << endl;
                    temp->value = value;
                    return;
                }
                temp = temp->next;
            }
            if (temp->key == key) {
                cout << "Key already exists! Updating value." << endl;
                temp->value = value;
            } else {
                temp->next = newNode; // Insert at end of linked list
            }
        }
    }

    // Find a value using key
    string find(int key) {
        int index = hashFunction(key);
        Node* temp = table[index];//head 

        while (temp != NULL) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        return "Not Found";
    }

    // Delete a key-value pair
    void remove(int key) {//computing hash function
        int index = hashFunction(key);//index
        Node* temp = table[index];//store head
        Node* prev = NULL;

        while (temp != NULL && temp->key != key) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Key not found!" << endl;
            return;
        }

        if (prev == NULL) {
            table[index] = temp->next; // Remove first node
        } else {
            prev->next = temp->next; // Bypass the node
        }
        delete temp;
        cout << "Key deleted successfully!" << endl;
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            Node* temp = table[i];
            while (temp != NULL) {
                cout << "[" << temp->key << ": " << temp->value << "] -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }
};

// Main Function
int main() {
    Dictionary dict;
    int choice, key;
    string value;

    do {
        cout << "\nMenu:\n1. Insert\n2. Find\n3. Delete\n4. Display\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key and value to insert: ";
                cin >> key >> value;
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                cout << "Value: " << dict.find(key) << endl;
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.remove(key);
                break;
            case 4:
                dict.display();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
