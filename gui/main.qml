import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtGraphicalEffects 1.14

import "components" as Components

ApplicationWindow {
    property real scaleFactor: 1.0

    id: root
    visible: true
    title: "Papercards"
    width: 800
    height: 600

    onActiveFocusControlChanged: {
        if(activeFocusControl == null) return;
        var focusObjectName = activeFocusControl.objectName;
        console.log(activeFocusControl)
        var cardFocused = focusObjectName.startsWith("card");
        toolBar.enableTextFunctions = cardFocused;

        var textAreaFocused = focusObjectName.startsWith("card-answer");
        toolBar.enableEditorFunctions = textAreaFocused;

        if(cardFocused){
            var cardView = activeFocusControl.parent.parent;
        }
    }

    Component.onCompleted: {
        toolBar.bold.connect(editorContent.bold);
        toolBar.italic.connect(editorContent.italic);
        toolBar.underlined.connect(editorContent.underlined);
        toolBar.bulletList.connect(editorContent.bulletList);
        toolBar.increaseIndentation.connect(editorContent.increaseIndentation);
        toolBar.decreaseIndentation.connect(editorContent.decreaseIndentation);
        toolBar.textBackground.connect(editorContent.textBackground);
        toolBar.textForground.connect(editorContent.textForground);
    }

    onScaleFactorChanged: {
        cardView.scaleFactor = scaleFactor;
        statusBar.scaleFactor = scaleFactor;
    }

    Components.RobotoFontLoader{}

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action { text: qsTr("&Open...") }
            Action { text: qsTr("&Save") }
            Action { text: qsTr("Save &As...") }
            MenuSeparator { }
            Action {
                text: qsTr("&Quit")
                onTriggered: Qt.callLater(Qt.quit)
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                onTriggered:aboutPopup.open();
            }
        }
    }
    DialogAbout{
        id: aboutPopup
    }


    header: EditorToolBar{
        id: toolBar
    }

    footer: EditorStatusBar{
        id: statusBar
        onScaleFactorChanged: {
            root.scaleFactor = statusBar.scaleFactor
        }
    }

    EditorContent {
        id: editorContent
        anchors.fill: parent
    }
}
