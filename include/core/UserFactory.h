#ifndef USERFACTORY_H
#define USERFACTORY_H

#include <string>
#include "../models/User.h"

using namespace std;

// Forward declarations
class Admin;
class Member;
class Librarian;
class Guest;

class UserFactory {
public:
    static User* createUser(const string& role, const string& uname, const string& pwd);
    static User* createGuestUser();
};

#endif // USERFACTORY_H
