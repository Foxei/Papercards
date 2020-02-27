import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.2


Pane {
    property int cardId: 0
    property real cardWidth: 148
    property real cardHeight: 105

    Layout.preferredWidth: cardWidth*Screen.pixelDensity
    Layout.preferredHeight: cardHeight*Screen.pixelDensity

    Material.elevation: 6
    Material.theme: Material.Light

    ColumnLayout {
        anchors.fill: parent
        TextField {
            Layout.fillWidth: true

            placeholderText: "Enter question here."
        }
        TextArea {
            Layout.fillWidth: true
            Layout.fillHeight: true

            placeholderText: "Enter answere here."

            id: textArea
            textFormat: Qt.RichText
            wrapMode: TextArea.Wrap
            focus: true
            selectByMouse: true
            persistentSelection: true

            leftPadding: 6
            rightPadding: 6
            topPadding: 0
            bottomPadding: 0

            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
}
