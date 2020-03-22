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
    id: cardRoot
    objectName: "card-view"
    property Card displayedCard: BackEnd.current_card

    property real pixelCardWidth: displayedCard.card_size.width*Screen.pixelDensity
    property real pixelCardHeight: displayedCard.card_size.height*Screen.pixelDensity
    property real pixelCardBorder: 5*Screen.pixelDensity

    property DocumentHandler documentInFocus

    signal bold()
    signal italic()
    signal underlined()
    signal bulletList()
    signal increaseIndentation()
    signal decreaseIndentation()
    signal textBackground(color highlightColor)
    signal textForground(color textColor)

    onBold: {
        if(documentInFocus == null) return;
        documentInFocus.bold = !documentInFocus.bold;
    }
    onItalic: {
        if(documentInFocus == null) return;
        documentInFocus.italic = !documentInFocus.italic;
    }
    onUnderlined: {
        if(documentInFocus == null) return;
        documentInFocus.underline = !documentInFocus.underline;
    }
    onBulletList: {
        if(documentInFocus == null) return;
        documentInFocus.bulletList = !documentInFocus.bulletList;
        cardAnswerInput.updateCursorPosition();
    }
    onIncreaseIndentation: {
        if(documentInFocus == null) return;
        documentInFocus.increaseIndentation();
        cardAnswerInput.updateCursorPosition();
    }
    onDecreaseIndentation: {
        if(documentInFocus == null) return;
        documentInFocus.decreaseIndentation();
        cardAnswerInput.updateCursorPosition();
    }
    onTextBackground: {
        if(documentInFocus == null) return;
        if(highlightColor === Qt.rgba(1,1,1,1)) documentInFocus.resetHighlightColor();
        else documentInFocus.highlightColor = highlightColor;
    }
    onTextForground: {
        if(documentInFocus == null) return;
        if(textColor === Qt.rgba(1,1,1,1)) documentInFocus.resetTextColor();
        else documentInFocus.textColor = textColor;
    }

    Component.onCompleted:{

    }
    function loadCard(){
        cardAnswerInputHandler.load();
        cardQuestionInputHandler.load();
    }

    Material.elevation: 6
    Material.theme: Material.Light

    Layout.preferredWidth: pixelCardWidth
    padding: 0

    ColumnLayout {
        id: cardRootLayout
        anchors.fill: parent
        spacing: 0

        TextArea {
            id: cardQuestionInput
            objectName: "card-question-input"

            Layout.fillWidth: true
            Layout.leftMargin: pixelCardBorder; Layout.rightMargin: pixelCardBorder
            Layout.bottomMargin: 0

            padding: 0

            font.pointSize: Screen.devicePixelRatio*20
            textFormat: Qt.PlainText
            selectByMouse: true
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
            placeholderText: "Enter question here."

            KeyNavigation.priority: KeyNavigation.BeforeItem
            KeyNavigation.tab: cardAnswerInput

            onActiveFocusChanged: {
                if(activeFocus)
                    documentInFocus = cardQuestionInputHandler;
            }
            DocumentHandler {
                id: cardQuestionInputHandler
                card: cardRoot.displayedCard
                cardField: Card.Question
                document: cardQuestionInput.textDocument
                cursorPosition: cardQuestionInput.cursorPosition
                selectionStart: cardQuestionInput.selectionStart
                selectionEnd: cardQuestionInput.selectionEnd
            }
        }

        Rectangle {
            id: cardSeperator
            Material.theme: Material.Dark
            color: Material.background
            implicitWidth: pixelCardWidth
            implicitHeight: 2
        }

        Components.TextAreaErrorField {
            id: cardAnswerInput
            objectName: "card-answer-input"

            Layout.preferredHeight: pixelCardHeight-2*pixelCardBorder
            Layout.fillWidth: true
            Layout.margins: pixelCardBorder

            padding: 0

            font.pointSize: Screen.devicePixelRatio*16
            textFormat: Qt.PlainText
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
            selectByMouse: true
            placeholderText: "Enter answer here."

            Keys.onPressed: {
                if (event.key === Qt.Key_Tab) {
                    increaseIndentation();
                }
                BackEnd.modified = true;
            }
            KeyNavigation.priority: KeyNavigation.BeforeItem
            KeyNavigation.tab: cardAnswerInput

            onTextChanged: {
                var overflow = cardAnswerInput.paintedHeight>cardAnswerInput.height;
                showTopErrorMessage(overflow);
                showBottomErrorMessage(overflow, "This card contains a text overflow.");
            }
            onActiveFocusChanged:{
                if(activeFocus) {
                    documentInFocus = cardAnswerInputHandler;
                }
            }

            DocumentHandler {
                id: cardAnswerInputHandler
                card: cardRoot.displayedCard
                cardField: Card.Answer
                document: cardAnswerInput.textDocument
                cursorPosition: cardAnswerInput.cursorPosition
                selectionStart: cardAnswerInput.selectionStart
                selectionEnd: cardAnswerInput.selectionEnd
            }
        }
    }
}
