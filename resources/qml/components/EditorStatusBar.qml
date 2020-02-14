import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.12
import io.papercards.backend 1.0

Pane {
    property real scale_factor: 1.0

    padding: 0
    leftPadding: 10
    rightPadding: 10

    Material.background: Material.primary

    RowLayout {
        anchors.fill: parent
        spacing: 1

        Label {
            text: "Ready!"
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            Label {
                text: "100%"
                Layout.alignment: Qt.AlignRight
            }

            Slider {
                from: 100
                stepSize:1
                to: 200
                value: scale_factor*100.0
                snapMode: Slider.SnapAlways
                Layout.alignment: Qt.AlignRight

                onMoved: {
                    scale_factor = value/100.0;
                }
            }

            Label {
                text: "200%"
                Layout.alignment: Qt.AlignRight
            }

        }

    }
}