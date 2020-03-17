import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
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
