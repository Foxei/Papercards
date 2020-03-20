add_executable(Papercards ${QT_RES}
    papercards_qml.cpp
    Backend.cpp
    DocumentHandler.cpp
    model/Card.cpp)

target_include_directories(Papercards PRIVATE src)

qt5_use_modules(Papercards Core Gui Qml Quick QuickControls2)