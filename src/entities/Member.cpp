#include "../include/entities/Member.h"

void Member::displayMenu() {
    int choice = 0;
    
    do {
        UIUtils::clearScreen();
        UIUtils::printHeader("MEMBER PANEL", "Member Dashboard");
        UIUtils::printSectionHeader("Member Menu");
        UIUtils::printMenuItem(1, "Search Book");
        UIUtils::printMenuItem(2, "Borrow Books");
        UIUtils::printMenuItem(3, "Return Books");
        UIUtils::printMenuItem(4, "View Borrow History");
        UIUtils::printMenuItem(5, "Check Fine");
        UIUtils::printMenuItem(6, "Logout");
        UIUtils::printSectionFooter();

        choice = UIUtils::getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                searchBook();
                break;
            case 2:
                borrowBooks();
                break;
            case 3:
                returnBooks();
                break;
            case 4:
                viewBorrowHistory();
                UIUtils::pause();
                break;
            case 5:
                checkFine();
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

void Member::searchBook() {
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

void Member::borrowBooks() {
    UIUtils::clearScreen();
    UIUtils::printHeader("BORROW BOOK");
    
    string title = UIUtils::getStringInput("  Enter book title: ");
    Book* book = LibraryManager::getInstance()->findBookByTitle(title);

    if (!book) {
        UIUtils::printError("Book not found with title: " + title);
        UIUtils::pause();
        return;
    }

    if (!book->borrow()) {
        UIUtils::printError("No copies available for this book.");
        UIUtils::pause();
        return;
    }

    string borrowDate = UIUtils::getStringInput("  Borrow date (DD/MM/YYYY): ");
    string dueDate = UIUtils::getStringInput("  Due date (DD/MM/YYYY): ");

    BorrowRecord record(this->getUsername(), title, book->getISBN(), borrowDate, dueDate);
    LibraryManager::getInstance()->addBorrowRecord(record);

    UIUtils::printSuccess("Book borrowed successfully!");
    UIUtils::pause();
}

void Member::returnBooks() {
    UIUtils::clearScreen();
    UIUtils::printHeader("RETURN BOOK");
    
    string title = UIUtils::getStringInput("  Enter book title: ");
    Book* book = LibraryManager::getInstance()->findBookByTitle(title);

    if (!book) {
        UIUtils::printError("Book not found with title: " + title);
        UIUtils::pause();
        return;
    }

    string returnDate = UIUtils::getStringInput("  Return date (DD/MM/YYYY): ");

    BorrowRecord* record = LibraryManager::getInstance()->getBorrowRecordByUsername(this->getUsername());
    if (record && record->getTitle() == title) {
        record->setReturnDate(returnDate);
        book->returnBook();
        UIUtils::printSuccess("Book returned successfully!");
        if (record->getFine() > 0) {
            cout << "Fine Amount: Rs. " << fixed << setprecision(2) << record->getFine() << "\n";
        }
    } else {
        UIUtils::printError("No borrow record found for this book.");
    }
    UIUtils::pause();
}

void Member::viewBorrowHistory() {
    UIUtils::clearScreen();
    UIUtils::printHeader("BORROW HISTORY");
    
    cout << "\n=== Your Borrow Records ===\n\n";
    cout << left << setw(25) << "Book Title" << setw(15) << "Borrow Date" 
         << setw(15) << "Due Date" << setw(15) << "Return Date" << setw(10) << "Fine\n";
    cout << string(80, '-') << "\n";

    bool found = false;
    for (const auto& record : LibraryManager::getInstance()->getBorrowHistory()) {
        if (record.getUsername() == this->getUsername()) {
            cout << left << setw(25) << record.getTitle()
                 << setw(15) << record.getBorrowDate()
                 << setw(15) << record.getDueDate()
                 << setw(15) << (record.isReturned() ? record.getReturnDate() : "Pending")
                 << setw(10) << fixed << setprecision(2) << "Rs. " << record.getFine() << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo borrow records found.\n";
    }
}

void Member::checkFine() {
    UIUtils::clearScreen();
    UIUtils::printHeader("FINE DETAILS");
    
    float totalFine = 0.0f;
    bool hasPendingBooks = false;

    cout << "\n=== Your Fines ===\n\n";
    for (const auto& record : LibraryManager::getInstance()->getBorrowHistory()) {
        if (record.getUsername() == this->getUsername()) {
            if (!record.isReturned()) {
                hasPendingBooks = true;
            }
            if (record.getFine() > 0) {
                cout << "Book: " << record.getTitle() << "\n";
                cout << "Fine: Rs. " << fixed << setprecision(2) << record.getFine() << "\n\n";
                totalFine += record.getFine();
            }
        }
    }

    if (totalFine == 0 && !hasPendingBooks) {
        UIUtils::printSuccess("No fines! You are all paid up.");
    } else {
        cout << "\nTotal Fine Due: Rs. " << fixed << setprecision(2) << totalFine << "\n";
    }
}
