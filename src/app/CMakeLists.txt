add_executable(Papercards src/papercards.cpp
    src/view/MainWindow.cpp
    src/view/card/CardEditor.cpp src/view/card/DualCardView.cpp src/view/card/DualCardView.h src/view/card/CardEditorBackground.cpp src/view/card/CardEditorBackground.h src/view/card/CardEditorToolbar.cpp src/view/card/CardEditorToolbar.h)
qt5_use_modules(Papercards Widgets)
