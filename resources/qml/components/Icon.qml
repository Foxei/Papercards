import QtQuick 2.9
import QtGraphicalEffects 1.0

Item{
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
        color: "#FFFFFF"
        cached: true
    }
}

