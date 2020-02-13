import QtQuick 2.6
import QtQuick.Controls 2.0
import io.qt.examples.backend 1.0

import "./components" as Components

ApplicationWindow {
    id: root
    width: 300
    height: 480
    visible: true

    header: Components.EditorToolbar{

    }

    BackEnd {
        id: backend
    }

    TextField {
        text: backend.userName
        placeholderText: qsTr("User name")
        anchors.centerIn: parent

        onTextChanged: backend.userName = text
    }
}