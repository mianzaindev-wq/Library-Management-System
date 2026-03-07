#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <string>
#include <iomanip>
#include "../models/User.h"
#include "../core/LibraryManager.h"
#include "../ui/UIUtils.h"

using namespace std;

class Librarian : public User {
public:
    Librarian(const string& uname, const string& pwd) 
        : User(uname, pwd, "Librarian") {}
    
    ~Librarian() = default;

    void displayMenu() override;

private:
    void addBook();
    void removeBook();
    void viewAllBooks();
    void viewAllBorrowHistory();
    void managePendingReturns();
};

#endif // LIBRARIAN_H
