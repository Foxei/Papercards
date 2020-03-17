import QtQuick 2.6
import QtQuick.Controls 2.2
import io.papercards.backend 1.0
import QtQuick.Controls.Material 2.2

import "components" as Components

ApplicationWindow {
    property real scaleFactor: 1.0

    id: root
    visible: true
    title: "Papercards"
    width: 800
    height: 600

    /*MouseArea {
    anchors.fill: parent
        onWheel: {
            if (wheel.modifiers & Qt.ControlModifier) {
                var scaleFactorBuffer = scaleFactor + (wheel.angleDelta.y/1200);

                if(scaleFactorBuffer > 2.0){
                    scaleFactorBuffer = 2.0;
                }else if(scaleFactorBuffer < 1.0){
                    scaleFactorBuffer = 1.0;
                }
                scaleFactor = scaleFactorBuffer;
            }
        }
    }*/

    onScaleFactorChanged: {
        cardView.scaleFactor = scaleFactor;
        statusBar.scaleFactor = scaleFactor;
    }

    header: Components.EditorToolBar{

    }

    footer: Components.EditorStatusBar{
        id: statusBar
        onScaleFactorChanged: {
            root.scaleFactor = statusBar.scaleFactor
        }
    }

    Components.DualCardView {
        id: cardView
        anchors.fill: parent
    }
}
