# Minimum version 3.10 to use imported targets
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
# Set project and version name
project(Papercards VERSION 0.1.0 LANGUAGES CXX)
# Set project name to lower case
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

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

# Finding Qt and print version
find_package(Qt5 COMPONENTS Quick Core Network Qml Gui Widgets QuickControls2 Widgets REQUIRED)
message(STATUS "QT_VERSION : ${Qt5_VERSION} ")

# Set Qt resources files
set(QT_RES
    ${CMAKE_SOURCE_DIR}/resources/resources.qrc
    ${CMAKE_SOURCE_DIR}/gui/gui.qrc)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui/)

# Set Qt source files
set(SRC ${QT_RES}
    src/papercards_qml.cpp
    src/mainwindow.cpp
    src/sidepanel.cpp)

# Copy version to source code
add_definitions(-DMAJOR_VERSION=${PROJECT_VERSION_MAJOR})
add_definitions(-DMINOR_VERSION=${PROJECT_VERSION_MINOR})
add_definitions(-DREVISION=${PROJECT_VERSION_PATCH})

# Add application
add_executable(${PROJECT_NAME} ${SRC})
# Add private include folder
target_include_directories(${PROJECT_NAME} PRIVATE src)
# Link application
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Qml Qt5::Quick Qt5::QuickControls2)

if (APPLE)
  # Setting application meta information
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_EXECUTABLE_NAME "${PROJECT_NAME}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME} - Version ${VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER "com.teamkoeln.${PROJECT_NAME}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT "Copyright © 2019–2020 Simon Schäfer. All rights reserved.")
  # Change following line to point to actual icns file in bundle.
  #set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_ICON_FILE "atom.icns")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/frameworks/MacOSXBundleInfo.plist.in")
elseif(UNIX)
  # Fix double click bug
  set(CMAKE_EXE_LINKER_FLAGS -no-pie)

  # Setting application meta information
  set(PROJECT_PATH "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")
  set(PROJECT_ICON "${CMAKE_BINARY_DIR}/${PROJECT_NAME_LOWER}-logo.png")

  # Copy launcher files
  file(COPY ${CMAKE_SOURCE_DIR}/frameworks/${PROJECT_NAME_LOWER}-logo.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
  configure_file(${CMAKE_SOURCE_DIR}/frameworks/${PROJECT_NAME_LOWER}.desktop.in ${PROJECT_NAME_LOWER}-launcher.desktop)
endif()