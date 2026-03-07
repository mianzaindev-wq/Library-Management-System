#include "../include/entities/Guest.h"

void Guest::displayMenu() {
    int choice = 0;
    
    do {
        UIUtils::clearScreen();
        UIUtils::printHeader("GUEST MODE", "Browse Library Catalog");
        UIUtils::printSectionHeader("Guest Menu");
        UIUtils::printMenuItem(1, "Search Book");
        UIUtils::printMenuItem(2, "View All Books");
        UIUtils::printMenuItem(3, "Exit Guest Mode");
        UIUtils::printSectionFooter();

        choice = UIUtils::getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                searchBook();
                break;
            case 2:
                viewAllBooks();
                break;
            case 3:
                UIUtils::printInfo("Exiting guest mode...");
                UIUtils::pause();
                break;
            default:
                UIUtils::printError("Invalid choice. Please try again.");
                UIUtils::pause();
        }
    } while (choice != 3);
}

void Guest::searchBook() {
    UIUtils::clearScreen();
    UIUtils::printHeader("SEARCH BOOK");
    
    string title = UIUtils::getStringInput("  Enter book title: ");

    Book* book = LibraryManager::getInstance()->findBookByTitle(title);
    if (book) {
        cout << "\n=== Search Results ===\n";
        LibraryManager::getInstance()->displayBookDetails(title);
    } else {
        UIUtils::printError("No book found with title: " + title);
    }
    UIUtils::pause();
}

void Guest::viewAllBooks() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ALL BOOKS");
    LibraryManager::getInstance()->displayAllBooks();
    UIUtils::pause();
}
