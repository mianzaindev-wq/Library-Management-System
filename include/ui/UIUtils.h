#ifndef UIUTILS_H
#define UIUTILS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include <cctype>
#include <regex>
#include <cfloat>

#ifdef _WIN32
    #include <cstdlib>
#else
    #include <cstdlib>
#endif

using namespace std;

class UIUtils {
public:
    // Color and style constants
    static constexpr const char* RESET = "\033[0m";
    static constexpr const char* BOLD = "\033[1m";
    static constexpr const char* RED = "\033[31m";
    static constexpr const char* GREEN = "\033[32m";
    static constexpr const char* YELLOW = "\033[33m";
    static constexpr const char* BLUE = "\033[34m";
    static constexpr const char* MAGENTA = "\033[35m";
    static constexpr const char* CYAN = "\033[36m";
    static constexpr const char* WHITE = "\033[37m";

    // Initialize console for colors (Windows only)
    static void initializeConsole() {
        #ifdef _WIN32
            // Windows-specific console initialization removed to avoid header conflicts
            // Colors will work in Windows Terminal, but not in legacy cmd.exe
        #endif
    }

    // Clear screen with animation
    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    // Print main header with enhanced styling
    static void printHeader(const string& title, const string& subtitle = "") {
        clearScreen();
        cout << "\n";
        cout << CYAN << BOLD;
        cout << "============================================================\n";
        cout << "|" << centerText("[" + title + "]", 60) << "|\n";
        cout << "============================================================\n";
        cout << RESET;

        if (!subtitle.empty()) {
            cout << YELLOW << centerText(subtitle, 62) << RESET << "\n";
        }
        cout << "\n";
    }

    // Print section header
    static void printSectionHeader(const string& title) {
        cout << "\n" << BLUE << BOLD << "--- " << title << " ";
        for (size_t i = 0; i < 50 - title.length(); ++i) cout << "-";
        cout << "\n" << RESET;
    }

    // Print section footer
    static void printSectionFooter() {
        cout << BLUE << BOLD;
        for (int i = 0; i < 60; ++i) cout << "-";
        cout << "\n" << RESET << "\n";
    }

    // Enhanced menu item with better formatting
    static void printMenuItem(int number, const string& description, const string& icon = "") {
        cout << "  [" << number << "] " << description << "\n";
    }

    // Print separator line
    static void printSeparator(char ch = '-', int length = 60) {
        cout << string(length, ch) << "\n";
    }

    // Enhanced status messages with colors and icons
    static void printSuccess(const string& message) {
        cout << "\n" << GREEN << "✓ " << message << RESET << "\n\n";
    }

    static void printError(const string& message) {
        cout << "\n" << RED << "✗ " << message << RESET << "\n\n";
    }

    static void printWarning(const string& message) {
        cout << "\n" << YELLOW << "⚠ " << message << RESET << "\n\n";
    }

    static void printInfo(const string& message) {
        cout << "\n" << BLUE << "ℹ " << message << RESET << "\n\n";
    }

    static void printLoading(const string& message) {
        cout << "\n" << CYAN << "⟳ " << message << "..." << RESET << "\n";
    }

    // Enhanced table formatting
    static void printTableHeader(const vector<string>& headers, const vector<int>& widths) {
        cout << "\n";
        // Top border
        cout << "+";
        for (size_t i = 0; i < headers.size(); ++i) {
            for (int j = 0; j < widths[i] + 2; ++j) cout << "-";
            cout << "+";
        }
        cout << "\n";

        // Headers
        cout << "|";
        for (size_t i = 0; i < headers.size(); ++i) {
            cout << " " << left << setw(widths[i]) << headers[i] << " |";
        }
        cout << "\n";

        // Separator
        cout << "+";
        for (size_t i = 0; i < headers.size(); ++i) {
            for (int j = 0; j < widths[i] + 2; ++j) cout << "-";
            cout << "+";
        }
        cout << "\n";
    }

