import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import io.papercards.backend 1.0

ScrollView {
    id: contentScroll

    property real scaleFactor: 1.0
    property CardView focusedCard: null

    signal bold()
    signal italic()
    signal underlined()
    signal bulletList()
    signal increaseIndentation()
    signal decreaseIndentation()
    signal textBackground(color highlightColor)
    signal textForground(color textColor)

    onBold: if(focusedCard !== null) focusedCard.bold();
    onItalic: if(focusedCard !== null) focusedCard.italic();
    onUnderlined: if(focusedCard !== null) focusedCard.underlined();
    onBulletList: if(focusedCard !== null) focusedCard.bulletList();
    onIncreaseIndentation: if(focusedCard !== null) focusedCard.increaseIndentation();
    onDecreaseIndentation: if(focusedCard !== null) focusedCard.decreaseIndentation();
    onTextBackground: if(focusedCard !== null) focusedCard.textBackground(highlightColor);
    onTextForground: if(focusedCard !== null) focusedCard.textForground(textColor);


    padding: 0
    anchors.fill: parent
    contentHeight: contentPane.height*scaleFactor
    contentWidth: Math.max(parent.width, contentPane.width*scaleFactor)

    Pane{
        id: contentPane
        anchors.centerIn: parent
        scale: scaleFactor

        ColumnLayout {
            id: layout
            spacing: 20

            CardView {
                onActiveFocusChanged: if(activeFocus) focusedCard = this;
            }

            CardView {
                onActiveFocusChanged: if(activeFocus) focusedCard = this;
            }

            CardView {
                onActiveFocusChanged: if(activeFocus) focusedCard = this
            }
        }
    }


}
