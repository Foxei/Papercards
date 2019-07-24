cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(Papercards VERSION 0.1 LANGUAGES CXX)

# Set CMake policy to suppres warning of boost
cmake_policy(SET CMP0074 NEW)

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
find_package(Qt5Widgets 5.10 REQUIRED)
message(STATUS "------> QT_VERSION : ${Qt5Widgets_VERSION} " )

# Include Boost as an imported target
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

set(QT_RES ${CMAKE_CURRENT_SOURCE_DIR}/res/res.qrc)
# Targets that we develop here
add_subdirectory(src)