    static void printTableRow(const vector<string>& data, const vector<int>& widths) {
        cout << "|";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << " " << left << setw(widths[i]) << data[i] << " |";
        }
        cout << "\n";
    }

    static void printTableFooter(const vector<int>& widths) {
        cout << "+";
        for (size_t i = 0; i < widths.size(); ++i) {
            for (int j = 0; j < widths[i] + 2; ++j) cout << "-";
            cout << "+";
        }
        cout << "\n\n";
    }

    // Enhanced input validation with better error handling
    static int getIntInput(const string& prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
        int choice;
        int attempts = 0;
        const int maxAttempts = 3;

        while (attempts < maxAttempts) {
            try {
                cout << prompt;
                string input;
                getline(cin, input);

                // Remove whitespace
                input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

                if (input.empty()) {
                    throw runtime_error("Input cannot be empty.");
                }

                // Check if input contains only digits (and optional minus sign)
                if (!regex_match(input, regex("^-?\\d+$"))) {
                    throw runtime_error("Input must contain only numbers.");
                }

                choice = stoi(input);

                if (choice < minVal || choice > maxVal) {
                    throw runtime_error("Value must be between " + to_string(minVal) +
                                      " and " + to_string(maxVal) + ".");
                }

            } catch (const out_of_range&) {
                printError("Number is too large. Please enter a smaller value.");
            } catch (const invalid_argument&) {
                printError("Invalid number format. Please try again.");
            } catch (const runtime_error& e) {
                printError(string(e.what()));
            } catch (const exception& e) {
                printError("Unexpected error: " + string(e.what()));
            }

            attempts++;
            if (attempts < maxAttempts) {
                printInfo("Attempts remaining: " + to_string(maxAttempts - attempts));
            }
        }

        printError("Maximum attempts exceeded. Returning to menu.");
        return -1; // Error indicator
    }

    // Enhanced string input with validation
    static string getStringInput(const string& prompt, bool allowEmpty = false,
                                size_t minLength = 0, size_t maxLength = 100,
                                const string& regexPattern = "") {
        string input;
        int attempts = 0;
        const int maxAttempts = 3;

        while (attempts < maxAttempts) {
            try {
                cout << prompt;
                getline(cin, input);

                // Trim whitespace
                input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
                    return !isspace(ch);
                }));
                input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
                    return !isspace(ch);
                }).base(), input.end());

                if (!allowEmpty && input.empty()) {
                    throw runtime_error("Input cannot be empty.");
                }

                if (input.length() < minLength) {
                    throw runtime_error("Input must be at least " + to_string(minLength) + " characters.");
                }

                if (input.length() > maxLength) {
                    throw runtime_error("Input cannot exceed " + to_string(maxLength) + " characters.");
                }

                if (!regexPattern.empty() && !regex_match(input, regex(regexPattern))) {
                    throw runtime_error("Input format is invalid.");
                }

                return input;

            } catch (const runtime_error& e) {
                printError(string(e.what()));
            } catch (const exception& e) {
                printError("Unexpected error: " + string(e.what()));
            }

            attempts++;
            if (attempts < maxAttempts) {
                printInfo("Attempts remaining: " + to_string(maxAttempts - attempts));
            }
        }

        printError("Maximum attempts exceeded. Returning to menu.");
        return ""; // Error indicator
    }

    // Specialized input functions
    static string getUsername(const string& prompt = "Username: ") {
        return getStringInput(prompt, false, 3, 20, "^[a-zA-Z0-9_]+$");
    }

    static string getPassword(const string& prompt = "Password: ") {
        return getStringInput(prompt, false, 4, 50);
    }

    static string getISBN(const string& prompt = "ISBN: ") {
        return getStringInput(prompt, false, 10, 20, "^[0-9-]+$");
    }

    static string getDate(const string& prompt = "Date (DD/MM/YYYY): ") {
        string date;
        int attempts = 0;
        const int maxAttempts = 3;

        while (attempts < maxAttempts) {
            date = getStringInput(prompt, false, 10, 10, "^\\d{2}/\\d{2}/\\d{4}$");

            if (date.empty()) return ""; // Error from getStringInput

            // Basic date validation
            try {
                int day = stoi(date.substr(0, 2));
                int month = stoi(date.substr(3, 2));
                int year = stoi(date.substr(6, 4));

                if (month < 1 || month > 12) {
                    throw runtime_error("Invalid month. Must be between 01-12.");
                }

                if (day < 1 || day > 31) {
                    throw runtime_error("Invalid day. Must be between 01-31.");
                }

                if (year < 2020 || year > 2030) {
                    throw runtime_error("Invalid year. Must be between 2020-2030.");
                }

                // Basic month-day validation
                if ((month == 2 && day > 29) ||
                    ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) {
                    throw runtime_error("Invalid day for the selected month.");
                }

                return date;

            } catch (const runtime_error& e) {
                printError(string(e.what()));
            } catch (const exception&) {
                printError("Invalid date format. Use DD/MM/YYYY.");
            }

            attempts++;
            if (attempts < maxAttempts) {
                printInfo("Attempts remaining: " + to_string(maxAttempts - attempts));
            }
        }

        printError("Maximum attempts exceeded. Returning to menu.");
        return "";
    }

    static float getFloatInput(const string& prompt, float minVal = -FLT_MAX, float maxVal = FLT_MAX) {
        float value;
        int attempts = 0;
        const int maxAttempts = 3;

        while (attempts < maxAttempts) {
            try {
                cout << prompt;
                string input;
                getline(cin, input);

                // Remove whitespace
                input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

                if (input.empty()) {
                    throw runtime_error("Input cannot be empty.");
                }

                // Check if input is a valid float
                if (!regex_match(input, regex("^-?\\d*\\.?\\d+$"))) {
                    throw runtime_error("Input must be a valid number.");
                }

                value = stof(input);

                if (value < minVal || value > maxVal) {
                    throw runtime_error("Value must be between " + to_string(minVal) +
                                      " and " + to_string(maxVal) + ".");
                }

                return value;

            } catch (const out_of_range&) {
                printError("Number is out of valid range.");
            } catch (const runtime_error& e) {
                printError(string(e.what()));
            } catch (const exception& e) {
                printError("Invalid number format. Please try again.");
            }

            attempts++;
            if (attempts < maxAttempts) {
                printInfo("Attempts remaining: " + to_string(maxAttempts - attempts));
            }
        }

        printError("Maximum attempts exceeded. Returning to menu.");
        return -FLT_MAX; // Error indicator
    }

    // Confirmation dialog
    static bool getConfirmation(const string& message) {
        string response;
        int attempts = 0;
        const int maxAttempts = 3;

        while (attempts < maxAttempts) {
            cout << "\n" << message << " (y/n): ";
            getline(cin, response);

            // Convert to lowercase
            transform(response.begin(), response.end(), response.begin(), ::tolower);

            if (response == "y" || response == "yes") {
                return true;
            } else if (response == "n" || response == "no") {
                return false;
            } else {
                printError("Please enter 'y' for yes or 'n' for no.");
            }

            attempts++;
        }

        printError("Maximum attempts exceeded. Assuming 'no'.");
        return false;
    }

    // Pause with custom message
    static void pause(const string& message = "Press Enter to continue...") {
        cout << "\n" << message;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Progress indicator
    static void showProgress(const string& message, int current, int total) {
        if (total <= 0) return;

        int percentage = (current * 100) / total;
        int barWidth = 40;
        int filledWidth = (current * barWidth) / total;

        cout << "\r" << message << " [";
        for (int i = 0; i < barWidth; ++i) {
            if (i < filledWidth) cout << "█";
            else cout << "░";
        }
        cout << "] " << percentage << "% (" << current << "/" << total << ")" << flush;

        if (current == total) cout << "\n";
    }

private:
    // Center text within a given width
    static string centerText(const string& text, int width) {
        if (static_cast<int>(text.length()) >= width) return text.substr(0, width);

        int totalPadding = width - static_cast<int>(text.length());
        int leftPadding = totalPadding / 2;
        int rightPadding = totalPadding - leftPadding;
        return string(leftPadding, ' ') + text + string(rightPadding, ' ');
    }
};

#endif // UIUTILS_H
