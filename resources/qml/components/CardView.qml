import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.2
import io.papercards.card 1.0
import io.papercards.backend 1.0


Pane {
    property int cardId: 0
    property real cardWidth: BackEnd.current_card.card_size.width
    property real cardHeight: BackEnd.current_card.card_size.height

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

            padding: 0

            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
}
