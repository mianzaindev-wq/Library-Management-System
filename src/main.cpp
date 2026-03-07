#include <iostream>
#include <iomanip>
#include "../include/core/LibraryManager.h"
#include "../include/core/UserFactory.h"
#include "../include/core/SystemInitializer.h"
#include "../include/ui/UIUtils.h"

using namespace std;

// Define static member
LibraryManager* LibraryManager::instance = nullptr;

void displayMainMenu() {
    UIUtils::printHeader("LIBRARY MANAGEMENT SYSTEM", "Professional Library Management Solution");
    UIUtils::printSectionHeader("Main Menu");
    UIUtils::printMenuItem(1, "Login to Your Account", "🔐");
    UIUtils::printMenuItem(2, "Browse as Guest", "👤");
    UIUtils::printMenuItem(3, "Exit Application", "🚪");
    UIUtils::printSectionFooter();
}

int main() {
    // Initialize system with default data
    SystemInitializer::initializeSystem();

    int choice = 0;
    
    while (true) {
        displayMainMenu();
        
        choice = UIUtils::getIntInput("Enter your choice: ");

        if (choice == 1) {
            UIUtils::clearScreen();
            UIUtils::printHeader("USER LOGIN");
            
            string username = UIUtils::getStringInput("  Username: ");
            string password = UIUtils::getStringInput("  Password: ");

            User* user = LibraryManager::getInstance()->login(username, password);
            if (user) {
                UIUtils::printSuccess("Login successful! Welcome, " + user->getUsername() + "!");
                UIUtils::pause();
                user->displayMenu();
            } else {
                UIUtils::printError("Invalid credentials. Please try again.");
                UIUtils::pause();
            }
        } 
        else if (choice == 2) {
            User* guest = UserFactory::createGuestUser();
            if (guest) {
                guest->displayMenu();
                delete guest;
            }
        } 
        else if (choice == 3) {
            UIUtils::clearScreen();
            cout << "\n";
            cout << "+==================================+\n";
            cout << "|  Thank you for using our system! |\n";
            cout << "|        Goodbye, have a nice      |\n";
            cout << "|              day!                |\n";
            cout << "+==================================+\n\n";
            break;
        } 
        else {
            UIUtils::printError("Invalid choice. Please try again.");
            UIUtils::pause();
        }
    }

    return 0;
}
