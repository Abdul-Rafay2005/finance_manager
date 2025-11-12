cmake_minimum_required(VERSION 3.16)

project(FinanceManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 modules
find_package(Qt6 6.9 REQUIRED COMPONENTS Widgets Sql)

# Source files
set(SOURCES
    src/main.cpp
    src/LoginWindow.cpp
    src/MainWindow.cpp
    src/TransactionDialog.cpp
    src/CategoryDialog.cpp
    src/ReportWindow.cpp
    src/SettingsDialog.cpp
    src/DatabaseManager.cpp
    src/UserManager.cpp
    src/Models/Transaction.cpp
    src/Models/Category.cpp
    src/Models/User.cpp
    src/Models/Budget.cpp
)

# Headers
set(HEADERS
    include/LoginWindow.h
    include/MainWindow.h
    include/TransactionDialog.h
    include/CategoryDialog.h
    include/ReportWindow.h
    include/SettingsDialog.h
    include/DatabaseManager.h
    include/UserManager.h
    include/Models/Transaction.h
    include/Models/Category.h
    include/Models/User.h
    include/Models/Budget.h
)

# UI files
set(UIS
    ui/LoginWindow.ui
    ui/MainWindow.ui
    ui/TransactionDialog.ui
    ui/CategoryDialog.ui
    ui/ReportWindow.ui
    ui/SettingsDialog.ui
)

# Resources (comment out if file doesn't exist yet)
set(RESOURCES
    # resources/resources.qrc
)

# Add executable (with MANUAL_FINALIZATION)
qt6_add_executable(FinanceManager
    MANUAL_FINALIZATION
    ${SOURCES}
    ${HEADERS}
    ${UIS}
    ${RESOURCES}
)

# Link Qt libraries
target_link_libraries(FinanceManager PRIVATE
    Qt6::Widgets
    Qt6::Sql
)

# Include directories
target_include_directories(FinanceManager PRIVATE include)

# Finalize Qt executable
qt_finalize_executable(FinanceManager)
