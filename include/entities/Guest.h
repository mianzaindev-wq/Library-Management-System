#ifndef GUEST_H
#define GUEST_H

#include <string>
#include "../models/User.h"
#include "../core/LibraryManager.h"
#include "../ui/UIUtils.h"

using namespace std;

class Guest : public User {
public:
    Guest() : User("Guest", "", "Guest") {}
    
    ~Guest() = default;

    void displayMenu() override;

private:
    void searchBook();
    void viewAllBooks();
};

#endif // GUEST_H
