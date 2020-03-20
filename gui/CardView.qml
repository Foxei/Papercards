import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14

import io.papercards.card 1.0
import io.papercards.backend 1.0
import io.papercards.texteditor 1.0

import "components" as Components

Pane {
    id: cardPane
    objectName: "card-view"
    property Card card: BackEnd.current_card

    property real cardWidth: BackEnd.current_card.card_size.width*Screen.pixelDensity
    property real cardHeight: BackEnd.current_card.card_size.height*Screen.pixelDensity
    property real cardBorder: 5*Screen.pixelDensity
    property real fontSize: document.fontSize

    signal bold()
    signal italic()
    signal underlined()
    signal bulletList()
    signal increaseIndentation()
    signal decreaseIndentation()

    onBold: document.bold = !document.bold;
    onItalic: document.italic = !document.italic;
    onUnderlined: document.underline = !document.underline;
    onBulletList: {
        document.bulletList = !document.bulletList;
        textArea.updateCursorPosition();
    }
    onIncreaseIndentation: {
        document.increaseIndentation();
        textArea.updateCursorPosition();
    }
    onDecreaseIndentation: {
        document.decreaseIndentation();
        textArea.updateCursorPosition();
    }
    Material.elevation: 6
    Material.theme: Material.Light

    padding: 0
    Layout.preferredWidth: cardWidth

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        TextArea {
            id: cardQuestionField
            objectName: "card-question"

            Layout.fillWidth: true
            Layout.leftMargin: cardBorder; Layout.rightMargin: cardBorder
            Layout.bottomMargin: 0

            padding: 0

            font.pointSize: Screen.devicePixelRatio*20
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere

            text: card.card_question_text;
            placeholderText: "Enter question here."

            selectByMouse: true
            persistentSelection: true

            onTextChanged: {
                card.card_question_text = cardQuestionField.text;
            }
        }
        Rectangle {
            Material.theme: Material.Dark
            color: Material.background
            implicitWidth: cardWidth
            implicitHeight: 2
        }
        Components.TextAreaErrorField {
            id: textArea
            objectName: "card-answer"

            Layout.preferredHeight: cardHeight-2*cardBorder
            Layout.fillWidth: true
            Layout.margins: cardBorder
            padding: 0
            font.pointSize: Screen.devicePixelRatio*16
            textFormat: Qt.PlainText
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere

            selectByMouse: true

            text: card.card_answer_text;
            placeholderText: "Enter answer here."
            Keys.onPressed: {
                if (event.key === Qt.Key_Tab) {
                    increaseIndentation();
                }
            }
            KeyNavigation.priority: KeyNavigation.BeforeItem
            KeyNavigation.tab: textArea
            onTextChanged: {
                var overflow = textArea.paintedHeight>textArea.height;
                showTopErrorMessage(overflow);
                showBottomErrorMessage(overflow, "This card contains a text overflow.");
            }
            DropArea {
                id: dropArea
                anchors.fill: parent
                keys: ["text/uri-list"]
                onEntered: {
                    if(drag.hasUrls){
                        if(BackEnd.checkIfValidImage(drag.urls)){
                            drag.accept(Qt.CopyAction);
                            console.log("[FrontEnd] File accepted.");
                            return;
                        }
                    }
                    console.log("[FrontEnd] File rejected.");
                    drag.accepted = false;
                }

                onDropped: {
                    if(drop.hasUrls){
                        console.log(drop.urls[0]);
                    }
                }
            }

        }
        Component.onCompleted: document.load("");
        DocumentHandler {
            id: document
            document: textArea.textDocument
            cursorPosition: textArea.cursorPosition
            selectionStart: textArea.selectionStart
            selectionEnd: textArea.selectionEnd
            onLoaded: {
                textArea.text = text
            }
            onError: {
                errorDialog.text = message
                errorDialog.visible = true
            }
        }
    }
}
