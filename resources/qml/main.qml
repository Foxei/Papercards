import QtQuick 2.6
import QtQuick.Controls 2.5
import io.papercards.backend 1.0
import QtQuick.Controls.Material 2.12

import "components" as Components

ApplicationWindow {

    id: root
    visible: true
    title: "Papercards"
    width: 800
    height: 600

    header: Components.EditorToolbar{

    }


    Pane {
        anchors.fill: parent
        TextField {
            placeholderText: qsTr("User name")
            anchors.centerIn: parent
        }
    }
}