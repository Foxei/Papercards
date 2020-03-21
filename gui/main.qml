import QtQuick 2.14
import QtQuick.Layouts 1.14
import Qt.labs.platform 1.0
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import io.papercards.backend 1.0

import "components" as Components

ApplicationWindow {
    property real scaleFactor: statusBar.scaleFactor

    id: root
    visible: true
    title: "Papercards"
    width: 800
    height: 600

    signal newDeck()
    signal openDeck()
    signal saveDeck()
    signal saveDeckAs()
    signal quitApplication()
    signal aboutApplication()

    onActiveFocusControlChanged: {
        if(activeFocusControl == null) return;
        var focusObjectName = activeFocusControl.objectName;

        var cardFocused = focusObjectName.startsWith("card");
        toolBar.enableTextFunctions = cardFocused;

        var textAreaFocused = focusObjectName.startsWith("card-answer");
        toolBar.enableEditorFunctions = textAreaFocused;

        if(cardFocused){
            var cardView = activeFocusControl.parent.parent;
        }
    }

    onNewDeck: {
        busyPopup.open();
        BackEnd.newDeck();
    }

    onOpenDeck: {
        openDialog.open()
    }

    onSaveDeck: {
        if(!BackEnd.isUrlValid()){
            saveDialog.open();
        }else{
            busyPopup.open();
            BackEnd.saveAs(BackEnd.fileUrl);
        }
    }

    onSaveDeckAs: {
        saveDialog.open()
    }

    onQuitApplication: {
        Qt.callLater(Qt.quit)
    }

    onAboutApplication: {
        aboutPopup.open();
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

         var component;
         var os = Qt.platform.os;
         if(os == "osx"){
             print("Os supports native menu bar: " + os + ".");
             component = Qt.createComponent("components/NativeMenuBar.qml");
         } else {
             print("Os does not supports native menu bar: " + os + ".");
            component = Qt.createComponent("components/DefaultMenuBar.qml");
         }
         var object = component.createObject(root);
         root.menuBar = object;
         object.newDeck.connect(newDeck);
         object.openDeck.connect(openDeck);
         object.saveDeck.connect(saveDeck);
         object.saveDeckAs.connect(saveDeckAs);
         object.quitApplication.connect(quitApplication);
         object.aboutApplication.connect(aboutApplication);
    }

    function backgroundWorkDone() {
        busyPopup.close();
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
            //BusyIndicator {
            //    running: true
            //}
            //Label {
            //   text: "Saving..."
            //}
        }
    }

}
