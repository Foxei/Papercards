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

    MouseArea {
        anchors.fill: parent
        onWheel: {
            if (wheel.modifiers & Qt.ControlModifier) {
                console.log(wheel.angleDelta.y);
            }
        }
     }

    header: Components.EditorToolBar{

    }

    Components.DualCardView {
        id: cardView
        anchors.centerIn: parent
        scaleFactor: statusBar.scaleFactor
    }

    footer: Components.EditorStatusBar{
        id: statusBar
        scaleFactor: cardView.scaleFactor
    }
}