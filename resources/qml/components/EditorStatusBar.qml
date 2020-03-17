import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
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
            Layout.alignment: Qt.AlignLeft
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            ToolButton {
                Icon{
                    iconSource: "qrc:/assets/zoom_out.png"
                }
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    scaleFactor = ((scaleSlider.value - 10) <  scaleSlider.from) ? (scaleSlider.value/100.0):((scaleSlider.value-10)/100.0);
                }
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

            ToolButton {
                Icon{
                    iconSource: "qrc:/assets/zoom_in.png"
                }
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    scaleFactor = ((scaleSlider.value + 10) >  scaleSlider.to) ? (scaleSlider.value/100.0):((scaleSlider.value+10)/100.0);
                }
            }

        }

    }
}
