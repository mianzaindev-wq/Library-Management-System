#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iomanip>
#include "../models/User.h"
#include "../core/LibraryManager.h"
#include "../ui/UIUtils.h"

using namespace std;

class Admin : public User {
public:
    Admin(const string& uname, const string& pwd) 
        : User(uname, pwd, "Admin") {}
    
    ~Admin() = default;

    void displayMenu() override;

private:
    void addBook();
    void removeBook();
    void addUser();
    void removeUser();
    void displayAllBooks();
    void displayBorrowHistory();
    void generateReport();
};

#endif // ADMIN_H
