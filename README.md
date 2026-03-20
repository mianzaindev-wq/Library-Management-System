# 📚 Library Management System

A professional, feature-rich library management system built with C++ using modern Object-Oriented Programming principles and design patterns. This application provides a terminal-based UI for managing books, handling user accounts, and tracking borrowing records with enhanced error handling and user experience.

## ✨ Features

### 🔐 User Management System
- **👑 Admin Panel**: Complete system control with user and book management capabilities
- **👨‍💼 Librarian Dashboard**: Book catalog management and borrow history tracking
- **👤 Member Account**: Personal borrowing, searching, and fine management
- **🏠 Guest Mode**: Browse the library catalog without authentication

### 📚 Advanced Book Management
- ➕ Add and remove books from the library collection
- 🔍 Search books by title, author, or ISBN
- 📊 Track book availability in real-time
- 📖 Manage multiple copies of the same book
- 🏷️ Organize books by genre and author

### 📋 Comprehensive Record Management
- 📝 Track all borrowing and returning transactions
- 💰 Calculate overdue fines automatically
- 📈 Generate system reports and statistics
- 👀 View borrowing history per member or system-wide

### 🎯 Design Patterns & Architecture
- **🏗️ Singleton Pattern**: Central LibraryManager instance
- **🏭 Factory Pattern**: Flexible user object creation
- **🔗 Inheritance**: Role-based user class hierarchy
- **🔒 Encapsulation**: Clean data abstraction and security

## 🏗️ Project Architecture

### Architecture Layers

```
LibraryManagementSystem/
├── src/                          # Source files
│   ├── main.cpp                  # Application entry point
│   ├── core/                     # Core business logic
│   │   ├── UserFactory.cpp       # User creation factory
│   │   └── SystemInitializer.cpp # System setup
│   ├── models/                   # Data models (header-only)
│   └── entities/                 # User role implementations
│       ├── Admin.cpp
│       ├── Member.cpp
│       ├── Librarian.cpp
│       └── Guest.cpp
│
├── include/                      # Header files
│   ├── ui/                       # UI utilities
│   │   └── UIUtils.h             # Enhanced terminal UI
│   ├── models/                   # Data model definitions
│   │   ├── User.h               # Abstract user base class
│   │   ├── Book.h               # Book entity
│   │   ├── BorrowRecord.h       # Transaction records
│   │   └── Fine.h               # Fine calculation
│   ├── core/                    # Core system components
│   │   ├── LibraryManager.h     # Central system controller
│   │   ├── UserFactory.h        # User creation factory
│   │   └── SystemInitializer.h  # System initialization
│   └── entities/                # User role definitions
│       ├── Admin.h
│       ├── Member.h
│       ├── Librarian.h
│       └── Guest.h
│
├── build/                       # Build artifacts (generated)
├── docs/                        # Documentation (legacy)
├── CMakeLists.txt               # Cross-platform build configuration
├── LICENSE                      # MIT License
└── README.md                    # This file
```

### Design Patterns Implementation

#### 1. Singleton Pattern
```cpp
class LibraryManager {
    static LibraryManager* instance;
public:
    static LibraryManager* getInstance() {
        if (instance == nullptr) {
            instance = new LibraryManager();
        }
        return instance;
    }
};
```
**Purpose:** Ensures a single instance of the library manager across the application.

#### 2. Factory Pattern
```cpp
class UserFactory {
    static User* createUser(const string& role,
                           const string& uname,
                           const string& pwd);
};
```
**Purpose:** Encapsulates user object creation based on role type.

#### 3. Inheritance & Polymorphism
```cpp
class User (abstract)
    ├── Admin       // Full system control
    ├── Member      // Borrowing capabilities
    ├── Librarian   // Catalog management
    └── Guest       // Read-only access
```
**Purpose:** Role-based hierarchy allowing different menu implementations per user type.

## 🚀 Installation & Building

### Prerequisites

#### Windows
- Visual Studio 2019+ or MinGW-w64
- CMake 3.10 or higher
- C++17 compatible compiler

