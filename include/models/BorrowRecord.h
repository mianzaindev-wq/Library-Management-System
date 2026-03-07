#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <iostream>
#include <string>
#include "Fine.h"

using namespace std;

class BorrowRecord {
private:
    string username;
    string ISBN;
    string title;
    string borrowDate;
    string dueDate;
    string returnDate;
    float fineAmount;

public:
    // Constructors
    BorrowRecord() : fineAmount(0.0f) {}
    
    BorrowRecord(const string& user, const string& ttle, const string& isbn, 
                 const string& borrow, const string& due) 
        : username(user), title(ttle), ISBN(isbn), borrowDate(borrow), 
          dueDate(due), returnDate(""), fineAmount(0.0f) {}

    // Destructor
    ~BorrowRecord() = default;

    // Setters
    void setReturnDate(const string& date) {
        returnDate = date;
        calculateFine();
    }

    // Fine calculation
    float calculateFine() {
        if (returnDate.empty()) {
            return 0.0f;
        }

        Fine fineCalc(100);
        fineCalc.calculateFine(dueDate, returnDate);
        fineAmount = fineCalc.getFineAmount();
        return fineAmount;
    }

    // Getters
    float getFine() const { return fineAmount; }
    string getTitle() const { return title; }
    string getUsername() const { return username; }
    string getISBN() const { return ISBN; }
    string getBorrowDate() const { return borrowDate; }
    string getDueDate() const { return dueDate; }
    string getReturnDate() const { return returnDate; }
    
    bool isReturned() const { return !returnDate.empty(); }
};

#endif // BORROWRECORD_H
