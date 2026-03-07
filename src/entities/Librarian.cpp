#include "../include/entities/Librarian.h"

void Librarian::displayMenu() {
    int choice = 0;
    
    do {
        UIUtils::clearScreen();
        UIUtils::printHeader("LIBRARIAN PANEL", "Library Staff Dashboard");
        UIUtils::printSectionHeader("Librarian Menu");
        UIUtils::printMenuItem(1, "Add Book");
        UIUtils::printMenuItem(2, "Remove Book");
        UIUtils::printMenuItem(3, "View All Books");
        UIUtils::printMenuItem(4, "View Borrow History");
        UIUtils::printMenuItem(5, "Manage Pending Returns");
        UIUtils::printMenuItem(6, "Logout");
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
                viewAllBooks();
                UIUtils::pause();
                break;
            case 4:
                viewAllBorrowHistory();
                UIUtils::pause();
                break;
            case 5:
                managePendingReturns();
                UIUtils::pause();
                break;
            case 6:
                UIUtils::printInfo("Logging out...");
                UIUtils::pause();
                break;
            default:
                UIUtils::printError("Invalid choice. Please try again.");
                UIUtils::pause();
        }
    } while (choice != 6);
}

void Librarian::addBook() {
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

void Librarian::removeBook() {
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

void Librarian::viewAllBooks() {
    UIUtils::clearScreen();
    UIUtils::printHeader("ALL BOOKS");
    LibraryManager::getInstance()->displayAllBooks();
}

void Librarian::viewAllBorrowHistory() {
    UIUtils::clearScreen();
    UIUtils::printHeader("BORROW HISTORY");
    LibraryManager::getInstance()->displayBorrowHistory();
}

void Librarian::managePendingReturns() {
    UIUtils::clearScreen();
    UIUtils::printHeader("PENDING RETURNS");
    
    cout << "\n=== Books Pending Return ===\n\n";
    cout << left << setw(15) << "Member" << setw(25) << "Book Title" 
         << setw(15) << "Borrow Date" << setw(15) << "Due Date\n";
    cout << string(70, '-') << "\n";

    bool found = false;
    for (const auto& record : LibraryManager::getInstance()->getBorrowHistory()) {
        if (!record.isReturned()) {
            cout << left << setw(15) << record.getUsername()
                 << setw(25) << record.getTitle()
                 << setw(15) << record.getBorrowDate()
                 << setw(15) << record.getDueDate() << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo pending returns.\n";
    }
}
