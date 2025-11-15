# cmake_minimum_required(VERSION 3.16)
# project(FinanceManagerApp LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)    # handles any .ui files you may add

# # Always bring in Core and Gui with Widgets
# # CRITICAL: This is correct, ensuring the Charts module is found.
# find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

# qt_standard_project_setup()

# qt_add_executable(FinanceManagerApp
#     main.cpp
#     loginwindow.h
#     loginwindow.cpp
#     mainwindow.h
#     mainwindow.cpp
#     transaction.h             # keep only header if there is no .cpp
#     # : Your file list contains 'financemanager.h/cpp' and 'transactionmanager.h/cpp'.
#     # Assuming 'transactionmanager' is the correct one based on your C++ code.
#     # financemanager.h
#     # financemanager.cpp
#     transactionmanager.h
#     transactionmanager.cpp
#     transactiondialog.h
#     transactiondialog.cpp
#     transactiontablemodel.h transactiontablemodel.cpp
# )

# target_link_libraries(FinanceManagerApp PRIVATE
#     Qt6::Core
#     Qt6::Gui
#     Qt6::Widgets
#     # FIX: You must link the Charts module to the executable!

# )

# # optional but tidy: put the binary under /bin
# set_target_properties(FinanceManagerApp PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )
cmake_minimum_required(VERSION 3.16)
project(FinanceManagerApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# --- Find Qt Packages ---
# CRITICAL FIX: Include the specific components used in the project,
# especially 'Charts' if you plan on adding graphs later.
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

# Standard project setup for Qt6
qt_standard_project_setup()

# --- Define the Executable and Source Files ---
# Ensure all headers (.h) and source files (.cpp) are listed.
# Note: 'loginwindow.h/cpp' is assumed to exist but was not provided.
qt_add_executable(FinanceManagerApp
    main.cpp
    loginwindow.h
    loginwindow.cpp
    mainwindow.h
    mainwindow.cpp

    transaction.h
    transactionmanager.h
    # CRITICAL: This is the file the linker needs, and it is correctly listed.
    transactionmanager.cpp

    transactiondialog.h
    transactiondialog.cpp

    # NEW: The Model files
    transactiontablemodel.h
    transactiontablemodel.cpp
)

# --- Link Libraries ---
# Link all required Qt components. This is where the Charts dependency is added.
target_link_libraries(FinanceManagerApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    # FIX: Explicitly link the Charts module for it to be included at build time.
    Qt6::Charts
)

# optional but tidy: put the binary under /bin
set_target_properties(FinanceManagerApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
