#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

const int MAX_SIZE = 100; // Max size for the array

// Function to read data from file into array
int readDataFromFile(const string& filename, int arr[], int maxSize) {
    ifstream file("C:\\Users\\habib\\source\\repos\\myFirstProject\\myFirstProject\\A1input.txt");
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return -1;
    }

    int value, count = 0;
    while (file >> value && count < maxSize) {
        arr[count++] = value;
    }

    file.close();
    return count; // Returns the number of elements read
}

// Function to check if an integer exists in the array
int findValue(int arr[], int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return i; // Return index of the value
        }
    }
    return -1; // Return -1 if the value is not found
}

// Function to modify the value at a specific index with exception handling
void modifyValue(int arr[], int size, int index, int newValue, int& oldValue) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    oldValue = arr[index];
    arr[index] = newValue;
}

// Function to add a new integer to the end of the array
bool addValue(int arr[], int& size, int value) {
    if (size >= MAX_SIZE) {
        return false; // Array is full, cannot add new value
    }
    arr[size++] = value;
    return true;
}

// Function to replace value with 0 or remove it
void replaceOrRemove(int arr[], int& size, int index, bool remove = false) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    if (remove) {
        // Shift elements left to remove the integer
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --size; // Decrease the size
    }
    else {
        arr[index] = 0; // Replace with 0
    }
}

int main() {
    int arr[MAX_SIZE];
    int size = readDataFromFile("A1input.txt", arr, MAX_SIZE);

    if (size == -1) {
        return 1; // Exit if there was an issue reading the file
    }

    int choice, value, index, oldValue;
    bool success;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Find value\n";
        cout << "2. Modify value\n";
        cout << "3. Add value\n";
        cout << "4. Replace or remove value\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to find: ";
            cin >> value;
            index = findValue(arr, size, value);
            if (index != -1) {
                cout << "Value found at index: " << index << endl;
            }
            else {
                cout << "Value not found." << endl;
            }
            break;

        case 2:
            try {
                cout << "Enter index to modify: ";
                cin >> index;
                cout << "Enter new value: ";
                cin >> value;
                modifyValue(arr, size, index, value, oldValue);
                cout << "Old value: " << oldValue << ", New value: " << value << endl;
            }
            catch (const out_of_range& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;

        case 3:
            cout << "Enter value to add: ";
            cin >> value;
            success = addValue(arr, size, value);
            if (success) {
                cout << "Value added successfully." << endl;
            }
            else {
                cout << "Array is full, cannot add value." << endl;
            }
            break;

        case 4:
            try {
                cout << "Enter index to replace or remove: ";
                cin >> index;
                cout << "Replace with 0 (1) or Remove (2)? ";
                cin >> value;
                replaceOrRemove(arr, size, index, value == 2);
                cout << (value == 2 ? "Value removed." : "Value replaced with 0.") << endl;
            }
            catch (const out_of_range& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;

        case 5:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}