add_executable(Papercards-QML ${QT_RES}
    papercards_qml.cpp
    Backend.cpp
    DocumentHandler.cpp
    model/Card.cpp)

target_include_directories(Papercards-QML PRIVATE app_qml/src)

qt5_use_modules(Papercards-QML Core Gui Qml Quick QuickControls2)