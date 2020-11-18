import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

ApplicationWindow {

    id: root
    visible: true
    title: "Papercards"
    width: 800
    height: 600

    ToolBar {
        id: toolBar
        height: 40
        position: ToolBar.Header
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Switch {
        id: element
        x: 228
        y: 310
        text: qsTr("Test")
    }

}

/*##^##
Designer {
    D{i:1;anchors_width:800;anchors_x:-6;anchors_y:0}
}
##^##*/