#### Linux
- GCC 9.0+ or Clang 10.0+
- CMake 3.10 or higher
- Build tools (`build-essential` on Ubuntu/Debian)

#### macOS
- Xcode Command Line Tools
- CMake 3.10 or higher
- Clang with C++17 support

### Build Instructions

#### Windows (Visual Studio - Recommended)
```bash
cd "Library Management System"
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
```

#### Windows (MinGW)
```bash
cd "Library Management System"
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

#### Linux/macOS
```bash
cd "Library Management System"
mkdir build
cd build
cmake ..
make
```

### Running the Application
```bash
# From build directory
cd bin
./LibraryManagementSystem        # Linux/macOS
./LibraryManagementSystem.exe    # Windows
```

## 🎮 Usage Guide

### Default Login Credentials
- **Admin**: username: `admin`, password: `admin123`
- **Librarian**: username: `librarian`, password: `lib123`
- **Member**: username: `member`, password: `mem123`

### Main Menu Options
1. **Login to Your Account** - Access role-specific features
2. **Browse as Guest** - View catalog without login
3. **Exit Application** - Close the program

### Admin Features
- ➕ Add/Remove users and books
- 📊 Generate system reports
- 👀 View all borrowing history
- ⚙️ Full system management

### Librarian Features
- ➕ Add/Remove books
- 📖 View all books
- 📋 Check borrowing history
- ⏰ Manage pending returns

### Member Features
- 🔍 Search for books
- 📚 Borrow/Return books
- 💰 Check fines
- 📋 View personal history

### Guest Features
- 🔍 Search books
- 📖 Browse catalog
- 👀 View available books

## 🔧 Technical Details

### Enhanced UI/UX Features
- 🎨 **Color-coded messages** with icons
- ✅ **Robust input validation** with error recovery
- 📋 **Professional table formatting**
- ⌨️ **Specialized input functions** (dates, ISBN, etc.)
- 🔄 **Progress indicators** for long operations
- ❓ **Confirmation dialogs** for critical actions

### Error Handling
- 🚨 **Exception-safe operations**
- 🔄 **Multiple retry attempts** for input
- 📝 **Detailed error messages**
- 🛡️ **Input sanitization** and validation
- ⚡ **Graceful failure recovery**

### Build System
- 🏗️ **CMake-based** cross-platform builds
- 📦 **Automatic dependency management**
- 🎯 **Release/Debug configurations**
- 🌐 **Platform-specific optimizations**

## 📊 System Requirements

### Minimum Requirements
- **OS**: Windows 10+, Ubuntu 18.04+, macOS 10.14+
- **RAM**: 512 MB
- **Storage**: 50 MB
- **Compiler**: C++17 compatible

### Recommended Requirements
- **OS**: Windows 11, Ubuntu 20.04+, macOS 12+
- **RAM**: 1 GB
- **Storage**: 100 MB
- **Compiler**: GCC 11+ or Clang 14+

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines
- Follow C++17 standards
- Use meaningful variable names
- Add comments for complex logic
- Test thoroughly before submitting
- Follow existing code style

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Built with modern C++ best practices
- Cross-platform compatibility
- Professional UI/UX design
- Comprehensive error handling
- Extensible architecture

## 📞 Support

For questions, issues, or contributions:
- Create an issue on GitHub
- Check existing documentation
- Review code comments for implementation details

---

**Happy Reading! 📖✨**
│   │   ├── User.h
│   │   ├── Book.h
│   │   ├── BorrowRecord.h
│   │   └── Fine.h
│   ├── core/                     # Core system
│   │   ├── LibraryManager.h      # Main system manager
│   │   ├── UserFactory.h
│   │   └── SystemInitializer.h   # Initial data setup
│   └── entities/                 # User role definitions
│       ├── Admin.h
│       ├── Member.h
│       ├── Librarian.h
│       └── Guest.h
│
├── build/                        # Build output directory
├── docs/                         # Documentation files
├── CMakeLists.txt               # Build configuration
├── README.md                     # This file
├── .gitignore                   # Git ignore rules
└── LICENSE                       # MIT License
```

