import QtQuick 2.9
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Material 2.2
import QtQuick.Controls.Material.impl 2.2

T.ToolBar {
    id: control

    Material.elevation: 4

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    Material.foreground: Material.toolTextColor

    spacing: 0

    background: Rectangle {
        implicitHeight: 48
        color: control.Material.toolBarColor

        layer.enabled: control.Material.elevation > 0
        layer.effect: ElevationEffect {
            elevation: control.Material.elevation
            fullWidth: true
        }
    }
}
