import QtQuick 2.6
import QtQuick.Controls 2.5
import io.papercards.backend 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.12

Pane {
    property real scaleFactor: 1.0

    scale: scaleFactor

    ColumnLayout {
        Pane {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100
            Material.elevation: 6
            Material.background: "white"

            //anchors.fill: parent
            Label {
                text: "Test Content"
                Material.foreground: "black"
                anchors.centerIn: parent
            }
        }

        Pane {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100
            Material.elevation: 6
            Material.background: "white"

            //anchors.fill: parent
            Label {
                text: "Test Content"
                Material.foreground: "black"
                anchors.centerIn: parent
            }
        }
    }
}