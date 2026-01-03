// Library Management System - improved with file handling and validation
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "book.h"
#include "fileio.h"

using namespace std;

void addBook(vector<Book> &library);
void displayBooks(const vector<Book> &library);
void searchBook(const vector<Book> &library);
void updateBook(vector<Book> &library);
void deleteBook(vector<Book> &library);
int getIntInput(const string &prompt, int minVal = INT_MIN, int maxVal = INT_MAX);

int main() {
    vector<Book> library;
    const string dataFile = "library.txt";

    cout << "===== Welcome to Library Management System =====\n";

    // Try to load existing data (if present)
    if (loadLibrary(dataFile, library)) {
        cout << "Loaded " << library.size() << " book(s) from " << dataFile << "\n";
    } else {
        cout << "No existing data found. Starting with empty library.\n";
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Update Book Information\n";
        cout << "5. Delete Book\n";
        cout << "6. Save and Exit\n";

        choice = getIntInput("Enter Your Choice: ", 1, 6);

        switch (choice) {
            case 1: addBook(library); break;
            case 2: displayBooks(library); break;
            case 3: searchBook(library); break;
            case 4: updateBook(library); break;
            case 5: deleteBook(library); break;
            case 6: 
                if (saveLibrary(dataFile, library))
                    cout << "Library saved to " << dataFile << "\n";
                else
                    cout << "Failed to save library to " << dataFile << "\n";
                cout << "Exiting the system. Goodbye!\n";
                break;
        }
    } while (choice != 6);

    return 0;
}

int getIntInput(const string &prompt, int minVal, int maxVal) {
    while (true) {
        cout << prompt;
        int value;
        if (cin >> value) {
            if (value < minVal || value > maxVal) {
                cout << "Value out of range. Try again.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void addBook(vector<Book> &library) {
    Book b;
    b.bookID = getIntInput("Enter Book ID: ");

    cout << "Enter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    b.quantity = getIntInput("Enter Quantity: ", 0);

    library.push_back(b);
    cout << "Book Added Successfully!\n";
}

void displayBooks(const vector<Book> &library) {
    if (library.empty()) {
        cout << "\nNo books available.\n";
        return;
    }

    cout << "\nList of Books:\n";
    for (const auto &b : library) {
        cout << "-----------------------------\n";
        cout << "Book ID   : " << b.bookID << endl;
        cout << "Title     : " << b.title << endl;
        cout << "Author    : " << b.author << endl;
        cout << "Quantity  : " << b.quantity << endl;
    }
}

void searchBook(const vector<Book> &library) {
    int id = getIntInput("Enter Book ID to search: ");
    for (const auto &b : library) {
        if (b.bookID == id) {
            cout << "Book Found!\n";
            cout << "Title    : " << b.title << endl;
            cout << "Author   : " << b.author << endl;
            cout << "Quantity : " << b.quantity << endl;
            return;
        }
    }
    cout << "Book not found.\n";
}

void updateBook(vector<Book> &library) {
    int id = getIntInput("Enter Book ID to update: ");
    for (auto &b : library) {
        if (b.bookID == id) {
            cout << "Enter new Title: ";
            getline(cin, b.title);
            cout << "Enter new Author: ";
            getline(cin, b.author);
            b.quantity = getIntInput("Enter new Quantity: ", 0);
            cout << "Book Information Updated Successfully!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void deleteBook(vector<Book> &library) {
    int id = getIntInput("Enter Book ID to delete: ");
    for (size_t i = 0; i < library.size(); ++i) {
        if (library[i].bookID == id) {
            library.erase(library.begin() + i);
            cout << "Book Deleted Successfully!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}
