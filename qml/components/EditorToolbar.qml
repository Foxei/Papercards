import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import io.qt.examples.backend 1.0

ToolBar{
    RowLayout {
        Button {
            Image {
                source: "clipboard.png"
            }
        }
        anchors.fill: parent
        ToolButton {
            text: qsTr("‹")
            onClicked: stack.pop()
        }
        Label {
            text: "Title"
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }
        ToolButton {
            text: qsTr("⋮")
            onClicked: menu.open()
        }
    }
}