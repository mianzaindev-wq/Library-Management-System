#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "../models/Book.h"
#include "../models/User.h"
#include "../models/BorrowRecord.h"

using namespace std;

class LibraryManager {
private:
    vector<Book> books;
    vector<User*> users;
    vector<BorrowRecord> borrowHistory;

    static LibraryManager* instance;
    
    LibraryManager() = default;

public:
    // Singleton pattern
    static LibraryManager* getInstance() {
        if (instance == nullptr) {
            instance = new LibraryManager();
        }
        return instance;
    }

    ~LibraryManager() {
        for (User* u : users) {
            delete u;
        }
    }

    // Book management
    void addBook(const Book& b) { books.push_back(b); }
    
    bool removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                books.erase(it);
                return true;
            }
        }
        return false;
    }

    Book* findBookByTitle(const string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                return &book;
            }
        }
        return nullptr;
    }

    Book* findBookByISBN(const string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                return &book;
            }
        }
        return nullptr;
    }

    void displayBookDetails(const string& title) {
        Book* book = findBookByTitle(title);
        if (book) {
            cout << "\n=== Book Details ===\n";
            cout << "Title: " << book->getTitle() << "\n";
            cout << "Author: " << book->getAuthor() << "\n";
            cout << "ISBN: " << book->getISBN() << "\n";
            cout << "Genre: " << book->getGenre() << "\n";
            cout << "Total Copies: " << book->getTotalCopies() << "\n";
            cout << "Available Copies: " << book->getAvailableCopies() << "\n";
        }
    }

    void displayAllBooks() {
        if (books.empty()) {
            cout << "\nNo books in library.\n";
            return;
        }
        cout << "\n=== Library Books ===\n\n";
        cout << left << setw(25) << "Title" << setw(20) << "Author" 
             << setw(20) << "ISBN" << setw(15) << "Genre" 
             << setw(10) << "Available\n";
        cout << string(90, '-') << "\n";
        
        for (const auto& book : books) {
            cout << left << setw(25) << book.getTitle() 
                 << setw(20) << book.getAuthor()
                 << setw(20) << book.getISBN() 
                 << setw(15) << book.getGenre()
                 << setw(10) << book.getAvailableCopies() << "\n";
        }
    }

    // User management
    void addUser(User* u) { users.push_back(u); }

    bool removeUser(const string& username) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if ((*it)->getUsername() == username) {
                delete *it;
                users.erase(it);
                return true;
            }
        }
        return false;
    }

    User* login(const string& username, const string& password) {
        for (User* u : users) {
            if (u->authenticate(username, password)) {
                return u;
            }
        }
        return nullptr;
    }

    // Borrow history management
    void addBorrowRecord(const BorrowRecord& record) { borrowHistory.push_back(record); }

    void displayBorrowHistory() {
        if (borrowHistory.empty()) {
            cout << "\nNo borrow history.\n";
            return;
        }
        cout << "\n=== Borrow History ===\n\n";
        cout << left << setw(15) << "Username" << setw(25) << "Book Title" 
             << setw(15) << "Borrow Date" << setw(15) << "Due Date" 
             << setw(15) << "Return Date" << setw(10) << "Fine\n";
        cout << string(95, '-') << "\n";
        
        for (const auto& record : borrowHistory) {
            cout << left << setw(15) << record.getUsername() 
                 << setw(25) << record.getTitle()
                 << setw(15) << record.getBorrowDate() 
                 << setw(15) << record.getDueDate()
                 << setw(15) << (record.isReturned() ? record.getReturnDate() : "Not Returned")
                 << setw(10) << "Rs. " << record.getFine() << "\n";
        }
    }

    BorrowRecord* getBorrowRecordByUsername(const string& username) {
        for (auto& record : borrowHistory) {
            if (record.getUsername() == username && !record.isReturned()) {
                return &record;
            }
        }
        return nullptr;
    }

    vector<Book>& getBooks() { return books; }
    vector<BorrowRecord>& getBorrowHistory() { return borrowHistory; }
};

#endif // LIBRARYMANAGER_H
