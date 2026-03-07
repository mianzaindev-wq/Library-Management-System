#ifndef SYSTEMINITIALIZER_H
#define SYSTEMINITIALIZER_H

#include "LibraryManager.h"
#include "UserFactory.h"
#include "../models/Book.h"

class SystemInitializer {
public:
    static void initializeSystem() {
        // Create default admin
        User* defaultAdmin = UserFactory::createUser("Admin", "admin", "admin");
        LibraryManager::getInstance()->addUser(defaultAdmin);

        // Add sample C++ books
        LibraryManager::getInstance()->addBook(
            Book("The C++ Programming Language", 
                 "Bjarne Stroustrup", "978-0321563842", "Programming", 5)
        );
        LibraryManager::getInstance()->addBook(
            Book("C++ Primer", 
                 "Stanley B. Lippman", "978-0321563840", "Programming", 3)
        );
        LibraryManager::getInstance()->addBook(
            Book("Effective C++", 
                 "Scott Meyers", "978-0321334876", "Programming", 4)
        );
        LibraryManager::getInstance()->addBook(
            Book("C++ Cookbook", 
                 "Anthony Williams", "978-0321563847", "Programming", 2)
        );
        LibraryManager::getInstance()->addBook(
            Book("Algorithms in C++", 
                 "Robert E. Sedgewick", "978-0201360684", "Programming", 3)
        );
    }
};

#endif // SYSTEMINITIALIZER_H
