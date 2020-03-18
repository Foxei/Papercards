import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Window 2.3
import io.papercards.card 1.0
import io.papercards.backend 1.0

import "../basics" as Basics

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
        spacing: 0

        TextField {
            id: cardQuestionField
            objectName: "card-question"

            Layout.fillWidth: true
            padding: 0

            font.pointSize: Screen.devicePixelRatio*20
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere

            text: card.card_question_text;
            placeholderText: "Enter question here."

            selectByMouse: true
            persistentSelection: true

            onTextEdited: {
                card.card_question_text = cardQuestionField.text;
            }
        }
        Basics.TextAreaErrorField {
            id: textArea
            objectName: "card-answer"

            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 0

            font.pointSize: Screen.devicePixelRatio*16
            textFormat: Qt.RichText
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere

            selectByMouse: true
            persistentSelection: true

            placeholderText: "Enter answere here."

            onTextChanged: {
                var overflow = textArea.paintedHeight>textArea.height;
                showTopErrorMessage(overflow);
                showBottomErrorMessage(overflow, "This card contains a text overflow.");

                card.card_question_text = textArea.text;
            }

        }
    }
}
