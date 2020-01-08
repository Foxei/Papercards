add_executable(Papercards ${QT_RES}
    src/papercards.cpp
    src/view/MainWindow.cpp
    src/view/card/CardEditor.cpp
    src/view/card/DualCardView.cpp
    src/view/card/CardEditorBackground.cpp
    src/view/card/CardEditorToolBar.cpp
    src/view/base/StatusBar.cpp
    src/view/base/ScalableVBoxLayout.cpp
    src/view/base/ScalableLineEdit.cpp
    src/view/base/ScalableTextEdit.cpp
    src/view/card/CardView.cpp
    src/view/View.cpp
    src/controller/Controller.cpp
    src/model/utility/JsonParser.cpp
    src/model/Model.cpp
    src/model/Card.cpp
    src/model/Field.cpp)

target_include_directories(Papercards PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

qt5_use_modules(Papercards Widgets)