## Prerequisites

- **C++17** or higher
- **CMake 3.10** or higher
- **Windows/Linux/Mac** with a compatible C++ compiler
  - MSVC (Windows)
  - GCC/Clang (Linux)
  - Clang (macOS)

## Building the Project

### Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Configure project
cmake ..

# Build project
cmake --build . --config Release

# Or compile directly
cmake --build .
```

### On Windows (with Visual Studio)

```bash
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..
cmake --build . --config Release
```

### On Linux/Mac

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Application

### After Building

```bash
# Navigate to build output
cd build/bin

# Run the executable
./LibraryManagementSystem    # Linux/Mac
LibraryManagementSystem.exe  # Windows
```

### Default Login Credentials

Username: `admin`  
Password: `admin`

## Usage Guide

### Admin Functions
1. Add/Remove books
2. Add/Remove users
3. View all books and borrow history
4. Generate system reports
5. Manage library statistics

### Librarian Functions
1. Add/Remove books from catalog
2. View all books and transactions
3. Monitor pending returns
4. View borrowing history
5. Manage library operations

### Member Functions
1. Search for books
2. Borrow books
3. Return books and pay fines
4. View borrowing history
5. Check outstanding fines

### Guest Mode
1. Search for books
2. View all available books
3. Check book availability and details

## Key Components

### UIUtils
Comprehensive terminal UI utilities providing:
- Clear, formatted menus
- Input validation
- Table formatting
- Color-coded messages (success, error, info, warning)
- Cross-platform compatibility

### LibraryManager
Singleton core system managing:
- Book inventory
- User authentication
- Borrow transactions
- Fine calculations
- System reports

### User Roles
- **User** (Abstract Base)
- **Admin**: System administrator
- **Librarian**: Library staff
- **Member**: Registered member
- **Guest**: Anonymous visitor

## Fine Calculation

- Default fine rate: **₹100 per day** late
- Automatically calculated when books are returned late
- Fine amount stored with borrow record
- Members can check outstanding fines anytime

## Technical Highlights

- **Object-Oriented Design**: Inheritance, polymorphism, encapsulation
- **Design Patterns**: Singleton, Factory
- **Cross-Platform**: Works on Windows, Linux, macOS
- **Clean Code**: Well-organized, documented, maintainable
- **Error Handling**: Comprehensive input validation
- **Memory Management**: Proper allocation and deallocation

## Future Enhancements

- [ ] Database integration (SQLite/MySQL)
- [ ] File persistence for data storage
- [ ] GUI interface using Qt or ImGui
- [ ] Email notifications for book availability
- [ ] Member reservation system
- [ ] Book ratings and reviews
- [ ] Advanced search filters
- [ ] Mobile app integration via REST API

## License

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

## Author

**Rana's Library Management System**

A demonstration of professional C++ software development with Object-Oriented principles and design patterns.

## Contributing

Contributions are welcome! Please feel free to submit pull requests with improvements, bug fixes, or new features.

## Troubleshooting

### Build Issues

**Problem**: CMake not found
```bash
# Solution: Install CMake
# Windows: Download from cmake.org
# Linux: sudo apt-get install cmake
# Mac: brew install cmake
```

**Problem**: C++ compiler not found
```bash
# Solution: Install compiler
# Windows: Install Visual Studio Build Tools
# Linux: sudo apt-get install build-essential
# Mac: xcode-select --install
```

### Runtime Issues

**Problem**: Can't login
- Check credentials (default: admin/admin)
- Ensure system initialized properly

**Problem**: Borrow/Return not working
- Verify date format (DD/MM/YYYY)
- Check book title spelling exactly

## Support

For issues and questions, please open an issue on the GitHub repository.

---

**Version**: 2.0  
**Last Updated**: March 2026  
**Status**: Active Development
