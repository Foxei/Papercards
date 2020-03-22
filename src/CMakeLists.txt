set(SRC ${QT_RES}
    papercards_qml.cpp
    Backend.cpp
    DocumentHandler.cpp
    model/Card.cpp)
if (APPLE)
  add_executable(Papercards MACOSX_BUNDLE ${SRC})
else ()
  add_executable(Papercards ${SRC})
endif()

target_include_directories(Papercards PRIVATE src)

qt5_use_modules(Papercards Core Gui Qml Quick QuickControls2 Widgets)