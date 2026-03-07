#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <iomanip>
#include "../models/User.h"
#include "../core/LibraryManager.h"
#include "../ui/UIUtils.h"

using namespace std;

class Member : public User {
public:
    Member(const string& uname, const string& pwd) 
        : User(uname, pwd, "Member") {}
    
    ~Member() = default;

    void displayMenu() override;

private:
    void searchBook();
    void borrowBooks();
    void returnBooks();
    void viewBorrowHistory();
    void checkFine();
};

#endif // MEMBER_H
