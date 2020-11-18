import QtQuick 2.14
import QtQuick.Layouts 1.14
import Qt.labs.platform 1.0
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import io.papercards.backend 1.0

import "components" as Components

ApplicationWindow {
//    flags: Qt.FramelessWindowHint
    property real scaleFactor: statusBar.scaleFactor
    property var targetFunction
    property bool discard: false

    id: root
    visible: true
    title: "Papercards"
    width: 800
    height: 600

    signal newDeck()
    signal openDeck()
    signal saveDeck()
    signal saveDeckAs()
    signal exportAsPdf()
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
        var modified = BackEnd.modified;
        console.log("Modified:", modified, "Discard:", discard);
        if(modified && !discard) {
            discardDialog.open();
            targetFunction = newDeck
        } else {
            busyPopup.open();
            BackEnd.newDeck();
            discard = false;
        }
    }

    onOpenDeck: {
        var modified = BackEnd.modified;
        console.log("Modified:", modified, "Discard:", discard);
        if(modified && !discard) {
            discardDialog.open();
            targetFunction = openDeck;
        } else {
            openDialog.open()
        }
    }

    onSaveDeck: {
        if(!BackEnd.isUrlValid()){
            saveDialog.open();
        }else{
            busyPopup.open();
            BackEnd.saveAs(BackEnd.fileUrl);
            BackEnd.modified = false;
            discard = true;
        }
    }

    onSaveDeckAs: {
        saveDialog.open()
    }

    onExportAsPdf: {
        exportDialog.open();
    }

    onClosing: {
        close.accepted = false;
        quitApplication();
    }

    onQuitApplication: {
        var modified = BackEnd.modified;
        if(modified && !discard) {
            discardDialog.open();
            targetFunction = quitApplication;
        } else {
            busyPopup.open();
            Qt.callLater(Qt.quit)
        }
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
        BackEnd.exported.connect(backgroundWorkDone);

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
         if(os !== "osx"){
            root.menuBar = object;
         }
         object.newDeck.connect(newDeck);
         object.openDeck.connect(openDeck);
         object.saveDeck.connect(saveDeck);
         object.saveDeckAs.connect(saveDeckAs);
         object.exportAsPdf.connect(exportAsPdf);
         object.quitApplication.connect(quitApplication);
         object.aboutApplication.connect(aboutApplication);

         BackEnd.modified = false;
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
        focus: true
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
        onRejected: discard = false
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
            BackEnd.modified = false;
            discard = true;
        }
    }

    FileDialog {
        id: exportDialog
        fileMode: FileDialog.SaveFile
        defaultSuffix: "pdf"
        nameFilters: ["Portable Document Format (PDF) (*.pdf)", "All files (*)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            busyPopup.open();
            BackEnd.exportAsPdf(file)
        }
    }

    Dialog {
        id: busyPopup
        anchors.centerIn: Overlay.overlay
        modal: true
        closePolicy: Popup.CloseOnEscape
        ColumnLayout{
            anchors.fill: parent
            BusyIndicator {
                running: true
            }
            Label {
               text: "Please wait..."
            }
        }
    }

    DialogConfirmDiscard {
        id: discardDialog
        onAccepted: {
            discard = true;
            targetFunction();
        }
        onRejected: {
            discard = false;
            targetFunction = null;
        }
    }

}
