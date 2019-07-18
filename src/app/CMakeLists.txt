add_executable(Papercards src/papercards.cpp
    src/view/MainWindow.cpp
    src/view/card/CardEditor.cpp src/view/card/CardView.cpp src/view/card/CardView.h)
qt5_use_modules(Papercards Widgets)
