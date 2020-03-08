import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.12
import io.papercards.backend 1.0

/**
 * @brief QML implementation of the status bar on the bottom of the screen.
 * @details
 */
Pane {
    id: statusBar
    property real scaleFactor: 1.0

    padding: 0
    leftPadding: 10
    rightPadding: 10

    Material.background: Material.primary

    onScaleFactorChanged: {
        scaleSlider.value = scaleFactor * 100.0;
    }

    RowLayout {
        anchors.fill: parent
        spacing: 1

        Label {
            text: "Ready!"
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            Label {
                text: "50%"
                Layout.alignment: Qt.AlignRight
            }

            Slider {
                id: scaleSlider
                from: 50
                stepSize:1
                to: 150
                value: scaleFactor*100.0
                snapMode: Slider.SnapAlways
                Layout.alignment: Qt.AlignRight
                onMoved: {
                    statusBar.scaleFactor = value/100.0;
                }
            }

            Label {
                text: "150%"
                Layout.alignment: Qt.AlignRight
            }

        }

    }
}
