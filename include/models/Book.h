#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;
    string genre;
    int totalCopies;
    int availableCopies;

public:
    // Constructors
    Book() = default;
    
    Book(const string& t, const string& auth, const string& isbn, 
         const string& gnre, int total_copies) 
        : title(t), author(auth), ISBN(isbn), genre(gnre), 
          totalCopies(total_copies), availableCopies(total_copies) {}

    // Destructor
    ~Book() = default;

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    string getGenre() const { return genre; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }

    // Setters
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setGenre(const string& g) { genre = g; }
    void setTotalCopies(int t) { totalCopies = t; }

    // Availability management
    bool borrow() {
        if (availableCopies > 0) {
            availableCopies--;
            return true;
        }
        return false;
    }

    void returnBook() {
        if (availableCopies < totalCopies) {
            availableCopies++;
        }
    }

    bool isAvailable() const { return availableCopies > 0; }
};

#endif // BOOK_H
