import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.2

Item{
    id: container
    anchors.fill: parent
    property url iconSource
    Image {
        id: image
        source: iconSource
        anchors.centerIn: parent
        sourceSize: Qt.size(24,24)
        smooth: true
        visible: false
    }
    ColorOverlay {
        anchors.fill: image
        source: image
        color: !container.enabled ? container.Material.hintTextColor :
                container.checked || container.highlighted ? container.Material.accent : container.Material.foreground
        cached: true
    }
}

