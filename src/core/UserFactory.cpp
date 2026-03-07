#include "../include/core/UserFactory.h"
#include "../include/entities/Admin.h"
#include "../include/entities/Member.h"
#include "../include/entities/Librarian.h"
#include "../include/entities/Guest.h"

User* UserFactory::createUser(const string& role, const string& uname, const string& pwd) {
    if (role == "Admin") {
        return new Admin(uname, pwd);
    } 
    else if (role == "Member") {
        return new Member(uname, pwd);
    } 
    else if (role == "Librarian") {
        return new Librarian(uname, pwd);
    } 
    else {
        return nullptr;
    }
}

User* UserFactory::createGuestUser() {
    return new Guest();
}
