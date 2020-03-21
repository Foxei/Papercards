import Qt.labs.platform 1.0

import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtGraphicalEffects 1.14
import io.papercards.backend 1.0

import "components" as Components

ApplicationWindow {
    property real scaleFactor: statusBar.scaleFactor

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
        toolBar.newCard.connect(BackEnd.addNewCard);
        toolBar.newDeck.connect(newDeck);

        BackEnd.loaded.connect(backgroundWorkDone);
        BackEnd.saved.connect(backgroundWorkDone);
    }

    function backgroundWorkDone() {
        busyPopup.close();
    }

    function save() {
        if(!BackEnd.isUrlValid()){
            saveDialog.open();
        }else{
            busyPopup.open();
            BackEnd.saveAs(BackEnd.fileUrl);
        }
    }

    function newDeck() {
        busyPopup.open();
        BackEnd.newDeck();
    }

    Components.RobotoFontLoader{}

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&New...")
                onTriggered: newDeck()
            }
            Action {
                text: qsTr("&Open...")
                shortcut: StandardKey.Open
                onTriggered: openDialog.open()
            }
            Action {
                text: qsTr("&Save")
                onTriggered: save()
            }
            Action {
                text: "Save &As..."
                shortcut: StandardKey.SaveAs
                onTriggered: saveDialog.open()
            }
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
    }

    EditorContent {
        id: editorContent
        anchors.fill: parent
        scaleFactor: root.scaleFactor
    }

    FileDialog {
        id: openDialog
        modality: Qt.ApplicationModal
        fileMode: FileDialog.OpenFile
        nameFilters: ["Json files (*.json)", "All files (*)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            busyPopup.open()
            BackEnd.load(file)
        }
    }

    FileDialog {
        id: saveDialog
        modality: Qt.ApplicationModal
        fileMode: FileDialog.SaveFile
        defaultSuffix: "json"
        nameFilters: openDialog.nameFilters
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            busyPopup.open();
            BackEnd.saveAs(file)
        }
    }

    Dialog {
        id: busyPopup
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape
        ColumnLayout{
            anchors.fill: parent
            BusyIndicator {
                running: true
            }
            Label {
                text: "Saving..."
            }
        }
    }

}
