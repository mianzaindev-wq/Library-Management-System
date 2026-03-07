#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User {
private:
    string username;
    string password;
    string role;

public:
    User() = default;
    
    User(const string& usn, const string& pass, const string& rle) 
        : username(usn), password(pass), role(rle) {}
    
    virtual ~User() = default;

    // Getters
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }

    // Setters
    void setPassword(const string& newPassword) { password = newPassword; }

    // Authentication
    bool authenticate(const string& uname, const string& pwd) const {
        return (uname == username && pwd == password);
    }

    // Virtual method for menu display
    virtual void displayMenu() = 0;
};

#endif // USER_H
