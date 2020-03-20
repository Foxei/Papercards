cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(Papercards VERSION 0.1 LANGUAGES CXX)

# Set CMake policy to suppres warning of boost
# cmake_policy(SET CMP0074 NEW)

# Set CMake flag to work with Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Enable C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED 14)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

# Finding Qt
find_package(Qt5 COMPONENTS Quick Core Network Qml Gui Widgets QuickControls2 REQUIRED)
message(STATUS "QT_VERSION : ${Qt5_VERSION} ")

set(QT_RES
    ${CMAKE_SOURCE_DIR}/resources/resources.qrc
    ${CMAKE_SOURCE_DIR}/gui/gui.qrc)

# Targets that we develop here
add_subdirectory(src)
