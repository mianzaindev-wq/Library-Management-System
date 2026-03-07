#include "../include/entities/Admin.h"
#include "../include/core/UserFactory.h"

void Admin::displayMenu() {
    int choice = 0;

    do {
        UIUtils::clearScreen();
        UIUtils::printHeader("ADMIN PANEL", "Library Management Administration");
        UIUtils::printSectionHeader("Admin Menu");
        UIUtils::printMenuItem(1, "Add Book");
        UIUtils::printMenuItem(2, "Remove Book");
        UIUtils::printMenuItem(3, "Add User");
        UIUtils::printMenuItem(4, "Remove User");
        UIUtils::printMenuItem(5, "Display All Books");
        UIUtils::printMenuItem(6, "Display Borrow History");
        UIUtils::printMenuItem(7, "Generate Report");
        UIUtils::printMenuItem(8, "Logout");
        UIUtils::printSectionFooter();

        choice = UIUtils::getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                addUser();
                break;
            case 4:
                removeUser();
                break;
            case 5:
                displayAllBooks();
                UIUtils::pause();
                break;
            case 6:
                displayBorrowHistory();
                UIUtils::pause();
                break;
            case 7:
                generateReport();
                UIUtils::pause();
                break;
            case 8:
                UIUtils::printInfo("Logging out...");
                UIUtils::pause();
                break;
            default:
                UIUtils::printError("Invalid choice. Please try again.");
                UIUtils::pause();
        }
    } while (choice != 8);
}

void Admin::addBook() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ADD NEW BOOK");
    
    string title = UIUtils::getStringInput("  Title: ");
    string author = UIUtils::getStringInput("  Author: ");
    string isbn = UIUtils::getStringInput("  ISBN: ");
    string genre = UIUtils::getStringInput("  Genre: ");
    int totalCopies = UIUtils::getIntInput("  Total Copies: ", 1);

    Book newBook(title, author, isbn, genre, totalCopies);
    LibraryManager::getInstance()->addBook(newBook);

    UIUtils::printSuccess("Book added successfully!");
    UIUtils::pause();
}

void Admin::removeBook() {
    UIUtils::clearScreen();
    UIUtils::printHeader("REMOVE BOOK");
    
    string isbn = UIUtils::getStringInput("  Enter ISBN: ");

    if (LibraryManager::getInstance()->removeBook(isbn)) {
        UIUtils::printSuccess("Book removed successfully!");
    } else {
        UIUtils::printError("Book not found with ISBN: " + isbn);
    }
    UIUtils::pause();
}

void Admin::addUser() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ADD NEW USER");
    
    cout << "\n  User Roles:\n";
    cout << "    [1] Admin\n";
    cout << "    [2] Member\n";
    cout << "    [3] Librarian\n\n";

    int roleChoice = UIUtils::getIntInput("  Select role: ", 1, 3);
    string role;
    
    switch (roleChoice) {
        case 1: role = "Admin"; break;
        case 2: role = "Member"; break;
        case 3: role = "Librarian"; break;
    }

    string username = UIUtils::getStringInput("  Username: ");
    string password = UIUtils::getStringInput("  Password: ");

    User* newUser = UserFactory::createUser(role, username, password);
    if (newUser) {
        LibraryManager::getInstance()->addUser(newUser);
        UIUtils::printSuccess("User added successfully!");
    } else {
        UIUtils::printError("Failed to create user.");
    }
    UIUtils::pause();
}

void Admin::removeUser() {
    UIUtils::clearScreen();
    UIUtils::printHeader("REMOVE USER");
    
    string username = UIUtils::getStringInput("  Enter username: ");

    if (LibraryManager::getInstance()->removeUser(username)) {
        UIUtils::printSuccess("User removed successfully!");
    } else {
        UIUtils::printError("User not found with username: " + username);
    }
    UIUtils::pause();
}

void Admin::displayAllBooks() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ALL BOOKS");
    LibraryManager::getInstance()->displayAllBooks();
}

void Admin::displayBorrowHistory() {
    UIUtils::clearScreen();
    UIUtils::printHeader("BORROW HISTORY");
    LibraryManager::getInstance()->displayBorrowHistory();
}

void Admin::generateReport() {
    UIUtils::clearScreen();
    UIUtils::printHeader("SYSTEM REPORT");
    
    auto& books = LibraryManager::getInstance()->getBooks();
    auto& borrowHistory = LibraryManager::getInstance()->getBorrowHistory();

    cout << "\n=== Library Statistics ===\n";
    cout << "Total Books: " << books.size() << "\n";
    cout << "Total Borrows: " << borrowHistory.size() << "\n";

    int returnedCount = 0;
    float totalFine = 0.0f;
    for (const auto& record : borrowHistory) {
        if (record.isReturned()) {
            returnedCount++;
        }
        totalFine += record.getFine();
    }

    cout << "Books Returned: " << returnedCount << "\n";
    cout << "Books Pending: " << (borrowHistory.size() - returnedCount) << "\n";
    cout << "Total Fine Collected: Rs. " << fixed << setprecision(2) << totalFine << "\n\n";
}
