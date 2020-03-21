import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import io.papercards.backend 1.0

import "components" as Components

Components.MoveableScrollView {
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

    onBold: {
        if(focusedCard == null) return;
        focusedCard.bold();
    }
    onItalic: {
        if(focusedCard == null) return;
        focusedCard.italic();
    }
    onUnderlined: {
        if(focusedCard == null) return;
        focusedCard.underlined();
    }
    onBulletList: {
        if(focusedCard == null) return;
        focusedCard.bulletList();
    }
    onIncreaseIndentation: {
        if(focusedCard == null) return;
        focusedCard.increaseIndentation();
    }
    onDecreaseIndentation: {
        if(focusedCard == null) return;
        focusedCard.decreaseIndentation();
    }
    onTextBackground: {
        if(focusedCard == null) return;
        focusedCard.textBackground(highlightColor);
    }
    onTextForground: {
        if(focusedCard == null) return;
        focusedCard.textForground(textColor);
    }


    padding: 0
    anchors.fill: parent
    contentHeight: contentPane.height*scaleFactor
    contentWidth: Math.max(parent.width, contentPane.width*scaleFactor)

    Component.onCompleted: {
        creatDynamicObjectList();
        BackEnd.cleared.connect(clearDynamicObjects);
        BackEnd.loaded.connect(creatDynamicObjectList);
        BackEnd.cardAdded.connect(createDynamicObject);
        BackEnd.cardAdded.connect(scollToEnd);
    }

    function scollToEnd(){
        contentScroll.scrollTo(1);
    }

    function checkFocus(){
        var childs = contentPane.contentChildren[0].children;
        for (var i=0; i<childs.length; i++) {
            var object = childs[i];
            if(object === null) continue
            if(object.activeFocus){
                object.activeFocusChanged.connect(checkFocus);
                focusedCard = object;
            }else{
                object.activeFocusChanged.disconnect(checkFocus);
            }
        }
    }

    function createDynamicObject(card){
        var component = Qt.createComponent("CardView.qml");
        var object = component.createObject(layout);
        object.displayedCard = card
        object.loadCard();
        object.activeFocusChanged.connect(checkFocus);
    }

    function creatDynamicObjectList() {
        for (var i=0; i<BackEnd.cards.length; i++) {
            createDynamicObject(BackEnd.cards[i]);
        }
    }

    function clearDynamicObjects() {
        focusedCard = null;
        var childs = contentPane.contentChildren[0].children;
        for (var i=childs.length-1; i>=0; i--) {
            var object = childs[i];
            object.destroy(1);
        }
    }

    Pane{
        id: contentPane
        anchors.centerIn: parent
        scale: scaleFactor

        ColumnLayout {
            id: layout
            spacing: 20
        }
    }
}
