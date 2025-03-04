#include <iostream>
using namespace std;

#define TABLE_SIZE 10  // Hash table size


class Client {
private:
    long long phone;
    bool occupied;

public:
    Client() {
        phone = -1;  // Default empty slot
        occupied = false;
    }

    long long getPhone() { return phone; }
    bool isOccupied() { return occupied; }

    void setPhone(long long p) { 
        phone = p; 
        occupied = true; 
    }

    void clear() { 
        phone = -1; 
        occupied = false; 
    }
};

class TelephoneBook {
private:
    Client table[TABLE_SIZE];//hash table ka size

    int hashFunction(long long phone) {
        return phone % TABLE_SIZE;
    }

public:
    // Insert Without Replacement
    void insertWithoutReplacement(long long phone) {
        int index = hashFunction(phone);
        int originalIndex = index;//tracking purpose ke liye 

        while (table[index].isOccupied()) { // Linear probing
            index = (index + 1) % TABLE_SIZE;

            if (index == originalIndex) {
                cout << "Table is full! Cannot insert " << phone << endl;
                return;
            }
        }
        table[index].setPhone(phone);
    }

    // Insert With Replacement
    void insertWithReplacement(long long phone) {
        int index = hashFunction(phone);
        int originalIndex = index;

        if (table[index].isOccupied()) {
            if (hashFunction(table[index].getPhone()) != index) { // If current element is misplaced
                long long displaced = table[index].getPhone();
                table[index].setPhone(phone);
                insertWithoutReplacement(displaced);
                return;
            }
        }

        while (table[index].isOccupied()) { // Linear probing
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].setPhone(phone);
    }

    // Search function
    int search(long long phone) {
        int index = hashFunction(phone);
        int originalIndex = index;
        int comparisons = 1;

        while (table[index].isOccupied()) {
            if (table[index].getPhone() == phone) {
                return comparisons;
            }
            index = (index + 1) % TABLE_SIZE;
            comparisons++;

            if (index == originalIndex) {
                return -1; // Not found
            }
        }
        return -1; // Not found
    }

    // Display hash table
    void display() {
        cout << "Index\tPhone Number\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << "\t";
            if (table[i].isOccupied()) cout << table[i].getPhone();
            else cout << "--";
            cout << endl;
        }
    }
};

// Main Function
int main() {
    TelephoneBook tb;
    int choice;
    long long phone;
    bool useReplacement;
    
    cout << "Use replacement method? (1 for Yes, 0 for No): ";
    cin >> useReplacement;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a Phone Number\n";
        cout << "2. Search for a Phone Number\n";
        cout << "3. Display Hash Table\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter phone number to insert: ";
                cin >> phone;
                if (useReplacement)
                    tb.insertWithReplacement(phone);
                else
                    tb.insertWithoutReplacement(phone);
                break;
            case 2:
                cout << "Enter phone number to search: ";
                cin >> phone;
                {
                    int comparisons = tb.search(phone);
                    if (comparisons == -1)
                        cout << "Phone number not found!\n";
                    else
                        cout << "Phone number found with " << comparisons << " comparisons.\n";
                }
                break;
            case 3:
                tb.display();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
