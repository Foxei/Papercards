add_executable(Papercards ${QT_RES}
    src/papercards.cpp
    src/view/MainWindow.cpp
    src/view/card/CardEditor.cpp
    src/view/card/DualCardView.cpp
    src/view/card/CardEditorBackground.cpp
    src/view/card/CardEditorToolbar.cpp)
qt5_use_modules(Papercards Widgets)
