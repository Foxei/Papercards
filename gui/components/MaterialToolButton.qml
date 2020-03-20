import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Window 2.14

ToolButton {
    font.family: "Material Icons"
    font.pointSize: Screen.devicePixelRatio*16
    ToolTip.delay: 200
    ToolTip.visible: hovered
}

