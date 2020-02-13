# Define library. Only source files here!
project(libpapercardsmodel VERSION 0.1 LANGUAGES CXX)

add_library(papercardsmodel SHARED
    src/Model.cpp
    src/Card.cpp
    src/Field.cpp
    src/utility/JsonParser.cpp
    include/papercardsmodel/Card.h
    include/papercardsmodel/Model.h
    include/papercardsmodel/Field.h)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(papercardsmodel PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# Depend on a library that we defined in the top-level file
qt5_use_modules(papercardsmodel Core)
qt5_use_modules(papercardsmodel Gui)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS papercardsmodel EXPORT PapercardsModelConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT PapercardsModelConfig DESTINATION share/PapercardsModel/cmake)

# This makes the project importable from the build directory
export(TARGETS papercardsmodel FILE PapercardsModelConfig.cmake)