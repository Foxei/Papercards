import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Window 2.3
import io.papercards.card 1.0
import io.papercards.backend 1.0


Pane {
    property Card card: BackEnd.current_card
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
            id: cardQuestionField
            objectName: "card-question"
            Layout.fillWidth: true
            font.pointSize: 20
            placeholderText: "Enter question here."
            text: card.card_question_text;

            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
            selectByMouse: true
            persistentSelection: true
            padding: 0

            onTextEdited: {
                card.card_question_text = cardQuestionField.text;
            }
        }
        TextArea {
            objectName: "card-answer"
            Layout.fillWidth: true
            Layout.fillHeight: true
            font.pointSize: 20

            placeholderText: "Enter answere here."

            id: textArea
            textFormat: Qt.RichText
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
            focus: true
            selectByMouse: true
            persistentSelection: true

            padding: 0

            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
}
