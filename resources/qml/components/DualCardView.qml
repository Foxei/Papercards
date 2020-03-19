import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import io.papercards.backend 1.0

Pane {
    property real scaleFactor: 1.0
    property real contentHeightBuffer: contentPane.height*scaleFactor
    property real contentWidthBuffer: contentPane.width*scaleFactor

    padding: 0

    ScrollView {
        id: contentScroll
        anchors.fill: parent
        contentWidth: Math.max(parent.width,contentWidthBuffer)
        contentHeight: contentHeightBuffer

        Pane{
            id: contentPane
            anchors.centerIn: parent
            scale: scaleFactor

            ColumnLayout {

                CardView {
                    Layout.alignment: Qt.AlignCenter
                }

                CardView {
                    Layout.alignment: Qt.AlignCenter
                }

                CardView {
                    Layout.alignment: Qt.AlignCenter
                }
            }
        }
    }
}
