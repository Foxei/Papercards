import QtQuick 2.14
import QtGraphicalEffects 1.14
import QtQuick.Controls.Material 2.14

Item{
    id: container
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
        color: "#B00020"
        cached: true
    }
}

