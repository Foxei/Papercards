add_executable(Papercards-QML ${QT_RES}
    src/papercards_qml.cpp
    src/Backend.cpp
  src/model/Card.cpp)

target_include_directories(Papercards-QML PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

qt5_use_modules(Papercards-QML Core Gui Qml Quick QuickControls2)
