cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem CXX)

# Force C++17
if(NOT MSVC)
    set(CMAKE_CXX_FLAGS_INIT "-std=c++17")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
    add_compile_options(/std:c++latest)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O2")
    if(NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()
endif()

# Output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/core/UserFactory.cpp
    src/entities/Admin.cpp
    src/entities/Member.cpp
    src/entities/Librarian.cpp
    src/entities/Guest.cpp
)

# Header files
set(HEADERS
    include/ui/UIUtils.h
    include/models/User.h
    include/models/Book.h
    include/models/BorrowRecord.h
    include/models/Fine.h
    include/core/LibraryManager.h
    include/core/UserFactory.h
    include/core/SystemInitializer.h
    include/entities/Admin.h
    include/entities/Member.h
    include/entities/Librarian.h
    include/entities/Guest.h
)

# Create executable
add_executable(LibraryManagementSystem ${SOURCES} ${HEADERS})

# Platform-specific settings
if(MSVC)
    set_target_properties(LibraryManagementSystem PROPERTIES
        COMPILE_FLAGS "/EHsc"
    )
endif()

# Optional: Create install target
install(TARGETS LibraryManagementSystem DESTINATION bin)

# Print configuration info
message(STATUS "")
message(STATUS "========== Library Management System Configuration ==========")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Executable Output: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "============================================================")
