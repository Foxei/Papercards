TEMPLATE = app
QT += core gui quick quickcontrols2 widgets
CONFIG += c++14

VERSION = 0.1.0

VERSIONS = $$split(VERSION, ".")
DEFINES += MAJOR_VERSION=$$member(VERSIONS, 0)
DEFINES += MINOR_VERSION=$$member(VERSIONS, 1)
DEFINES += REVISION=$$member(VERSIONS, 2)
#ICON = not set

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/papercards_qml.cpp src/Backend.cpp src/DocumentHandler.cpp src/model/Card.cpp \
    src/mainwindow.cpp
HEADERS += src/Backend.h src/DocumentHandler.h src/model/Card.h \
    src/mainwindow.h \
    src/material_icons.h

RESOURCES += resources/resources.qrc gui/gui.qrc \
    ui/ui.qrc

OTHER_FILES += gui/*.qml gui/components/*.qml


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/mainwindow.ui
