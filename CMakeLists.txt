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
find_package(Qt5 COMPONENTS Quick Core Network Qml Gui Widgets QuickControls2 Widgets REQUIRED)
message(STATUS "QT_VERSION : ${Qt5_VERSION} ")

set(QT_RES
    ${CMAKE_SOURCE_DIR}/resources/resources.qrc
    ${CMAKE_SOURCE_DIR}/gui/gui.qrc)

# Targets that we develop here
set(SRC ${QT_RES}
    src/papercards_qml.cpp
    src/Backend.cpp
    src/DocumentHandler.cpp
    src/model/Card.cpp)

add_executable(Papercards ${SRC})
if (APPLE)
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE TRUE)
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Papercards" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_EXECUTABLE_NAME "Papercards" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_INFO_STRING "Papercards - Version 0.1.1" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION "0.1.1" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "0.1.1" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1.1" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER "com.teamkoeln.Papercards" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_COPYRIGHT "Copyright © 2019–2020 Simon Schäfer. All rights reserved." )
  # Change following line to point to actual icns file in bundle.
  #set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_ICON_FILE "atom.icns" )
  set_target_properties(Papercards PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/resources/MacOSXBundleInfo.plist.in")
endif()

target_include_directories(Papercards PRIVATE src)
target_link_libraries(Papercards Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Qml Qt5::Quick Qt5::QuickControls2)
